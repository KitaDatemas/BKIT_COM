/*
 * Hardware_Interface_Layer.c
 *
 *  Created on: Jan 31, 2025
 *      Author: ASUS
 */
#include "Hardware_Interface_Layer.h"

uint8_t i2c_en = 0, spi_en = 0, uart_en = 0, RS485_en = 0;
BKIT_COM_type_t Com;
PROTOCOL Com_Send_Signal;

void hw_init(void) {
	if (i2c_en) {
		Com.i2c_Handler->i2c->Init.ClockSpeed = 100000;
		Com.i2c_Handler->i2c->Init.DutyCycle = I2C_DUTYCYCLE_2;
		Com.i2c_Handler->i2c->Init.OwnAddress1 = 0;
		Com.i2c_Handler->i2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
		Com.i2c_Handler->i2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		Com.i2c_Handler->i2c->Init.OwnAddress2 = 0;
		Com.i2c_Handler->i2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		Com.i2c_Handler->i2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
		if (HAL_I2C_Init(Com.i2c_Handler->i2c) != HAL_OK)
		{
			Error_Handler();
		}
	}

	if (spi_en) {
		Com.spi_Handler->spi->Init.Mode = SPI_MODE_MASTER;
		Com.spi_Handler->spi->Init.Direction = SPI_DIRECTION_2LINES;
		Com.spi_Handler->spi->Init.DataSize = SPI_DATASIZE_8BIT;
		Com.spi_Handler->spi->Init.CLKPolarity = SPI_POLARITY_LOW;
		Com.spi_Handler->spi->Init.CLKPhase = SPI_PHASE_1EDGE;
		Com.spi_Handler->spi->Init.NSS = SPI_NSS_SOFT;
		Com.spi_Handler->spi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
		Com.spi_Handler->spi->Init.FirstBit = SPI_FIRSTBIT_MSB;
		Com.spi_Handler->spi->Init.TIMode = SPI_TIMODE_DISABLE;
		Com.spi_Handler->spi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
		Com.spi_Handler->spi->Init.CRCPolynomial = 10;
		if (HAL_SPI_Init(Com.spi_Handler->spi) != HAL_OK)
		{
			Error_Handler();
		}
	}

	if (uart_en) {
		Com.uart_Handler->uart->Init.BaudRate = Com.uart_Handler->baudrate;
		Com.uart_Handler->uart->Init.WordLength = UART_WORDLENGTH_8B;
		Com.uart_Handler->uart->Init.StopBits = UART_STOPBITS_1;
		Com.uart_Handler->uart->Init.Parity = UART_PARITY_NONE;
		Com.uart_Handler->uart->Init.Mode = UART_MODE_TX_RX;
		Com.uart_Handler->uart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
		Com.uart_Handler->uart->Init.OverSampling = UART_OVERSAMPLING_16;
		if (HAL_UART_Init(Com.uart_Handler->uart) != HAL_OK)
		{
			Error_Handler();
		}
	}

	if (RS485_en) {
		Com.RS485_Handler->uart->Init.BaudRate = Com.RS485_Handler->baudrate;
		Com.RS485_Handler->uart->Init.WordLength = UART_WORDLENGTH_8B;
		Com.RS485_Handler->uart->Init.StopBits = UART_STOPBITS_1;
		Com.RS485_Handler->uart->Init.Parity = UART_PARITY_NONE;
		Com.RS485_Handler->uart->Init.Mode = UART_MODE_TX_RX;
		Com.RS485_Handler->uart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
		Com.RS485_Handler->uart->Init.OverSampling = UART_OVERSAMPLING_16;
		if (HAL_UART_Init(Com.RS485_Handler->uart) != HAL_OK)
		{
			Error_Handler();
		}
	}
}

