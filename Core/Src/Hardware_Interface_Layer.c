/*
 * Hardware_Interface_Layer.c
 *
 *  Created on: Jan 31, 2025
 *      Author: ASUS
 */
#include "Hardware_Interface_Layer.h"

void hw_init(BKIT_COM_type_t * BKIT_COM) {
	if (BKIT_COM->uart != NULL) {

	}
	if (BKIT_COM->i2c != NULL) {
	}
	if (BKIT_COM->spi != NULL) {

	}
}

enum error_code hw_send(uint8_t * data, uint32_t data_length);
enum error_code hw_send_byte(uint8_t data);
enum error_code hw_receive(uint8_t * data);
