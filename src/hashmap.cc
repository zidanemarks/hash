#include "hashmap.h" 
#include "murmurhash.h"
#include "configure.h"
#include <string>
#include <time.h>

uint32_ SDBMHash(char *str)
{
    unsigned int hash = 0;

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

uint32_t HashWrapper32(char *str){

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

uint64_t HashWrapper64(char *str)
{ 
    uint32_t  result32;

    #if defined MURMURHASH
    uint32_t len = strlen()
    uint32_t
     return MurmurHash64A
    #elif defined RSHASH  
      result32 = RSHash(*str);
    #elif defined SDBMHASH  
      result32 = SDBMHash(str);
    #elif defined JSHASH  
      result32 = JSHash(str);
    #elif defined PJWHASH  
      result32 = PJWHash();
    #elif defined ELFHASH  
      result32 = ELFHash();
    #elif defined BKDRHASH  
      result32 = BKDRHash();
    #elif defined DJBHASH  
      result32 = DJBHash();
    #elif defined APHASH  
      result32 = APHash();
    #endif

    return ((result32+1) << 32) & ((result32+2) << 32);

}




