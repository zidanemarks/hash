//  Copyright (c) 2018-present, Starblaze, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
/*
  All code is released to the public domain. For business purposes, Murmurhash
  is under the MIT license.
*/

#include "include/murmurhash.h"
#include "include/hashmap.h"
#include "include/util.h"
#include "stdio.h"
#include "stdint.h"


int main()
{
    uint64_t hash;
    hash = (uint64_t) HashWrapper("abcdefghijklmn");
    printf("INFO : hash value is %016llx\n", hash);
    hash = (uint64_t) HashWrapper("fdafadasfsdfasdfasdfasdfasdfadfadfadadfsa");
    printf("INFO : hash value is %016llx\n", hash);
    hash = (uint64_t) HashWrapper("fdfadassssssssfdfdf rercrqwcrcerqerqecceqrq");
    printf("INFO : hash value is %016llx\n", hash);
    hash = (uint64_t) HashWrapper("fdgadgvateaaetvwettvtavva");
    printf("INFO : hash value is %016llx\n", hash);
    hash = (uint64_t) HashWrapper("qeuirbvqwunrvo;weurqwv;ermueo;vnmq;runvonveo;rvno;qwvrnuqo;rnvrnuvqr");
    printf("INFO : hash value is %016llx\n", hash);
    return 0;
}
