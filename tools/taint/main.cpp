//
// Created by uthpala on 9/20/18.
//

#include <blocksci/blocksci.hpp>
#include <blocksci/address/address.hpp>
#include <blocksci/cluster/cluster_manager.hpp>
#include <blocksci/chain/transaction.hpp>
#include <blocksci/heuristics/taint.hpp>
#include <blocksci/chain/blockchain.hpp>


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

#include <vector>
#include <array>

#include <functional>
#include <iostream>
#include <assert.h>

using namespace std::chrono;
/*
typedef enum {
    CUCKOO_FILTER_OK = 0,
    CUCKOO_FILTER_NOT_FOUND = 1,
    CUCKOO_FILTER_FULL = 2,
    CUCKOO_FILTER_ALLOCATION_FAILED = 3,
} CUCKOO_FILTER_RETURN;

typedef struct cuckoo_filter_t cuckoo_filter_t;

CUCKOO_FILTER_RETURN
cuckoo_filter_new (
        cuckoo_filter_t     **filter,
        size_t                max_key_count,
        size_t                max_kick_attempts,
        uint32_t              seed
);

CUCKOO_FILTER_RETURN
cuckoo_filter_free (
        cuckoo_filter_t     **filter
);

CUCKOO_FILTER_RETURN
cuckoo_filter_add (
        cuckoo_filter_t      *filter,
        void                 *key,
        size_t                key_length_in_bytes
);

CUCKOO_FILTER_RETURN
cuckoo_filter_remove (
        cuckoo_filter_t      *filter,
        void                 *key,
        size_t                key_length_in_bytes
);

CUCKOO_FILTER_RETURN
cuckoo_filter_contains (
        cuckoo_filter_t      *filter,
        void                 *key,
        size_t                key_length_in_bytes
);


#define CUCKOO_NESTS_PER_BUCKET     4

static inline uint32_t murmurhash (const void *, uint32_t, uint32_t);
static inline uint32_t hash (const void *, uint32_t, uint32_t, uint32_t,
                             uint32_t);

typedef struct {
    uint16_t              fingerprint;
} __attribute__((packed)) cuckoo_nest_t;

typedef struct {
    uint32_t              fingerprint;
    uint32_t              h1;
    uint32_t              h2;
    uint32_t              padding;
} __attribute__((packed)) cuckoo_item_t;

typedef struct {
    bool                  was_found;
    cuckoo_item_t         item;
} cuckoo_result_t;

struct cuckoo_filter_t {
    uint32_t              bucket_count;
    uint32_t              nests_per_bucket;
    uint32_t              mask;
    uint32_t              max_kick_attempts;
    uint32_t              seed;
    uint32_t              padding;
    cuckoo_item_t         victim;
    cuckoo_item_t        *last_victim;
    cuckoo_nest_t         bucket[1];
} __attribute__((packed));

*/

/* ------------------------------------------------------------------------- */
/*
static inline size_t
next_power_of_two (size_t x) {
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    if (8 == sizeof(size_t)) {
        x |= x >> 32;
    }

    return ++x;
}
*/
/* ------------------------------------------------------------------------- */
/*
static inline CUCKOO_FILTER_RETURN
add_fingerprint_to_bucket (
        cuckoo_filter_t      *filter,
        uint32_t              fp,
        uint32_t              h
) {
    fp &= filter->mask;
    for (size_t ii = 0; ii < filter->nests_per_bucket; ++ii) {
        cuckoo_nest_t *nest =
                &filter->bucket[((h - 1) * filter->nests_per_bucket) + ii];
        if (0 == nest->fingerprint) {
            nest->fingerprint = fp;
            return CUCKOO_FILTER_OK;
        }
    }

    return CUCKOO_FILTER_FULL;

} *//* add_fingerprint_to_bucket() */
/* ------------------------------------------------------------------------- */
/*
static inline CUCKOO_FILTER_RETURN
remove_fingerprint_from_bucket (
        cuckoo_filter_t      *filter,
        uint32_t              fp,
        uint32_t              h
) {
    fp &= filter->mask;
    for (size_t ii = 0; ii < filter->nests_per_bucket; ++ii) {
        cuckoo_nest_t *nest =
                &filter->bucket[((h - 1) * filter->nests_per_bucket) + ii];
        if (fp == nest->fingerprint) {
            nest->fingerprint = 0;
            return CUCKOO_FILTER_OK;
        }
    }


    return CUCKOO_FILTER_NOT_FOUND;

}*/ /* remove_fingerprint_from_bucket() */

