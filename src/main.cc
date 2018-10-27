//  Copyright (c) 2018-present, Starblaze, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
/*
  All code is released to the public domain. For business purposes, Murmurhash
  is under the MIT license.
*/

#include "murmurhash.h"
#include "hashmap.h"
#include "util.h"

main()
{
    char *str= "abcdefghijklmn";
    uint64_t hash;
    hash = (uint64_t) HashWrappar(str);
    printf("INFO : hash value is %20x", hash);
    return 0;
}

