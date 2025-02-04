/*
 * Error_Code.h
 *
 *  Created on: Jan 31, 2025
 *      Author: ASUS
 */

#ifndef INC_ERROR_CODE_H_
#define INC_ERROR_CODE_H_

typedef enum {
	BKITCOM_SUCCESS = 0,
	BKITCOM_BUSY,
	BKITCOM_TIMEOUT,
	BKITCOM_COLLAPSED,
	BKITCOM_INVALID,
	BKITCOM_PROTOCOL_NOT_INIT
} BKITCOM_Error_Code;

#endif /* INC_ERROR_CODE_H_ */
