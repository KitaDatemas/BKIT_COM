/*
 * Hardware_Interface_Layer.c
 *
 *  Created on: Jan 31, 2025
 *      Author: ASUS
 */
#include "Hardware_Interface_Layer.h"

uint8_t i2c_en = 0, spi_en = 0, uart_en = 0, RS485_en = 0;
uint8_t Received_Buffer_Flag = 0;
uint8_t Received_Buffer[50] = {0};

BKITCOM_Error_Code code;
BKIT_COM_type_t Com;
Protocol Com_Send_Signal;
Protocol Com_Receive_Signal;

uint8_t Received_Buffer [50];

HIL_State state = IDLE;

/**
  * @brief	Initialize all the protocols that STM32 has (UART, I2C, SPI, ...)
  * @param	NONE
  * @retval	NONE
  */
void i2c_init(void){
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

void hw_reboot(Protocol com){
	switch (com) {
		case UART:
			HAL_UART_DeInit(Com->uart_Handler->uart);
			RS485_init();
			break;
		case I2C:
			HAL_I2C_DeInit(Com->i2c_Handler->i2c);
			i2c_init();
			break;
		case SPI:
			HAL_SPI_DeInit(Com->spi_Handler->spi);
			spi_init();
			break;
		case RS485:
			HAL_UART_DeInit(Com->RS485_Handler->uart);
			RS485_init();
			break;
		default:
			return;
	}
}

void spi_init(void){
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

void uart_init(void){
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

void RS485_init(void){
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


BKITCOM_Error_Code ErrorCode_Handler (HAL_StatusTypeDef Error_Code) {
	switch (Error_Code) {
	case HAL_OK:
		return BKITCOM_SUCCESS;
	case HAL_BUSY:
		return BKITCOM_BUSY;
	case HAL_ERROR:
		switch (Com_Send_Signal) {
		case UART:
			if (code == HAL_UART_ERROR_ORE) {
				uart_reboot();
				return BKITCOM_OVERRUN;
			}
			break;
		case I2C:
			Error_Code = HAL_I2C_GetError(Com->i2c_Handler->i2c);
			if (Error_Code == HAL_I2C_ERROR_ARLO) {
				i2c_reboot();
				return BKITCOM_I2C_COLLISION;
			}
		}
		break;
		case SPI:
			Error_Code = HAL_SPI_GetError(Com.spi_Handler->spi);
			if (Error_Code == HAL_SPI_ERROR_FRE) {
				/*Incorrect SPI clock polarity/phase*/
				spi_reboot();
				return BKITCOM_INVALID_CLOCK_PHASE_POLARITY;
			}
			if (Error_Code == HAL_SPI_ERROR_ABORT) {
				/*Abort arise when the SPI connection is lost, reconnect required*/
				return BKITCOM_ABORT;
			}
			break;
		case RS485:
			break;
		default:
			break;
	}
}

BKITCOM_Error_Code hw_send(Protocol com,uint8_t * data, uint32_t data_length) {
	HAL_StatusTypeDef Error_Code;

	/*Com_Send_Signal is set for FSM to capture the sending signal*/
	Com_Send_Signal = com;
	uint8_t retry = 0;

	/*Determined the protocol to send*/
	SEND_MESSAGE:
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
		break;
	default:
		/*Dealing with uninitialized protocol calling*/
		PROTOCOL_NOT_INIT:
		return BKITCOM_PROTOCOL_NOT_INIT;
	}
	code = Error_Code_Handler(Error_Code);
	if (code != BKITCOM_SUCCESS && retry < 3) {
		retry++;
		goto SEND_MESSAGE;
	}
	return code;
}

BKITCOM_Error_Code hw_receive(uint8_t * data);



void Hardware_Interface_Layer_FSM (void) {
	switch (state) {
	case IDLE:
	/*Com_Send_Signal is set when sending function is called. Check Com_Send_Signal for arriving calling sending function*/
		if (Com_Send_Signal != NONE) {
			state = VERI_SENDING;
		}
		if (Com_Receive_Signal != NONE){
			state = VERI_RECEIVING;
		}
		break;
	/*Verified error code after sending*/
	case VERI_SENDING:
		if (code == SUCCESS)
			state = IDLE;
		else {
				
			}
		}
		break;
	case VERI_RECEIVING:
		if (code == SUCCESS){
			state = IDLE;
		}
		else{
			switch(Com_Receive_Signal){
				case UART:
					Received_Buffer_Flag = 1;
					break;
				case I2C:
					break;
				case SPI:
					break;
				case RS485:
					break;
			}
		}
		break;
	case ERROR_STATE:
		break;
	}
}
