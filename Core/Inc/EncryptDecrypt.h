/*
 * EncryptDecrypt.h
 *
 *  Created on: Feb 7, 2025
 *      Author: ADMIN
 */

#ifndef INC_ENCRYPTDECRYPT_H_
#define INC_ENCRYPTDECRYPT_H_
#include <stdint.h>
#include <stdio.h>

#define TEA_DELTA 0x9E3779B9
#define TEA_NUM_ROUNDS 32

extern uint32_t key[4];

/*
 * @brief	This function is used for encrypt data
 * @param	data: raw data need to encrypt
 * @param	key: key to encrypt
 * @retval	encrypted data
 * */
uint64_t TEA_encrypt(uint64_t data, uint32_t key[4]);

/*
 * @brief	This function is used for decrypt data
 * @param	data: encrypted data need to decrypt
 * @param	key: key to encrypt
 * @retval	decrypted data
 * */
uint64_t TEA_decrypt(uint64_t data, uint32_t key[4]);

/*
 * @brief	This function is used for padding data
 * @param	data: data need to padding
 * @param	length: length of data
 * @param	paddingData: data after padding
 * @retval	None
 * */
void padData(uint8_t *data, size_t length, uint64_t *paddingData);

/*
 * @brief	This function is used for unpadding data
 * @param	data: data need to unpadding
 * @param	length: length of data
 * @param	paddingData: data after unpadding
 * @retval	None
 * */
void unpadData(uint64_t *paddingData, size_t length, uint8_t *data);

#endif /* INC_ENCRYPTDECRYPT_H_ */
