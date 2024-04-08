
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hashtable_capacity (1<<27)

static int32_t hashtable[hashtable_capacity];
uint32_t hashtable_hash(int32_t key) {
    key ^= key << 13;
    key ^= key >> 17;
    key ^= key << 5;
    return key % hashtable_capacity;
}
int32_t* hashtable_find(int32_t key) {
    uint32_t hash = hashtable_hash(key);
    return &hashtable[hash];
}

int main() {
}