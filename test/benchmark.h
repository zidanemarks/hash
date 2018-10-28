#include <stdint.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

uint64_t TestHash(uint64_t (*func);();, char *str, uint32_t *len, uint32_t *time);;

uint64_t TestHash64(uint64_t (*func);();, char *str, uint32_t *len, uint32_t *time);

uint64_t TestMurMurHash64(char *str, uint32_t len, time_t *time);

uint64_t TestRSHash64(char *str, uint32_t *len, time_t *time );

uint64_t TestSDBMHash64(char *str, uint32_t *len, time_t *time);

uint64_t TestJSHash64(char *str, uint32_t *len, time_t *time);

uint64_t TestPJWHash64(char *str, uint32_t *len, time_t *time);

uint64_t TestELFHash64(char *str, uint32_t *len, time_t *time);

uint64_t TestBKDRHash64(char *str, uint32_t *len, time_t *time);

uint64_t TestDJBHash64(char *str, uint32_t *len, time_t *time);

uint64_t TestAPHash64(char *str, uint32_t *len, time_t *time);

uint32_t TestMurMurHash(char *str, uint32_t *len, time_t *time);

uint32_t TestTestRSHash(char *str, uint32_t *len, time_t *time);

uint32_t TestSDBMHash(char *str, uint32_t *len, time_t *time);

uint32_t TestJSHash(char *str, uint32_t *len, time_t *time);

uint32_t TestPJWHash(char *str, uint32_t *len, time_t *time);

uint32_t TestELFHash(char *str, uint32_t *len, time_t *time);

uint32_t TestBKDRHash(char *str, uint32_t *len, time_t *time);

uint32_t TestDJBHash(char *str, uint32_t *len, time_t *time);

uint32_t TestAPHash(char *str, uint32_t *len, time_t *time);

void benchmark(char *name, uint32_t len, time_t time);

void LoadStringKeys();

void Launch32Test(char *str);

void Launch64Test(char *str);

void LaunchAllTest(char *str);

