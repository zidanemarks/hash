#include <stdint.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <io.h>
#include "include/configure.h"
#include <string.h>
#include <assert.h>

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
    double  *time;
    uint32_t *len;
    char *name;
    HashStr hashstr[1000];
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
       "MurMur",
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

void LoadString(char *name, char *str);


void BenchMark(HashParam *param);

void LoadStringKeys();

void LaunchTest(char *name);

void LaunchAllTest(void);

