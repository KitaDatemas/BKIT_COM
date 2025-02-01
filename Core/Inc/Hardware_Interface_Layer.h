/*
 * Hardware_Interface_Layer.h
 *
 *  Created on: Jan 31, 2025
 *      Author: ASUS
 */

#ifndef INC_HARDWARE_INTERFACE_LAYER_H_
#define INC_HARDWARE_INTERFACE_LAYER_H_
#include "main.h"
#include "Error_Code.h"


typedef struct {
	UART_HandleTypeDef * uart_x;
	uint16_t baudrate;
} UART_type_t;

typedef struct {
	I2C_HandleTypeDef * i2c_x;
	uint32_t address;
} I2C_type_t;

typedef struct {
	SPI_HandleTypeDef * spi_x;
	uint16_t CPOL;
	uint16_t CPHA;
} SPI_type_t;

typedef struct {
	UART_type_t * uart;
	I2C_type_t * i2c;
	SPI_type_t * spi;
} BKIT_COM_type_t;

void hw_init();
enum error_code hw_send(uint8_t * data, uint32_t data_length);
enum error_code hw_send_byte(uint8_t data);
enum error_code hw_receive(uint8_t * data);

#endif /* INC_HARDWARE_INTERFACE_LAYER_H_ */
