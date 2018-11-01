//Copyright : starblaze inc for hash performance test
// 1. use given string patten 
// 2. hash exectuting timing cost caculate  
// 3. test hash hit ratio
#include "test/benchmark.h"
#include "hashmap.h"
#include "murmurhash.h"
#include <stdlib.h>


HashStr TestHash(HashParam *param){

    struct timeval start, end;
    //caculate length of string
    *(param->len) = strlen(param->str);
    param->len++;

    //caculate the time of hash executing
    gettimeofday(&start, NULL);

    HashStr hash = param->handler(param->str);
    // in X86_64 mode
    if(sizeof(HashStr)==8) 
       hash = ((hash+2) << sizeof(uint32_t)*8) & ((hash+1) << sizeof(uint32_t));

    gettimeofday(&end, NULL);

    //*(param->time) = end.tv_sec-star.tv_sec;
    *param->time=(time2.tv_sec-time1.tv_sec)*1000.+ (time2.tv_usec-time1.tv_usec)/1000.; 
    param->time++;

    return hash; 
}

HashStr TestMurMurHash(HashParam *param){
    printf("INFO : MurMurHash Test");

    struct timeval start, end;
    //caculate length of string
    *(param->len) = strlen(param->str);
    param->len++;

    uint32_t len = strlen(str);
    uint32_t seed = GetTimeStrapasSeed();

    //caculate the time of hash executing
    gettimeofday(&start, NULL);

    // in X86_64 mode
    if(sizeof(HashStr) == 8)
       HashStr hash = MurmurHash64A(param->str, len,  seed);
    // in i386 mode
    else if(sizeof(HashStr) ==4)
       HashStr hash = MurmurHash2(param->str, len, seed);

    gettimeofday(&end, NULL);

    //*(param->time) = end.tv_sec-star.tv_sec;
    *param->time = (time2.tv_sec-time1.tv_sec)*1000.+ (time2.tv_usec-time1.tv_usec)/1000.; 
    param->time++;

    return hash; 
}

void BenchMark(HashParam *param){
   // make stastics for different string length

    printf("INFO : **************************************************\n");
    printf("INFO : Result of  %s\n", param.name);
    printf("INFO : **************************************************\n");

    for(int i=0; i<sizeof(param->len); i++){
        uint32_t N128;
        uint32_t N256;
        uint32_t N512;
        uint32_t N1024;
        uint32_t N2048;
        uint32_t N4096;

        long N128;
        long N256;
        long N512;
        long N1024;
        long N2048;
        long N4096;

        uint32_t HIT;
       if(param->len[i] < 128){
           N128++;
           T128+=param->time[i];
       }
       else if(param->len[i] < 256){
           N256++;
           T256+=param->time[i];
       }
       else if(param->len[i] < 512){
           N512++;
           T512+=param->time[i];
       }
       else if(param->len[i] < 1024){
           N1024++;
           T1024+=param->time[i];
       }
       else if(param->len[i] < 2048){
           N2048++;
           T2048+=param->time[i];
       }
       else if(param->len[i] < 4096){
           N4096++;
           T4096+=param->time[i];
       }

       HashStr *str= param->hashstr[i];
       uint32_t hittmp;
       for(int j=0; j<sizeof(param->hashstr); j++){
           if(strcmp(str, param->hashstr[j])==0)
              hittmp++;
       }
       if(hittmp>1);
         HIT++;
    }
    
    printf("INFO : hash hit ratio : %d\n", HIT)
    printf("INFO : bit128 average performance : %ld\n", (long)(T128/N128));
    printf("INFO : bit128 average performance : %ld\n", (long)(T256/N256));
    printf("INFO : bit128 average performance : %ld\n", (long)(T512/N512));
    printf("INFO : bit128 average performance : %ld\n", (long)(T1024/N1024));
    printf("INFO : bit128 average performance : %ld\n", (long)(T2048/N2048));
    printf("INFO : bit128 average performance : %ld\n", (long)(T4096/N4096));
    printf("INFO : **************************************************\n");
    

}

char FindCase(char *name){
    for(uint32_t i=0; i<sizeof(list), i++){
        if(strcmp(name, list[i]) == 0)
          return i+1;
    }
    return 0;
}

uint32_t FindPattern(fileType files){
     _finddata_t filedir;

    long lfDir;
    uint32_t i=0;
 
    if((lfDir = _findfirst(dir,&fileDir))==-1l)
      printf("INFO : No pattern is found\n");
      assert(0);
    else{
      printf("file list:\n");
      do{
        printf("%s\n",fileDir.name);
        files[i]=fileDir.name;
        i++;
      }while( _findnext( lfDir, &fileDir ) == 0 );
    }
    _findclose(lfDir);
 
  return i;

}

void LoadString(char* name, char* str){
  FILE *fp;

  if( (fp=fopen(name)) == NULL ){
       printf("Cannot open file : %s, press any key to exit!\n", name);
       getch();
       exit(1);
   }
  
   fgets(str, N, fp);

   fclose(fp);
} 

void LaunchTest(char *name){
    fileType files;
    HashParam *param;

    param = (HashParam*)malloc(sizeof(struct HashParam));
    param->time =(double *)malloc(sizeof(double)*1000);
    param->len =(uint32_t *)malloc(sizeof(uint32_t)*1000);
    param->hashstr =(uint32_t *)malloc(sizeof(uint32_t)*1000);

    uint32_t num =  FindFiles(files);
    char opcode = FindHash(name);
    if(opecode==1){
         for(int i=0, i<num; i++){
           LoadString(files[i], param->str); 
           TestMurMurHash(param)
           free(param->str);
         }

         BenchMark(param);

    } 
    else{
       switch(opcode) {
          case 2:
              param->handler = RSHash;
              param->name = "RSHash";
          case 3:
              param->handler = SDBMHash;
              param->name = "SDBMHash";
          case 4:
              param->handler = JSHash;
              param->name = "JSHash";
          case 5:
              param->handler = PJWHash;
              param->name = "PJWHash";
          case 6:
              param->handler = ELFHash;
              param->name = "ELFHash";
          case 7:
              param->handler = BKDRHash;
              param->name = "BKDRHash";
          case 8:
              param->handler = DJBHash;
              param->name = "DJBHash";
          case 9:
              param->handler = APHash;
              param->name = "APHash";
       }
       for(int i=0, i<num; i++){
         LoadString(files[i], param->str); 
         param->hashstr[i] = TestHash(param)
         free(param->str);
       }
       BenchMark(param);
    }

    free(param->time);
    free(param->len);
    free(param->hashstr);
    free(param);
}

void LaunchAllTest(char *str){
    print("launch all Hash test")

    for(int i=0; i<sizeof(list); i++){
      LaunchTest(list[i]);
    }
}