/* ------------------------------------------------------------------------- */
/*
static inline CUCKOO_FILTER_RETURN
cuckoo_filter_move (
        cuckoo_filter_t      *filter,
        uint32_t              fingerprint,
        uint32_t              h1,
        int                   depth
) {
    uint32_t h2 = ((h1 ^ hash(&fingerprint, sizeof(fingerprint),
                              filter->bucket_count, 900, filter->seed)) % filter->bucket_count);

    if (CUCKOO_FILTER_OK == add_fingerprint_to_bucket(filter,
                                                      fingerprint, h1)) {
        return CUCKOO_FILTER_OK;
    }

    if (CUCKOO_FILTER_OK == add_fingerprint_to_bucket(filter,
                                                      fingerprint, h2)) {
        return CUCKOO_FILTER_OK;
    }

    printf("depth = %u\n", depth);
    if (filter->max_kick_attempts == depth) {
        return CUCKOO_FILTER_FULL;
    }

    size_t row = (0 == (rand() % 2) ? h1 : h2);
    size_t col = (rand() % filter->nests_per_bucket);
    size_t elem =
            filter->bucket[((row - 1) * filter->nests_per_bucket) + col].fingerprint;
    filter->bucket[((row - 1) * filter->nests_per_bucket) + col].fingerprint =
            fingerprint;
    //printf("row, %u\n", row );
    //printf(" column %u\n", col );
    //printf("elem = %u\n", elem);
    return cuckoo_filter_move(filter, elem, row, (depth + 1));

} *//* cuckoo_filter_move() */

/* ------------------------------------------------------------------------- */
/*

CUCKOO_FILTER_RETURN
cuckoo_filter_new (
        cuckoo_filter_t     **filter,
        size_t                max_key_count,
        size_t                max_kick_attempts,
        uint32_t              seed
) {
    cuckoo_filter_t      *new_filter;

    size_t bucket_count =
            next_power_of_two(max_key_count / CUCKOO_NESTS_PER_BUCKET);
    if (0.96 < (double) max_key_count / bucket_count / CUCKOO_NESTS_PER_BUCKET) {
        bucket_count <<= 1;
    }

    size_t allocation_in_bytes = (sizeof(cuckoo_filter_t)
                                  + (bucket_count * CUCKOO_NESTS_PER_BUCKET * sizeof(cuckoo_nest_t)));

    if (0 != posix_memalign((void **) &new_filter, sizeof(uint64_t),
                            allocation_in_bytes)) {
        return CUCKOO_FILTER_ALLOCATION_FAILED;
    }

    memset(new_filter, 0, allocation_in_bytes);

    new_filter->last_victim = NULL;
    memset(&new_filter->victim, 0, sizeof(new_filter)->victim);
    new_filter->bucket_count = bucket_count;
    new_filter->nests_per_bucket = CUCKOO_NESTS_PER_BUCKET;
    new_filter->max_kick_attempts = max_kick_attempts;
    new_filter->seed = (size_t) time(NULL);
    //new_filter->seed = (size_t) 10301212;
    new_filter->mask = (uint32_t) ((1U << (sizeof(cuckoo_nest_t) * 8)) - 1);

    *filter = new_filter;

    return CUCKOO_FILTER_OK;

}*/ /* cuckoo_filter_new() */

