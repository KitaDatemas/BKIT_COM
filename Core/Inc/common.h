/*
 * common.h
 *
 *  Created on: Feb 14, 2025
 *      Author: truon
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_
typedef enum {NONE, UART, I2C, SPI, RS485} Protocol;

typedef enum{
	BKITCOM_MASTER,
	BKITCOM_SLAVE
}BKITCOM_Role_type_t;

typedef enum{
	BKITCOM_NONE,
	BKITCOM_CRC_VALID,
	BKITCOM_CRC_INVALID
} CRC_Status_type_t;


#endif /* INC_COMMON_H_ */
