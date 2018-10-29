
#include <stdint.h>
#include <time.h>
#include "configure.h"

uint32_t RSHash(char *str);

uint32_t SDBMHash(char *str);

uint32_t JSHash(char *str);

uint32_t PJWHash(char *str);

uint32_t ELFHash(char *str);

uint32_t BKDRHash(char *str);

uint32_t DJBHash(char *str);

uint32_t APHash(char *str);

#if defined (__i386__)
  uint32_t HashWrapper(char *str);
#elif defined(__x86_64__)
  uint64_t HashWrapper(char *str);
#endif

uint32_t GetTimeStrapasSeed();