/* ------------------------------------------------------------------------- */
/*
CUCKOO_FILTER_RETURN
cuckoo_filter_free (
        cuckoo_filter_t     **filter
) {
    free(*filter);
    *filter = NULL;

    return CUCKOO_FILTER_OK;
}
*/
/* ------------------------------------------------------------------------- */
/*
static inline CUCKOO_FILTER_RETURN
cuckoo_filter_lookup (
        cuckoo_filter_t      *filter,
        cuckoo_result_t      *result,
        void                 *key,
        size_t                key_length_in_bytes
) {
    uint32_t fingerprint = hash(key, key_length_in_bytes, filter->bucket_count,
                                1000, filter->seed);
    uint32_t h1 = hash(key, key_length_in_bytes, filter->bucket_count, 0,
                       filter->seed);
    uint32_t h2 = ((h1 ^ hash(&fingerprint, sizeof(fingerprint),
                              filter->bucket_count, 900, filter->seed)) % filter->bucket_count);

    result->was_found = false;
    result->item.fingerprint = 0;
    result->item.h1 = 0;
    result->item.h2 = 0;

    fingerprint &= filter->mask;
    for (size_t ii = 0; ii < filter->nests_per_bucket; ++ii) {
        cuckoo_nest_t *n1 =
                //&filter->bucket[(h1 * filter->nests_per_bucket) + ii];
        &filter->bucket[((h1 - 1) * filter->nests_per_bucket) + ii];
        if (fingerprint == n1->fingerprint) {
            result->was_found = true;
            break;
        }

        cuckoo_nest_t *n2 =
                //&filter->bucket[(h2 * filter->nests_per_bucket) + ii];
        &filter->bucket[((h2 - 1) * filter->nests_per_bucket) + ii];
        if (fingerprint == n2->fingerprint) {
            result->was_found = true;
            break;
        }
    }

    result->item.fingerprint = fingerprint;
    result->item.h1 = h1;
    result->item.h2 = h2;
  //  printf("hiii this is lookup %u\n",result->was_found);
    return ((true == result->was_found)
            ? CUCKOO_FILTER_OK : CUCKOO_FILTER_NOT_FOUND);

}*/ /* cuckoo_filter_lookup() */

/* ------------------------------------------------------------------------- */
/*
CUCKOO_FILTER_RETURN
cuckoo_filter_add (
        cuckoo_filter_t      *filter,
        void                 *key,
        size_t                key_length_in_bytes
) {
    cuckoo_result_t   result;

    cuckoo_filter_lookup(filter, &result, key, key_length_in_bytes);
    if (true == result.was_found) {
        return CUCKOO_FILTER_OK;
    }


    if (NULL != filter->last_victim) {
        return CUCKOO_FILTER_FULL;
    }

    return cuckoo_filter_move(filter, result.item.fingerprint, result.item.h1,
                              0);

} *//* cuckoo_filter_add() */

/* ------------------------------------------------------------------------- */
/*
CUCKOO_FILTER_RETURN
cuckoo_filter_remove (
        cuckoo_filter_t      *filter,
        void                 *key,
        size_t                key_length_in_bytes
) {
    cuckoo_result_t   result;
    bool              was_deleted = false;

    cuckoo_filter_lookup(filter, &result, key, key_length_in_bytes);
    if (false == result.was_found) {
        return CUCKOO_FILTER_NOT_FOUND;
    }

    if (CUCKOO_FILTER_OK == remove_fingerprint_from_bucket(filter,
                                                           result.item.fingerprint, result.item.h1)) {
        was_deleted = true;
    } else if (CUCKOO_FILTER_OK == remove_fingerprint_from_bucket(filter,
                                                                  result.item.fingerprint, result.item.h2)) {
        was_deleted = true;
    }

    if ((true == was_deleted) & (NULL != filter->last_victim)) {

    }

    return ((true == was_deleted) ? CUCKOO_FILTER_OK : CUCKOO_FILTER_NOT_FOUND);

} *//* cuckoo_filter_remove() */

