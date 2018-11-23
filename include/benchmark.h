#include <stdint.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <sys/time.h>
//#include <conio.h>
#include <unistd.h>
#include <assert.h>
#include "hashmap.h"
#include "murmurhash.h"
#include "configure.h"
#ifdef _WIN32 
  #include <dirent.h>
  #include <sys/types.h>
#endif


#if defined(__x86_64__)
   typedef uint32_t (*HashHandler)(char *str);
   typedef uint64_t HashStr;
#elif defined(__i386__) 
   typedef uint32_t (*HashHandler)(char *str);
   typedef uint32_t HashStr;
#endif

typedef struct{
    char *str; 
    HashHandler handler;
    double  time[1000];
    uint32_t len[1000];
    char *name;
    HashStr hashstr[1000];
    uint32_t num;
} HashParam;

#if(0)
std::string strArray[] =
{
}
for(auto obj : strarray){
    str_vec.push_back(obj);
}
#endif

typedef char * myType; 
 // testcase pattern files name list 
const myType list[]= {
       "MURMUR",
       "RS",
       "SDBM",
       "JS",
       "PJW",
       "ELF",
       "BKDR",
       "DJB",
       "AP"
   };

char FindHash(char *name);

uint32_t FindPattern(char *files[1000]);

void LoadString(char *name, HashParam *param);


void BenchMark(HashParam *param);

void LoadStringKeys();

void LaunchTest(char *name);

void LaunchAllTest(void);

