/*
 * EncryptDecrypt.c
 *
 *  Created on: Feb 7, 2025
 *      Author: ADMIN
 */

#include "EncryptDecrypt.h"

  uint8_t key[16] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
                     0xAB, 0xF7, 0xCF, 0x8F, 0xAC, 0x3C, 0x88, 0x92};

void aes_encrypt(uint8_t *input) {
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);
    AES_ECB_encrypt(&ctx, input);
}

void aes_decrypt(uint8_t *input) {
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);
    AES_ECB_decrypt(&ctx, input);
}