/* ------------------------------------------------------------------------- */
/*
CUCKOO_FILTER_RETURN
cuckoo_filter_contains (
        cuckoo_filter_t      *filter,
        void                 *key,
        size_t                key_length_in_bytes
) {
    cuckoo_result_t   result;

    return cuckoo_filter_lookup(filter, &result, key, key_length_in_bytes);

}*/ /* cuckoo_filter_contains() */

/* ------------------------------------------------------------------------- */
/*
static inline uint32_t
murmurhash (
        const void           *key,
        uint32_t              key_length_in_bytes,
        uint32_t              seed
) {
    uint32_t              c1 = 0xcc9e2d51;
    uint32_t              c2 = 0x1b873593;
    uint32_t              r1 = 15;
    uint32_t              r2 = 13;
    uint32_t              m = 5;
    uint32_t              n = 0xe6546b64;
    uint32_t              h = 0;
    uint32_t              k = 0;
    uint8_t              *d = (uint8_t *) key;
    const uint32_t       *chunks = NULL;
    const uint8_t        *tail = NULL;
    int                   i = 0;
    int                   l = (key_length_in_bytes / sizeof(uint32_t));

    h = seed;

    chunks = (const uint32_t *) (d + l * sizeof(uint32_t));
    tail = (const uint8_t *) (d + l * sizeof(uint32_t));

    for (i = -l; i != 0; ++i) {
        k = chunks[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;
        h ^= k;
        h = (h << r2) | (h >> (32 - r2));
        h = h * m + n;
    }

    k = 0;
    switch (key_length_in_bytes & 3) {
        case 3: k ^= (tail[2] << 16);
        case 2: k ^= (tail[1] << 8);
        case 1:
            k ^= tail[0];
            k *= c1;
            k = (k << r1) | (k >> (32 - r1));
            k *= c2;
            h ^= k;
    }

    h ^= key_length_in_bytes;
    h ^= (h >> 16);
    h *= 0x85ebca6b;
    h ^= (h >> 13);
    h *= 0xc2b2ae35;
    h ^= (h >> 16);

    return h;

}*/ /* murmurhash() */

/* ------------------------------------------------------------------------- */
/*
static inline uint32_t
hash (
        const void           *key,
        uint32_t              key_length_in_bytes,
        uint32_t              size,
        uint32_t              n,
        uint32_t              seed
) {
    uint32_t h1 = murmurhash(key, key_length_in_bytes, seed);
    uint32_t h2 = murmurhash(key, key_length_in_bytes, h1);

    return ((h1 + (n * h2)) % size);

}
*/
//using namespace blocksci::heuristics;


//#include "MurmurHash3.h"
void MurmurHash3_x64_128(const void *key, int len, uint32_t seed, void *out)
{
    // emulate MurmurHash3_x64_128
    size_t h = std::hash<std::string>()(std::string((const char*)key, len));
    size_t *s = reinterpret_cast<size_t*>(out);
    for (int i = 0; i < 128; i += 8*sizeof(size_t))
        *s++ = h;
}

//basic structure of a bloom filter object
struct BloomFilter {
    BloomFilter(size_t size, uint8_t numHashes);
    void add(const uint8_t *data, std::size_t len);
    bool possiblyContains(const uint8_t *data, std::size_t len) const;
private:
    uint8_t m_numHashes;
    std::vector<bool> m_bits;
};
//Bloom filter constructor
BloomFilter::BloomFilter(size_t size, uint8_t numHashes)
    : m_bits(size),
    m_numHashes(numHashes) {}
