/*
 * EncryptDecrypt.h
 *
 *  Created on: Feb 7, 2025
 *      Author: ADMIN
 */

#ifndef INC_ENCRYPTDECRYPT_H_
#define INC_ENCRYPTDECRYPT_H_

#include "main.h"
#include "aes.h"
#include <stdio.h>
#include <string.h>

extern uint8_t key[16];
extern uint8_t temp[16];

void aes_encrypt(uint8_t *input);
void aes_decrypt(uint8_t *input);

#endif /* INC_ENCRYPTDECRYPT_H_ */
