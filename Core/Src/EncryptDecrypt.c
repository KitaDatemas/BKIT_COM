/*
 * EncryptDecrypt.c
 *
 *  Created on: Feb 7, 2025
 *      Author: ADMIN
 */

#include "EncryptDecrypt.h"

uint32_t key[4] = {0xA56BABCD, 0x0000FFFF, 0x12345678, 0x87654321};

uint64_t TEA_encrypt(uint64_t data, uint32_t key[4]) {
    uint32_t v0 = (uint32_t)(data >> 32);
    uint32_t v1 = (uint32_t)(data & 0xFFFFFFFF);
    uint32_t sum = 0;

    for (int i = 0; i < TEA_NUM_ROUNDS; i++) {
        sum += TEA_DELTA;
        v0 += ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        v1 += ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
    }

    return ((uint64_t)v0 << 32) | v1;
}

uint64_t TEA_decrypt(uint64_t data, uint32_t key[4]) {
	uint32_t v0 = (uint32_t)(data >> 32);
    uint32_t v1 = (uint32_t)(data & 0xFFFFFFFF);
    uint32_t sum = TEA_DELTA * TEA_NUM_ROUNDS;
    for (int i = 0; i < TEA_NUM_ROUNDS; i++) {
        v1 -= ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
        v0 -= ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        sum -= TEA_DELTA;
    }
     return ((uint64_t)v0 << 32) | v1;
}

void padData(uint8_t *data, size_t length, uint64_t *paddingData) {
    for (size_t i = 0; i < length; i++) {
        paddingData[i] = (uint64_t)data[i];
    }
}

void unpadData(uint64_t *paddingData, size_t length, uint8_t *data) {
    for (size_t i = 0; i < length; i++) {
        data[i] = (uint8_t)(paddingData[i] & 0xFF);  // Lấy byte cuối cùng
    }
}


