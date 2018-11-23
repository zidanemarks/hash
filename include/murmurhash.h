//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
/*
  Murmurhash from http://sites.google.com/site/murmurhash/

  All code is released to the public domain. For business purposes, Murmurhash
  is under the MIT license.
*/
//#pragma once
#include <stdint.h>
#include <stdio.h>
#include "configure.h"
#include "util.h"

#if 0
#include "slice.h"
#endif

//#if defined(__x86_64__)
#if(1)
#define MURMUR_HASH MurmurHash64A
uint64_t MurmurHash64A ( const void * key, int len, unsigned int seed );
//#define MurmurHash MurmurHash64A
//typedef uint64_t murmur_t;

//#elif defined(__i386__)
#define MURMUR_HASH MurmurHash2
unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed );
//#define MurmurHash MurmurHash2
//typedef unsigned int murmur_t;

#else
#define MURMUR_HASH MurmurHashNeutral2
unsigned int MurmurHashNeutral2 ( const void * key, int len, unsigned int seed );
#define MurmurHash MurmurHashNeutral2
typedef unsigned int murmur_t;
#endif

// Allow slice to be hashable by murmur hash.
#if 0
namespace rocksdb {
struct murmur_hash {
  size_t operator()(const Slice& slice) const {
    return MurmurHash(slice.data(), static_cast<int>(slice.size()), 0);
  }
};
}  // rocksdb
#endif
