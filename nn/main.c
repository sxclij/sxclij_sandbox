#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string_capacity 1024
#define model_capacity 65536

uint8_t nn_calc_bitcnt(uint64_t x) {
    uint64_t y = x;
    y -= (y >> 1) & 0x5555555555555555;
    y = (y & 0x3333333333333333) + ((y >> 2) & 0x3333333333333333);
    y = ((y + (y >> 4) & 0xF0F0F0F0F0F0F0F) * 0x101010101010101) >> 56;
    return y;
}
uint8_t nn_calc_64_to_1(uint64_t x, const uint64_t* w) {
    uint64_t x_posi = x & w[0];
    uint64_t x_nega = x & w[1];
    uint64_t y_posi = nn_calc_bitcnt(x_posi);
    uint64_t y_nega = nn_calc_bitcnt(x_nega);
    uint8_t y = y_posi > y_nega ? 1 : 0;
}

int main() {
    uint64_t model[model_capacity];
    uint64_t layers = {8,16,1};

}