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
#include "softwareTimer.h"

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
	UART_type_t *uart_Handler;
	I2C_type_t *i2c_Handler;
	SPI_type_t *spi_Handler;
	RS485_type_t *RS485_Handler;
} BKIT_COM_type_t;

typedef enum {NONE, UART, I2C, SPI, RS485} Protocol;
typedef enum {IDLE, VERI_SENDING, VERI_RECEIVING, ERROR_STATE} HIL_State;

extern uint8_t uart_en, i2c_en, spi_en, RS485_en;
extern BKIT_COM_type_t Com;
extern BKITCOM_Error_Code code;
extern Protocol Com_Send_Signal;
extern Protocol Com_Receive_Signal;

extern uint8_t Received_Buffer [50];
extern char Received_Buffer_Flag;

extern HIL_State state;

BKITCOM_Error_Code uart_config(uint8_t uart_x, uint32_t baudrate);
BKITCOM_Error_Code i2c_config(uint8_t i2c_x, uint32_t address);
BKITCOM_Error_Code spi_config(uint8_t spi_x, uint16_t CPOL, uint16_t CPHA);
BKITCOM_Error_Code RS485_config(uint8_t uart_x, uint32_t baudrate, uint32_t address);

void i2c_init(void);
void spi_init(void);
void uart_init(void);
void RS485_init(void);
void hw_init(void);

void hw_reboot(Protocol com);

BKITCOM_Error_Code hw_send(Protocol com, uint8_t * data, uint32_t data_length);
BKITCOM_Error_Code hw_receive(uint8_t * data);

BKITCOM_Error_Code ErrorCode_Handler (HAL_StatusTypeDef Error_Code);

void Hardware_Interface_Layer_FSM (void);
#endif /* INC_HARDWARE_INTERFACE_LAYER_H_ */