//Hash array created using the MurmurHash3 code
static std::array<uint64_t, 2> myhash(const uint8_t *data, std::size_t len)
{
    std::array<uint64_t, 2> hashValue;
    MurmurHash3_x64_128(data, len, 0, hashValue.data());
    return hashValue;
}
//Hash array created using the MurmurHash3 code
inline size_t nthHash(int n,
    uint64_t hashA,
    uint64_t hashB,
    size_t filterSize) {
    return (hashA + n * hashB) % filterSize; // <- not sure if that is OK, perhaps it is.
}
//Adds an element to the array
void BloomFilter::add(const uint8_t *data, std::size_t len) {
    auto hashValues = myhash(data, len);
    for (int n = 0; n < m_numHashes; n++)
    {
        m_bits[nthHash(n, hashValues[0], hashValues[1], m_bits.size())] = true;
    }
}
//Returns true or false based on a probabilistic assesment of the array         using MurmurHash3
bool BloomFilter::possiblyContains(const uint8_t *data, std::size_t   len) const {
    auto hashValues = myhash(data, len);
    for (int n = 0; n < m_numHashes; n++)
    {
        if (!m_bits[nthHash(n, hashValues[0], hashValues[1], m_bits.size())])
        {
            return false;
        }
    }
    return true;
}

