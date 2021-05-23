#pragma once

#include <stdint.h>

int bit_one_count(uint32_t n)
{
    unsigned int c = 0 ;
    for (c =0; n; ++c)
        n &= (n -1) ;
    return c ;
}