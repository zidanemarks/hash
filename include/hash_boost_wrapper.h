#pragma once
#include <stdint.h>
#include <iostream>
#include <string.h>
#include "hashmap.h"
#include "murmurhash.h"
#include <boost/python.hpp>
#include <boost/thread/thread.hpp>

uint64_t PyMurmurHash64A(char *str,  int len, unsigned int seed);
uint32_t PyMurmurHash2(char *str,  int len, unsigned int seed);