int main() {
   
    blocksci::Blockchain chain("/root/bitcoin-data");
    std::ifstream myFile;
   // cuckoo_filter_t  *filter;
   BloomFilter bf(1024 * 1024,34);
    //bool rc;

    //rc =  cuckoo_filter_new(&filter, 500000000, 300, (uint32_t) (time(NULL) & 0xffffffff));
  /*  myFile.open("/root/BlockSci/tools/taint/data.csv");

     

    std::string input;

    while(myFile.good()){
        getline(myFile,input,'\n');
        std::cout<<"hash  "<< input<<myFile.good()<<std::endl;
        auto root = blocksci::Transaction(input, chain.getAccess());
       */ auto num = 1;

      ////////////////////////////////////////////////////////////// 
    //time in bloom filter
    //auto root = blocksci::Transaction("1e8df21db15a9573b346db5d9c9458c58af357b58abc8f198e4b4c1e884c7cf8", chain.getAccess());//2017.12.18  921.7 seconds in bloom filter
    //auto root = blocksci::Transaction("fa2c927ffeb2750e6c0898b5f4140df1a7fc886d4d95e8f53a58d7f713f31c10", chain.getAccess());//2012.09.22  51768 seconds in bloom filter num=54787366
     //auto root = blocksci::Transaction("fff2525b8931402dd09222c50775608f75787bd2b87e56995a7bdd30f79702c4", chain.getAccess()); // address from 2010.12.29 took around    microseconds
      //auto root = blocksci::Transaction("10f072e631081ad6bcddeabb90bc34d787fe7d7116fe0298ff26c50c5e21bfea", chain.getAccess()); // address from 2009.01.27 took around   16522647 microseconds num=0

////////////////////////////////////////////////////////////////////////////
    //Time to get unspent transavctions In poison


   

   // auto root = blocksci::Transaction("e9d168adf7118de3c0fb7888f6a696c6fa7825dea5cb7746eb8ffdf5e12fb831", chain.getAccess());//2018.03.21   457948 microseconds num =2
  // auto root = blocksci::Transaction("1e8df21db15a9573b346db5d9c9458c58af357b58abc8f198e4b4c1e884c7cf8", chain.getAccess());//address from 2017.12.18 took about 2390750296 microseconds num=13351854

   // auto root = blocksci::Transaction("e58bff4fbb6d5d4d425b20367f888846d6499722b425251fd241df4d450777ef", chain.getAccess()); // address from 2018.01.20  18977142 microseconds num=1349568
   // auto root = blocksci::Transaction("3655a9fb3fd9788e17478f667d1f264522425df858ef163ebef3843f4eff0b3e", chain.getAccess()); // address from 2016.02.25   44345279529 microseonds num=14609208
    //auto root = blocksci::Transaction("6e3b2b7196f0ce40a0560633e45c71313e3722b7825d20192b465b5567a244d1", chain.getAccess()); // address from 2015.03.30 took around 20124276 microseconds num=3
    //auto root = blocksci::Transaction("32e19411618c67afc97dc6ecb188d9d3a7c179ba652191f52d019a1db85eaa39", chain.getAccess()); // address from 2014.04.05 took around  7535225361 microseconds  num=22946544
   // auto root = blocksci::Transaction("fa2c927ffeb2750e6c0898b5f4140df1a7fc886d4d95e8f53a58d7f713f31c10", chain.getAccess()); // address from 2012.09.22 took around   18329035879 microseconds num=54787366
    //auto root = blocksci::Transaction("8d30eb0f3e65b8d8a9f26f6f73fc5aafa5c0372f9bb38aa38dd4c9dd1933e090", chain.getAccess()); // address from 2011.10.20 took around  16698866 microseconds num=1
    auto root = blocksci::Transaction("fff2525b8931402dd09222c50775608f75787bd2b87e56995a7bdd30f79702c4", chain.getAccess()); // address from 2010.12.29 took around   7623450349 microseconds num=28101002
    //auto root = blocksci::Transaction("ac3e686574072f5fe09e6c190d5ad365613833bbdf2ad8295e43468631132cd9", chain.getAccess()); // address from 2009.10.14 took around   18826931   microseconds num=0
   // auto root = blocksci::Transaction("10f072e631081ad6bcddeabb90bc34d787fe7d7116fe0298ff26c50c5e21bfea", chain.getAccess()); // address from 2009.01.27 took around   870072 microseconds num=0 


    //////////////////////////////////////////////////////////////////////////////

    //Time to get unspent transavctions In haircut


   

    //auto root = blocksci::Transaction("e9d168adf7118de3c0fb7888f6a696c6fa7825dea5cb7746eb8ffdf5e12fb831", chain.getAccess());//2018.03.21   315833 microseconds num =2
   //auto root = blocksci::Transaction("1e8df21db15a9573b346db5d9c9458c58af357b58abc8f198e4b4c1e884c7cf8", chain.getAccess());//address from 2017.12.18 took about 72538799 microseconds num=9341

    //auto root = blocksci::Transaction("e58bff4fbb6d5d4d425b20367f888846d6499722b425251fd241df4d450777ef", chain.getAccess()); // address from 2018.01.20  27806749 microseconds num=5057
    //auto root = blocksci::Transaction("3655a9fb3fd9788e17478f667d1f264522425df858ef163ebef3843f4eff0b3e", chain.getAccess()); // address from 2016.02.25   122470558 microseonds num=559
   // auto root = blocksci::Transaction("6e3b2b7196f0ce40a0560633e45c71313e3722b7825d20192b465b5567a244d1", chain.getAccess()); // address from 2015.03.30 took around 876156 microseconds num=3
   // auto root = blocksci::Transaction("32e19411618c67afc97dc6ecb188d9d3a7c179ba652191f52d019a1db85eaa39", chain.getAccess()); // address from 2014.04.05 took around  1222068283 microseconds  num=56818
    //auto root = blocksci::Transaction("fa2c927ffeb2750e6c0898b5f4140df1a7fc886d4d95e8f53a58d7f713f31c10", chain.getAccess()); // address from 2012.09.22 took around   1222068283 microseconds num=5129511
    //auto root = blocksci::Transaction("8d30eb0f3e65b8d8a9f26f6f73fc5aafa5c0372f9bb38aa38dd4c9dd1933e090", chain.getAccess()); // address from 2011.10.20 took around  17355233 microseconds num=1
    //auto root = blocksci::Transaction("fff2525b8931402dd09222c50775608f75787bd2b87e56995a7bdd30f79702c4", chain.getAccess()); // address from 2010.12.29 took around   2476659072 microseconds num=390030
    //auto root = blocksci::Transaction("ac3e686574072f5fe09e6c190d5ad365613833bbdf2ad8295e43468631132cd9", chain.getAccess()); // address from 2009.10.14 took around   7387732   microseconds num=0                                                                                                                                                                                                         
    //auto root = blocksci::Transaction("10f072e631081ad6bcddeabb90bc34d787fe7d7116fe0298ff26c50c5e21bfea", chain.getAccess()); // address from 2009.01.27 took around   671876 microseconds num=0 
/////////////////////////////////////////////////////////////////////////////////////////////////////

    //Time to get unspent transavctions In FIFO


   

    //auto root = blocksci::Transaction("e9d168adf7118de3c0fb7888f6a696c6fa7825dea5cb7746eb8ffdf5e12fb831", chain.getAccess());//2018.03.21   853753 microseconds num =2
  // auto root = blocksci::Transaction("1e8df21db15a9573b346db5d9c9458c58af357b58abc8f198e4b4c1e884c7cf8", chain.getAccess());//address from 2017.12.18 took about 72538799 microseconds num=9341

   // auto root = blocksci::Transaction("e58bff4fbb6d5d4d425b20367f888846d6499722b425251fd241df4d450777ef", chain.getAccess()); // address from 2018.01.20  27806749 microseconds num=5057
    //auto root = blocksci::Transaction("3655a9fb3fd9788e17478f667d1f264522425df858ef163ebef3843f4eff0b3e", chain.getAccess()); // address from 2016.02.25   122470558 microseonds num=559
   // auto root = blocksci::Transaction("6e3b2b7196f0ce40a0560633e45c71313e3722b7825d20192b465b5567a244d1", chain.getAccess()); // address from 2015.03.30 took around  1092490 microseconds num=3
   // auto root = blocksci::Transaction("32e19411618c67afc97dc6ecb188d9d3a7c179ba652191f52d019a1db85eaa39", chain.getAccess()); // address from 2014.04.05 took around  1222068283 microseconds  num=56818
    //auto root = blocksci::Transaction("fa2c927ffeb2750e6c0898b5f4140df1a7fc886d4d95e8f53a58d7f713f31c10", chain.getAccess()); // address from 2012.09.22 took around   1222068283 microseconds num=5129511
    //auto root = blocksci::Transaction("8d30eb0f3e65b8d8a9f26f6f73fc5aafa5c0372f9bb38aa38dd4c9dd1933e090", chain.getAccess()); // address from 2011.10.20 took around  17355233 microseconds num=1
    //auto root = blocksci::Transaction("fff2525b8931402dd09222c50775608f75787bd2b87e56995a7bdd30f79702c4", chain.getAccess()); // address from 2010.12.29 took around   2476659072 microseconds num=390030
    //auto root = blocksci::Transaction("ac3e686574072f5fe09e6c190d5ad365613833bbdf2ad8295e43468631132cd9", chain.getAccess()); // address from 2009.10.14 took around   7387732   microseconds num=0                                                                                                                                                                                                         
    //auto root = blocksci::Transaction("10f072e631081ad6bcddeabb90bc34d787fe7d7116fe0298ff26c50c5e21bfea", chain.getAccess()); // address from 2009.01.27 took around   870072 microseconds num=0 

    auto t= 0;

        if (root.outputCount() > 0) {
            auto count = root.outputCount();

            for (auto i = 0; i < count; i++) {
                if ((root.outputs()[i].getType() == blocksci::AddressType::PUBKEYHASH) || (root.outputs()[i].getType() == blocksci::AddressType::WITNESS_PUBKEYHASH)){
                    auto tainted = blocksci::heuristics::getPoisonTainted(root.outputs()[i], root.outputs()[i].getValue());
                    for (auto taints:tainted) {
                        auto pubkey = taints.first.getAddress().getScript().toString();
                        auto pubkeyHash =  pubkey.substr(18,34);
                        std::cout<<pubkeyHash<<"  num:"<<num<<std::endl;
                        //bool rc1;
                        //rc1 = cuckoo_filter_add(filter,const_cast<char*>(pubkeyHash.c_str()),34);
                        //std::cout<<"rc1: "<<rc1<<"    "<<pubkeyHash<<"    "<<"number : "<<num<<std::endl;
                        auto start = high_resolution_clock::now();
                        bf.add((uint8_t*)pubkeyHash.c_str(), pubkeyHash.size());
                        auto stop = high_resolution_clock::now();
                        auto duration = duration_cast<microseconds>(stop - start);
                        t=t+duration.count();

                        std::cout<<duration.count() << "Time taken for Poison tainted : "<< t << " microseconds" << std::endl;
                        //bool possiblyContains  = bf.possiblyContains((uint8_t*)pubkeyHash.c_str(), pubkeyHash.size());
                        //std::cout << "possible: " << possiblyContains <<" num :"<<num<< std::endl;
                       // assert(possiblyContains);
                        num++;
                 }
            }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
        }

    }

  // }
   // myFile.close();
/*
    //auto root = blocksci::Transaction("e9d168adf7118de3c0fb7888f6a696c6fa7825dea5cb7746eb8ffdf5e12fb831", chain.getAccess());//2018.03.21
   //auto root = blocksci::Transaction("1e8df21db15a9573b346db5d9c9458c58af357b58abc8f198e4b4c1e884c7cf8", chain.getAccess());//address from 2017.12.18 took about 889 seconds for posion tainted

    //auto root = blocksci::Transaction("e58bff4fbb6d5d4d425b20367f888846d6499722b425251fd241df4d450777ef", chain.getAccess()); // address from 2018.01.20
    //auto root = blocksci::Transaction("3655a9fb3fd9788e17478f667d1f264522425df858ef163ebef3843f4eff0b3e", chain.getAccess()); // address from 2016.02.25
    //auto root = blocksci::Transaction("6e3b2b7196f0ce40a0560633e45c71313e3722b7825d20192b465b5567a244d1", chain.getAccess()); // address from 2015.03.30 took around 20600595 microseconds
    //auto root = blocksci::Transaction("32e19411618c67afc97dc6ecb188d9d3a7c179ba652191f52d019a1db85eaa39", chain.getAccess()); // address from 2014.04.05 took around  6637358384 microseconds
    //auto root = blocksci::Transaction("fa2c927ffeb2750e6c0898b5f4140df1a7fc886d4d95e8f53a58d7f713f31c10", chain.getAccess()); // address from 2012.09.22 took around   17723294801 microseconds
   // auto root = blocksci::Transaction("8d30eb0f3e65b8d8a9f26f6f73fc5aafa5c0372f9bb38aa38dd4c9dd1933e090", chain.getAccess()); // address from 2011.10.20 took around  14436324  microseconds
   // auto root = blocksci::Transaction("fff2525b8931402dd09222c50775608f75787bd2b87e56995a7bdd30f79702c4", chain.getAccess()); // address from 2010.12.29 took around   7497978860 microseconds
    //auto root = blocksci::Transaction("ac3e686574072f5fe09e6c190d5ad365613833bbdf2ad8295e43468631132cd9", chain.getAccess()); // address from 2009.10.14 took around   13235126  microseconds
    //auto root = blocksci::Transaction("10f072e631081ad6bcddeabb90bc34d787fe7d7116fe0298ff26c50c5e21bfea", chain.getAccess()); // address from 2009.01.27 took around   13235126  microseconds

    std::cout<<root<<std::endl;
*/

    
    
   // bool rc5;
    //rc5 = cuckoo_filter_contains(filter,const_cast<char*>("1PAwW5WiRwoqiBC3DBfWh81ZJkmrP5iq7X"), 34);
    //std::cout<<"rc5 is "<<rc5<<std::endl;

    


}