/**
 * @file   UartIf.h
 * @author Thomas Pfeiffer
 * @date   Jun 28, 2015
 * @brief
 */

#ifndef _UARTIF_H_
#define _UARTIF_H_

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t TUartDataType;
typedef uint8_t TUartBufferSize;

typedef enum {
   eNone, eEven, eOdd
} TUartParityEnum;

/**
 * Defines the Uart configuration datatype
 */
typedef struct {
   uint32_t baud;
   uint8_t databits;
   uint8_t stopbits;
   TUartParityEnum parity;
} TUartConfiguration;

/**
 * Defines a fifo buffer.
 */
typedef struct {
   /* A pointer to the buffer. */
   TUartDataType* buffer;
   /* The current read index in the buffer. */
   TUartBufferSize rdIdx;
   /* The current write index in the buffer. */
   TUartBufferSize wrIdx;
   /* The number of free elements in the buffer. */
   TUartBufferSize space;
   /* The size of the buffer. */
   const TUartBufferSize size;
} TUartBufferType;

typedef enum {
   ePowerOn, ePowerOff, eEnableTx, eDisableTx, eEnableRx, eDisableRx
} TUartIoCtlEnum;

typedef struct {
   uint8_t * inData;
   uint8_t inDataLength;
   uint8_t * outData;
   uint8_t outDataLength;
} TUartIoCtlData;

/**
 * Function pointer definition for the hardware dependent init function
 * @param channel The hardware channel which should be used.
 * @param conf    The configuration to be used.
 * @return True if the initialization was successfull, false otherwise.
 */
typedef bool (*TUartInitFunc)(uint8_t channel, TUartConfiguration const * conf);

/**
 * Allows the application a generic control over the hardware
 * @param ctlCode The controlcode to be executed
 * @param data A Pointer to a controlcode-data structure. Can be null if no data are needed for the controlcode.
 * @return Returns true if the controlcode was executed successfully, false otherwise.
 */
typedef bool (*TUartIoCtl)(uint8_t channel, TUartIoCtlEnum ctlCode,
      TUartIoCtlData * data);

/**
 * Defines the Uart datatype
 */
typedef struct {
   uint8_t channel;
   const char * name;
   TUartConfiguration config;
   TUartBufferType rx;
   TUartBufferType tx;
   TUartInitFunc fpDevInit;
   TUartIoCtl fpIoCtl;
} TUart;

/**
 * Initializes the uart peripheral. TODO: describe how to port to other hardware
 * @param pUart          A pointer to the UART which should be initialized
 * @param pConfiguration A pointer to the configuration to be used. Gets stored in the uart structure.
 */
void uart_init(TUart const * pUart);

/**
 * Tries to write length data of pData into the uart's buffer.
 * @param pUart The uart over which the data should be sent.
 * @param pData The buffer which contains the data to be sent.
 * @param length The number of bytes to be sent.
 * @return The number of bytes actually written to the buffer.
 */
TUartBufferSize uart_put_data(TUart const * pUart, TUartDataType const * pData,
      TUartBufferSize length);

/**
 * Gets data from the uart's buffer
 * @param pUart The uart to get the data from
 * @param pData The buffer where the data should be stored
 * @param length The maximum number of bytes which are fetched from the uart's buffer.
 * @return The number of bytes actually fetched from the uart.
 */
TUartBufferSize uart_get_data(TUart const * pUart,
      TUartDataType const * const pData, TUartBufferSize length);

#endif /* _UARTIF_H_ */
