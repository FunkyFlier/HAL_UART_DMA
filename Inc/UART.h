/*
 * UART.h
 *
 *  Created on: Jun 6, 2016
 *      Author: work
 *
 * Cube code must have UART_HandleTypeDef having gState and RxState instead of just State
 * Tested working on:
 * F0 v1.6.0
 * F4 v1.12.0
 * Assumed working:
 * F3 v1.5.0
 * F7 v1.4.0
 * L0 v1.7.0
 * L4 v1.5.0
 * Will not work with:
 * F1 v1.4.0
 * F2 v1.3.0
 * L1 v1.5.0
 *
 * Usage:
 * 1 - Select defines
 * 2 - Call UARTInit() in user code 2 of main loop
 * 3 - Call UARTLoopDemo() in while(1){} if using loop back demonstration
 *
 * #define UART_1
 * #define UART_2
 * #define UART_3
 * #define UART_4
 * #define UART_5
 * #define UART_6
 * #define UART_7
 * #define UART_8
 * #define UART_1_DMA_TX
 * #define UART_2_DMA_TX
 * #define UART_3_DMA_TX
 * #define UART_4_DMA_TX
 * #define UART_5_DMA_TX
 * #define UART_6_DMA_TX
 * #define UART_7_DMA_TX
 * #define UART_8_DMA_TX
 * #define UART_1_DMA_RX
 * #define UART_2_DMA_RX
 * #define UART_3_DMA_RX
 * #define UART_4_DMA_RX
 * #define UART_5_DMA_RX
 * #define UART_6_DMA_RX
 * #define UART_7_DMA_RX
 * #define UART_8_DMA_RX
 * #include "stm32f0xx_hal.h"
 * #include "stm32f3xx_hal.h"
 * #include "stm32f4xx_hal.h"
 * #include "stm32f5xx_hal.h"
 * #include "stm32l0xx_hal.h"
 * #include "stm32l4xx_hal.h"
 * Do not define unless using demo
 * #define LOOP_BACK_DEMO
 */

#ifndef UART_H_
#define UART_H_

#include <string.h>
#include <stdbool.h>
#include "stdint.h"
#include <stdio.h>

//user defines----------------------
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_dma.h"
#define UART_2
#define UART_2_DMA_TX
//#define UART_2_DMA_RX


#define LOOP_BACK_DEMO

#define UART_RING_BUF_SIZE_RX 128
#define UART_RING_BUF_SIZE_TX 128
//user defines----------------------

typedef struct{
	uint8_t* buffer;
	uint16_t size;
	volatile int writeIdx,writeIdxTemp;
	volatile int readIdx,readIdxTemp;
	volatile int availableWrite,availableRead;
}RingBuffer_t;

typedef struct{
	uint8_t* buffer0;//must have two buffers otherwise there is the potential the data can be changed between transmits;
	uint8_t* buffer1;
	uint8_t* buffer;
	volatile bool useBuffer0;
	volatile bool writing;
	uint16_t size;
	volatile uint16_t writeIdx;
}DoubleBuffer_t;
typedef struct {
	UART_HandleTypeDef *uartHandler;
	RingBuffer_t *rxBuffer;
	DoubleBuffer_t *txBuffer;
	uint8_t* ISRBuf;
	bool RXOverRun;
	bool TXOverRun;
	bool TXDMA;
	bool RXDMA;
	volatile bool transmitting;
} UART_STRUCT;



void UARTInit();

int UARTWriteBuffer(UART_STRUCT*, uint8_t*, int);
int UARTGetBuffer(UART_STRUCT*, uint8_t*, int);
int UARTAvailabe(UART_STRUCT*);
void UARTLoopDemo();

void RingBufferCreate(RingBuffer_t *, uint8_t *, int );
int RingBufferWrite(RingBuffer_t *, uint8_t *, int );
int RingBufferRead(RingBuffer_t *, uint8_t *, int );
int RingBufferAvailable(RingBuffer_t *);

#define DoubleBufferFree(T) ((T)->size - (T)->writeIdx)
#define DoubleBufferAvailable(T) ((T)->writeIdx)
#define DoubleBufferCommitWrite(T,A) ((T)->writeIdx += A)

#define RingBufferFree(B) ((B)->size - RingBufferAvailable(B))
#define RingWriteIdxToEnd(B) ((B)->size - (B)->writeIdx)
#define RingReadIdxToEnd(B) ((B)->size - (B)->readIdx)
#define RingBufferCommitRead(B, A) ((B)->readIdx = ((B)->readIdx + (A)) % (B)->size)
#define RingBufferCommitWrite(B, A) ((B)->writeIdx = ((B)->writeIdx + (A)) % (B)->size)

#ifdef LOOP_BACK_DEMO
uint8_t loopBackBuffer[UART_RING_BUF_SIZE_RX];
int numBytes;
#endif

#ifdef UART_1
UART_STRUCT UART_1_STRUCT;
uint8_t UART_1_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_1_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_1_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_1[1];
RingBuffer_t UART_1_RX_RING;
DoubleBuffer_t UART_1_TX_DB;
extern UART_HandleTypeDef huart1;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART1Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART1;
#endif
#endif
#ifdef UART_2
UART_STRUCT UART_2_STRUCT;
uint8_t UART_2_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_2_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_2_TX_BUFFER2[UART_RING_BUF_SIZE_TX];

uint8_t ISRBuffer_2[1];
#ifdef UART_2_DMA_RX

#endif
RingBuffer_t UART_2_RX_RING;
DoubleBuffer_t UART_2_TX_DB;
extern UART_HandleTypeDef huart2;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART2Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART2;
#endif
#endif
#ifdef UART_3
UART_STRUCT UART_3_STRUCT;
uint8_t UART_3_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_3_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_3_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_3[1];
RingBuffer_t UART_3_RX_RING;
DoubleBuffer_t UART_3_TX_DB;
extern UART_HandleTypeDef huart3;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART3Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART3;
#endif
#endif
#ifdef UART_4
UART_STRUCT UART_4_STRUCT;
uint8_t UART_4_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_4_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_4_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_4[1];
RingBuffer_t UART_4_RX_RING;
DoubleBuffer_t UART_4_TX_DB;
extern UART_HandleTypeDef huart4;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART4Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART4;
#endif
#endif
#ifdef UART_5
UART_STRUCT UART_5_STRUCT;
uint8_t UART_5_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_5_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_5_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_5[1];
RingBuffer_t UART_5_RX_RING;
DoubleBuffer_t UART_5_TX_DB;
extern UART_HandleTypeDef huart5;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART5Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART5;
#endif
#endif
#ifdef UART_6
UART_STRUCT UART_6_STRUCT;
uint8_t UART_6_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_6_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_6_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_6[1];
RingBuffer_t UART_6_RX_RING;
DoubleBuffer_t UART_6_TX_DB;
extern UART_HandleTypeDef huart6;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART6Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART6;
#endif
#endif
#ifdef UART_7
UART_STRUCT UART_7_STRUCT;
uint8_t UART_7_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_7_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_7_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_7[1];
RingBuffer_t UART_7_RX_RING;
DoubleBuffer_t UART_7_TX_DB;
extern UART_HandleTypeDef huart7;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART7Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART7;
#endif
#endif
#ifdef UART_8
UART_STRUCT UART_8_STRUCT;
uint8_t UART_8_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_8_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_8_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_8[1];
RingBuffer_t UART_8_RX_RING;
DoubleBuffer_t UART_8_TX_DB;
extern UART_HandleTypeDef huart8;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART8Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART8;
#endif
#endif



#endif /* UART_H_ */
