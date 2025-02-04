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
	UART_HandleTypeDef * uart;
	uint16_t baudrate;
} UART_type_t;

typedef struct {
	I2C_HandleTypeDef * i2c;
	uint32_t address;
} I2C_type_t;

typedef struct {
	SPI_HandleTypeDef * spi;
	uint16_t CPOL;
	uint16_t CPHA;
} SPI_type_t;

typedef struct {
	UART_HandleTypeDef * uart;
	uint32_t baudrate;
	uint32_t address;
} RS485_type_t;

typedef struct {
	UART_type_t * uart_Handler;
	I2C_type_t * i2c_Handler;
	SPI_type_t * spi_Handler;
	RS485_type_t * RS485_Handler;
} BKIT_COM_type_t;

typedef enum {UART, I2C, SPI, RS485} PROTOCOL;

extern uint8_t uart_en, i2c_en, spi_en, RS485_en;
extern BKIT_COM_type_t Com;
extern PROTOCOL Com_Send_Signal;

void hw_init(void);
BKITCOM_Error_Code uart_config(uint8_t uart_x, uint32_t baudrate);
BKITCOM_Error_Code i2c_config(uint8_t i2c_x, uint32_t address);
BKITCOM_Error_Code spi_config(uint8_t spi_x, uint16_t CPOL, uint16_t CPHA);
BKITCOM_Error_Code RS485_config(uint8_t uart_x, uint32_t baudrate, uint32_t address);

BKITCOM_Error_Code hw_send(uint8_t * data, uint32_t data_length);
BKITCOM_Error_Code hw_send_byte(uint8_t data);
BKITCOM_Error_Code hw_receive(uint8_t * data);

BKITCOM_Error_Code HAL_ErrorCode_Handler (HAL_StatusTypeDef Error_Code);
#endif /* INC_HARDWARE_INTERFACE_LAYER_H_ */
