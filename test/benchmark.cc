//Copyright : starblaze inc for hash performance test
// 1. use given string patten 
// 2. hash exectuting timing cost caculate  
// 3. test hash hit ratio
#include "test/benchmark.h"
#include "include/hashmap.h"
#include "include/murmurhash.h"
#include <stdlib.h>
#include <sys/time.h>
#include <conio.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


HashStr TestHash(HashParam *param, uint32_t n){

    struct timeval start, end;
    uint32_t hash_tmp;
    HashStr hash;
    //caculate length of string
    //*(param->len) = strlen(param->str);
    //param->len++;
    param->len[n]=strlen(param->str);

    //caculate the time of hash executing
    gettimeofday(&start, NULL);

    hash_tmp = param->handler(param->str);
    // in X86_64 mode
    if(sizeof(HashStr)==8) 
       hash = ((hash_tmp+2) << sizeof(uint32_t)*8) & ((hash_tmp+1) << sizeof(uint32_t));

    gettimeofday(&end, NULL);

    //*(param->time) = end.tv_sec-star.tv_sec;
    //*param->time=(end.tv_sec-start.tv_sec)*1000.+ (end.tv_usec-start.tv_usec)/1000.; 
    //param->time++;
    param->time[n]=(end.tv_sec-start.tv_sec)*1000.+ (end.tv_usec-start.tv_usec)/1000.; 

    return hash; 
}

HashStr TestMurMurHash(HashParam *param, uint32_t n){
    printf("INFO : MurMurHash Test");

    struct timeval start, end;
    HashStr hash;
    //caculate length of string
    printf("string is %s\n", param->str);
    printf("string is %d\n", strlen(param->str));
    *(param->len+n) = strlen(param->str) ;

    uint32_t len = strlen(param->str);
    uint32_t seed = GetTimeStrapasSeed();

    //caculate the time of hash executing
    gettimeofday(&start, NULL);

    // in X86_64 mode
    if(sizeof(HashStr) == 8)
       hash = MurmurHash64A(param->str, len,  seed);
    // in i386 mode
    else if(sizeof(HashStr) == 4)
       hash = MurmurHash2(param->str, len, seed);

    gettimeofday(&end, NULL);

    //*(param->time) = end.tv_sec-star.tv_sec;
    *(param->time+n) = (end.tv_sec-start.tv_sec)*1000.+ (end.tv_usec-start.tv_usec)/1000.; 

    return hash; 
}

void BenchMark(HashParam *param){
   // make stastics for different string length

    uint32_t HIT=0;

    uint32_t N128=0;
    uint32_t N256=0;
    uint32_t N512=0;
    uint32_t N1024=0;
    uint32_t N2048=0;
    uint32_t N4096=0;

    uint64_t T128=0;
    uint64_t T256=0;
    uint64_t T512=0;
    uint64_t T1024=0;
    uint64_t T2048=0;
    uint64_t T4096=0;

    printf("INFO : **************************************************\n");
    printf("INFO : Result of  %s\n", param->name);
    printf("INFO : **************************************************\n");

    for(int i=0; i<param->num; i++){



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

       HashStr str= param->hashstr[i];
       uint32_t hittmp=0;
       for(int j=0; j<param->num; j++){
           //if(strcmp(str, param->hashstr[j])==0)
           if(str != param->hashstr[j])
              hittmp++;
       }
       HIT=hittmp-param->num;
    }

    double R128 = (N128!=0) ? (double) (T128/N128) : 0.;
    double R256 = (N256!=0) ? (double) (T256/N256) : 0.;
    double R512 = (N512!=0) ? (double) (T512/N512) : 0.;
    double R1024 = (N1024!=0) ? (double) (T1024/N1024) : 0.;
    double R2048 = (N2048!=0) ? (double) (T2048/N2048) : 0.;
    double R4096 = (N4096!=0) ? (double) (T4096/N4096) : 0.;


    


    printf("INFO : hash hit ratio : %d\n", HIT);
    printf("INFO : bit128 average performance : %f\n", R128);
    printf("INFO : bit256 average performance : %f\n", R256);
    printf("INFO : bit512 average performance : %f\n", R512);
    printf("INFO : bit1024 average performance : %f\n", R1024);
    printf("INFO : bit2048 average performance : %f\n", R2048);
    printf("INFO : bit4096 average performance : %f\n", R4096);
    printf("INFO : **************************************************\n");
    

}

