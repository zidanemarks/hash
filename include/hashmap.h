
#include <stdint.h>
#include <time.h>

uint32_t RSHash(char *str);

uint32_t SDBMHash(char *str);

uint32_t JSHash(char *str);

uint32_t PJWHash(char *str);

uint32_t ELFHash(char *str);

uint32_t BKDRHash(char *str);

uint32_t DJBHash(char *str);

uint32_t APHash(char *str);

uint64_t Hash64(uint32_t (*func)(), char *str);

uint64_t RSHash64(char *str);

uint64_t SDBMHash64(char *str);

uint64_t JSHash64(char *str);

uint64_t PJWHash64(char *str);

uint64_t ELFHash64(char *str);

uint64_t BKDRHash64(char *str);

uint64_t DJBHash64(char *str);

uint64_t APHash64(char *str);

#if defined (__i386__)
  uint32_t HashWrapper(char *str);
#elif defined(__x86_64__)
  uint64_t HashWrapper(char *str);
#endif

uint32_t GetTimeStrapasSeed();