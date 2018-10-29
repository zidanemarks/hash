#include "include/hashmap.h" 
#include "include/murmurhash.h"
#include "include/configure.h"
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>



uint32_t SDBMHash(char *str)
{
    unsigned int hash = 0;

    printf("INFO : SDBHASH\n"); 

    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}
//RShas
uint32_t RSHash(char *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    printf("INFO : RSHASH\n"); 

    while (*str)
    {
        hash = hash * a + (*str++);
        a *= b;
    }

    return (hash & 0x7FFFFFFF);
}

uint32_t JSHash(char *str)
{
    unsigned int hash = 1315423911;

    printf("INFO : JSHASH\n"); 

    while (*str)
    {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }

    return (hash & 0x7FFFFFFF);
}

// P. J. Weinberger Hash Function
uint32_t PJWHash(char *str)
{
    unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters    = (unsigned int)((BitsInUnignedInt  * 3) / 4);
    unsigned int OneEighth        = (unsigned int)(BitsInUnignedInt / 8);
    unsigned int HighBits         = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
    unsigned int hash             = 0;
    unsigned int test             = 0;

    printf("INFO : PJWHASH\n"); 

    while (*str)
    {
        hash = (hash << OneEighth) + (*str++);
        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return (hash & 0x7FFFFFFF);
}

// ELF Hash Function
uint32_t ELFHash(char *str)
{
    unsigned int hash = 0;
    unsigned int x    = 0;

    printf("INFO : ELFHASH\n"); 

    while (*str)
    {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }

    return (hash & 0x7FFFFFFF);
}

// BKDR Hash Function
uint32_t BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    printf("INFO : BKDRHASH\n"); 

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

// DJB Hash Function
uint32_t DJBHash(char *str)
{
    unsigned int hash = 5381;

    printf("INFO : DJBRHASH\n"); 

    while (*str)
    {
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

// AP Hash Function
uint32_t APHash(char *str)
{
    unsigned int hash = 0;
    int i;

    printf("INFO : APHASH\n"); 

    for (i=0; *str; i++)
    {
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }

    return (hash & 0x7FFFFFFF);
}

#if defined (__i386__) 

uint32_t HashWrapper(char *str){

    #if defined MURMURHASH
     uint32_t len=strlen(str);
     return MurmurHash2();
    #elif defined RSHASH  
      return RSHash(str);
    #elif defined SDBMHASH  
      return SDBMHash(str);
    #elif defined JSHASH  
      return JSHash(str);
    #elif defined PJWHASH  
      return PJWHash(str);
    #elif defined ELFHASH  
      return ELFHash(str);
    #elif defined BKDRHASH  
      return BKDRHash(str);
    #elif defined DJBHASH  
      return DJBHash(str);
    #elif defined APHASH  
      return APHash(str);
    #endif


}

#elif defined(__x86_64__)

uint64_t HashWrapper(char *str)
{ 
    uint32_t  result32;

    #if defined MURMURHASH
    uint32_t len = strlen(str);
    uint32_t seed = GetTimeStrapasSeed();
     return MurmurHash64A(str, len, seed);
    #elif defined RSHASH  
      result32 = RSHash(str);
    #elif defined SDBMHASH  
      result32 = SDBMHash(str);
    #elif defined JSHASH  
      result32 = JSHash(str);
    #elif defined PJWHASH  
      result32 = PJWHash(str);
    #elif defined ELFHASH  
      result32 = ELFHash(str);
    #elif defined BKDRHASH  
      result32 = BKDRHash(str);
    #elif defined DJBHASH  
      result32 = DJBHash(str);
    #elif defined APHASH  
      result32 = APHash(str);
    #endif

    return ((result32+1) << 32) & ((result32+2) << 32);

}

#endif

//  set the sum of all time(year, month, day, hours, miniuts, seconds) as the seed
uint32_t GetTimeStrapasSeed(){
    time_t t;
    struct tm *lt;
    time(&t);
    lt = localtime(&t);
    return lt->tm_year+lt->tm_mon+lt->tm_mday+lt->tm_hour+lt->tm_min+lt->tm_sec;
}