char FindHash(char *name){
    for(uint32_t i=0; i<sizeof(list); i++){
        if(strcmp(name, list[i]) == 0)
          return i+1;
    }
    return 0;
}

uint32_t FindPattern( char *files[1000]){
    struct _finddata_t fileDir;

    long lfDir;
    uint32_t i=0;

    char* _Dir;
    _Dir = (char*)malloc(sizeof(char)*255);
    char dir[255];
    getcwd(dir, sizeof(dir));
    strcpy(_Dir, dir);

    #ifdef _WIN32
    printf("windosws !\n" );
    strcat(dir, "\\pattern\\*txt");
    strcat(_Dir, "\\pattern\\");
    #endif

    #ifdef linux
    strcat(dir, "/pattern/*.txt");
    strcat(_Dir, "/pattern/");
    #endif

    if((lfDir = _findfirst(dir, &fileDir))==-1){
      printf("INFO : No pattern is found\n");
      assert(0);
    }
    else{
      printf("file list:\n");
      do{
        printf("%s\n",fileDir.name);
        //files[i]=&fileDir.name[0];
        char *_Files;
        _Files = (char *)malloc(sizeof(char)*255);
        strcpy(_Files, _Dir);
        strcat(_Files, fileDir.name);
        files[i] =(char*)malloc(sizeof(char)*255);
        strcpy(files[i],_Files);
        printf("%s\n",files[i]);
        free(_Files);
        i++;
      }while( _findnext( lfDir, &fileDir ) == 0 );
    }
    _findclose(lfDir);

  for(int j=0; j<i; j++){
     printf("files is %s\n", files[j]);
  }
 
  return i;

}

void LoadString(char* name, HashParam *param){
  FILE *fp;
  uint32_t flen;  

  if( (fp=fopen(name, "r")) == NULL ){
       printf("Cannot open file : %s, press any key to exit!\n", name);
       getch();
       exit(1);
   }

   fseek(fp, 0L, SEEK_END);
   flen=ftell(fp); 
   param->str=(char *)malloc(flen+1);
   if(param->str==NULL){
       printf("INFO: file : %s is empty", name);
       getch();
   }
   else {
     fseek(fp, 0L, SEEK_SET);
     fread(param->str, flen, 1, fp);
     param->str[flen] = 0;
   }

   fclose(fp);
} 

void LaunchTest(char *name){
    char*files[1000];
    HashParam *param;

    param = (HashParam*)malloc(sizeof(HashParam));
    //param->time =(double *)malloc(sizeof(double)*1000);
    //param->len =(uint32_t *)malloc(sizeof(uint32_t)*1000);
    //param->hashstr =(uint32_t *)malloc(sizeof(uint32_t)*1000);

    param->name = name;

    param->num =  FindPattern(files);
    char opcode = FindHash(name);
    if(opcode==1){
         for(int i=0; i<param->num; i++){
           printf("file name is %s", files[i]);
           LoadString(files[i], param); 
           param->hashstr[i] = TestMurMurHash(param, i);
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
       for(int i=0; i<param->num; i++){
         LoadString(files[i], param); 
         param->hashstr[i] = TestHash(param, i);
         free(param->str);
       }
       BenchMark(param);
    }

    free(param->time);
    free(param->len);
    free(param->hashstr);
    free(param);
}

void LaunchAllTest(void){
    printf("launch all Hash test");

    for(int i=0; i<sizeof(list); i++){
      LaunchTest(list[i]);
    }
}