BKITCOM_Error_Code i2c_config (uint8_t i2c_x, uint32_t address) {
	switch (i2c_x) {
		case 1:
			Com.i2c_Handler->i2c->Instance = I2C1;
			break;
		case 2:
			Com.i2c_Handler->i2c->Instance = I2C2;
			break;
		case 3:
			Com.i2c_Handler->i2c->Instance = I2C3;
			break;
		default:
			return BKITCOM_INVALID;
	}
	Com.i2c_Handler->address = address;
	i2c_en = 1;
	return BKITCOM_SUCCESS;
}

BKITCOM_Error_Code spi_config (uint8_t spi_x, uint16_t CPOL, uint16_t CPHA) {
	switch (spi_x) {
		case 1:
			Com.spi_Handler->spi->Instance = SPI1;
			break;
		case 2:
			Com.spi_Handler->spi->Instance = SPI2;
			break;
		case 3:
			Com.spi_Handler->spi->Instance = SPI3;
			break;
		default:
			return BKITCOM_INVALID;
	}
	Com.spi_Handler->CPOL = CPOL;
	Com.spi_Handler->CPHA = CPHA;
	spi_en = 1;
	return BKITCOM_SUCCESS;
}

BKITCOM_Error_Code uart_config (uint8_t uart_x, uint32_t baudrate) {
	switch (uart_x) {
		case 1:
			Com.uart_Handler->uart->Instance = USART1;
			break;
		case 2:
			Com.uart_Handler->uart->Instance = USART2;
			break;
		case 3:
			Com.uart_Handler->uart->Instance = USART3;
			break;
		default:
			return BKITCOM_INVALID;
	}
	Com.uart_Handler->baudrate = baudrate;
	uart_en = 1;
	return BKITCOM_SUCCESS;
}

BKITCOM_Error_Code RS485_config (uint8_t uart_x, uint32_t baudrate, uint32_t address) {
	switch (uart_x) {
	case 1:
		Com.RS485_Handler->uart->Instance = USART1;
		break;
	case 2:
		Com.RS485_Handler->uart->Instance = USART2;
		break;
	case 3:
		Com.RS485_Handler->uart->Instance = USART3;
		break;
	default:
		return BKITCOM_INVALID;
	}
	Com.RS485_Handler->baudrate = baudrate;
	Com.RS485_Handler->address = address;
	RS485_en = 1;
	return BKITCOM_SUCCESS;
}

BKITCOM_Error_Code hw_send(uint8_t * data, uint32_t data_length) {
	HAL_StatusTypeDef Error_Code;
	switch (Com_Send_Signal) {
	case UART:
		if (uart_en == 0)
			goto PROTOCOL_NOT_INIT;
		Error_Code = HAL_UART_Transmit(Com.uart_Handler->uart, data, data_length, 50);
		break;
	case I2C:
		if (i2c_en == 0)
			goto PROTOCOL_NOT_INIT;
		Error_Code = HAL_I2C_Master_Transmit(Com.i2c_Handler->i2c, Com.i2c_Handler->address, data, data_length, 50);
		break;
	case SPI:
		if (spi_en == 0)
			goto PROTOCOL_NOT_INIT;
		Error_Code = HAL_SPI_Transmit(Com.spi_Handler->spi, data, data_length, 50);
		break;
	case RS485:
		if (RS485_en == 0)
			goto PROTOCOL_NOT_INIT;
//
		break;
	default:
		PROTOCOL_NOT_INIT:
		return BKITCOM_PROTOCOL_NOT_INIT;
	}
//	if ()
	return BKITCOM_SUCCESS;
}

BKITCOM_Error_Code hw_send_byte(uint8_t data);
BKITCOM_Error_Code hw_receive(uint8_t * data);

BKITCOM_Error_Code HAL_ErrorCode_Handler (HAL_StatusTypeDef Error_Code) {
	switch (Error_Code) {
	case HAL_OK:
		return BKITCOM_SUCCESS;
	case HAL_BUSY:
		return BKITCOM_BUSY;
	case HAL_ERROR:
		break;
	}
}
