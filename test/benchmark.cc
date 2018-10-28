//Copyright : starblaze inc for hash performance test
// 1. use given string patten 
// 2. hash exectuting timing cost caculate  
// 3. test hash hit ratio
#include "benchmark.h"
#include "hashmap.h"
#include "murmurhash.h"


uint64_t TestHash64(uint64_t (*func)(),  char *str, uint32_t *len, time_t *time){
    struct timeval start, end;

    //caculate length of string
    *len = strlen(str);
    len++;

    //caculate the time of hash executing
    gettimeofday(&start, NULL);

    uint64_t hash = (func)(str);
    gettimeofday(&end, NULL);

    *time_t = end.tv_sec-star.tv_sec;
    time_t++;

    return hash; 
}

uint64_t TestHash(uint32_t (*func)(),  char *str, uint32_t *len, time_t *time){
    struct timeval start, end;

    //caculate length of string
    *len = strlen(str);
    len++;

    //caculate the time of hash executing
    gettimeofday(&start, NULL);

    uint64_t hash = (func)(str);
    gettimeofday(&end, NULL);

    *time_t = end.tv_sec-star.tv_sec;
    time_t++;

    return hash; 
}


uint64_t TestMurMurHash64(char *str, uint32_t len, time_t *time){
    printf("INFO : MurMurHash64 Test");
    return TestHash64(MurmurHash64A, str, len, time);
}

uint64_t TestRSHash64(char *str, uint32_t *len, time_t *time ){
    printf("INFO : RSHash64 Test");
    return TestHash64(RSHash64, str, len, time);
}

uint64_t TestSDBMHash64(char *str, uint32_t *len, time_t *time){
    printf("INFO : SDBMHash64 Test");
    return TestHash64(SDBMHash64, str, len, time);
}

uint64_t TestJSHash64(char *str, uint32_t *len, time_t *time){
    printf("INFO : JSHash64 Test");
    return TestHash64(JSHash64, str, len, time);
}

uint64_t TestPJWHash64(char *str, uint32_t *len, time_t *time){
    printf("INFO : PJWHash64 Test");
    return TestHash64(PJWHash64, str, len, time);
}

uint64_t TestELFHash64(char *str, uint32_t *len, time_t *time){
    printf("INFO : ELFHash64 Test");
    return TestHash64(ELFHash64, str, len, time);
}

uint64_t TestBKDRHash64(char *str, uint32_t *len, time_t *time){
    printf("INFO : BKDRHash64 Test");
    return TestHash64(BKDRHash64, str, len, time);
}

uint64_t TestDJBHash64(char *str, uint32_t *len, time_t *time){
    printf("INFO : DJBHash64 Test");
    return TestHash64(DJBHash64, str, len, time);
}

uint64_t TestAPHash64(char *str, uint32_t *len, time_t *time){
    printf("INFO : APHash64 Test");
    return TestHash64(APHash64, str, len, time);
}

uint32_t TestMurMurHash(char *str, uint32_t len, time_t *time){
    printf("INFO : MurMurHash Test");
    return TestHash(MurmurHash2, str, len, time);
}

uint32_t TestRSHash(char *str, uint32_t *len, time_t *time ){
    printf("INFO : RSHash Test");
    return TestHash(RSHash, str, len, time);
}

uint32_t TestSDBMHash(char *str, uint32_t *len, time_t *time){
    printf("INFO : SDBMHash Test");
    return TestHash(SDBMHash, str, len, time);
}

uint32_t TestJSHash(char *str, uint32_t *len, time_t *time){
    printf("INFO : JSHash64 Test");
    return TestHash(JSHash, str, len, time);
}

uint32_t TestPJWHash(char *str, uint32_t *len, time_t *time){
    printf("INFO : PJWHash Test");
    return TestHash(PJWHash, str, len, time);
}

uint32_t TestELFHash(char *str, uint32_t *len, time_t *time){
    printf("INFO : ELFHash Test");
    return TestHash(ELFHash, str, len, time);
}

uint32_t TestBKDRHash(char *str, uint32_t *len, time_t *time){
    printf("INFO : BKDRHash Test");
    return TestHash(BKDRHash, str, len, time);
}

uint32_t TestDJBHash(char *str, uint32_t *len, time_t *time){
    printf("INFO : DJBHash Test");
    return TestHash(DJBHash, str, len, time);
}

uint32_t TestAPHash(char *str, uint32_t *len, time_t *time){
    printf("INFO : APHash Test");
    return TestHash(APHash, str, len, time);
}

void benchmark(char *name, uint32_t len, time_t time){
   // make stastics for different string length

    printf("INFO : **************************************************");
    printf("INFO : Result of  %s", name);
    printf("INFO : **************************************************");

    //
}

void LoadStringKeys(){

}

void Launch32Test(char *str){

}
void Launch64Test(char *str){

}
void LaunchAllTest(char *str){

}

