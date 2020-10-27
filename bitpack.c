#include <stdbool.h>
#include <stdint.h>
#include "except.h"
#include "assert.h"
#include "bitpack.h"
#include <math.h>

uint64_t Bitpack_newu(uint64_t word, unsigned width, 
                        unsigned lsb, uint64_t value)
{
    if((width > 64) || (width + lsb > 64) ){
        RAISE(Bitpack_Overflow);
    }
    uint64_t mask = (uint64_t) (pow(2,32) - 1);
    uint64_t mask2 = (uint64_t) (pow(2,width) - 1) << lsb;
    uint64_t mask3 = mask - mask2;
    uint64_t repVal = value << lsb;
    uint64_t repWord = word & mask3;
    uint64_t final = repWord + repVal;
    return final;
}


uint64_t Bitpack_news(uint64_t word, unsigned width, 
                    unsigned lsb, int64_t value)
{
    if((width > 64) || (width + lsb > 64)){
        RAISE(Bitpack_Overflow);
    }
    uint64_t mask = (uint64_t) (pow(2,32) - 1);
    uint64_t mask2 = (uint64_t) (pow(2, width) - 1) << lsb;
    uint64_t masker = mask - mask2;
    uint64_t maskVal = (uint64_t) (pow(2,width) - 1);
    uint64_t repVal = (value & maskVal) << lsb;
    uint64_t repWord = word & masker;
    uint64_t final = repWord + repVal;
    return final; 
}

uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb)
{
    assert(width + lsb <= 64);
    uint64_t mask = (uint64_t) (pow(2,width) - 1) << lsb;
    uint64_t final = (word & mask) >> lsb;
    return final;
}

int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb)
{
    assert(width + lsb <= 64);
    uint64_t mask = (uint64_t) (pow(2,width) - 1) << lsb;
    int64_t final = (word & mask) >> lsb;
    return final;
}

bool Bitpack_fitsu(uint64_t n, unsigned width)
{  
    assert(width <= 64);
    uint64_t lim = pow(2,width) - 1;
    if(n > lim) {
        return false;
    } else {
        return true;
    }

}
bool Bitpack_fitss( int64_t n, unsigned width)
{
    assert(width <= 64);
    int64_t lim = pow(2,width) - 1;
    int64_t nlim = -1 * pow(2,width);
    if(n >= nlim && n <= lim) {
        return true;
    } else {
        return false;
    }
}

