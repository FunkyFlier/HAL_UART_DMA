/*
 * UART.c
 *
 *  Created on: Jun 6, 2016
 *      Author: Michael Baker
 *      Works up to 230400 for loop back
 */

#include <UART.h>

#include "stm32f4xx_hal_uart.h"
void UARTSetup(UART_STRUCT*, UART_HandleTypeDef*, RingBuffer_t*,DoubleBuffer_t*, uint8_t*);

void UARTTXCallBackHandler(UART_STRUCT*);
void UARTRXCallBackHandler(UART_STRUCT*);
void DoubleBufferCreate(DoubleBuffer_t *, uint8_t *, uint8_t *,int );
int DoubleBufferWrite(DoubleBuffer_t *, uint8_t *, int );
void DoubleBufferSwap(DoubleBuffer_t *);

#ifdef LOOP_BACK_DEMO
uint8_t testMessage0[] = "****************************\r\n";
#ifdef UART_1
uint8_t testMessage1[] = "UART1 loop back demonstration\r\n";
#endif
#ifdef UART_2
uint8_t testMessage2[] = "UART2 loop back demonstration\r\n";
#endif
#ifdef UART_3
uint8_t testMessage3[] = "UART3 loop back demonstration\r\n";
#endif
#ifdef UART_4
uint8_t testMessage4[] = "UART4 loop back demonstration\r\n";
#endif
#ifdef UART_5
uint8_t testMessage5[] = "UART5 loop back demonstration\r\n";
#endif
#ifdef UART_6
uint8_t testMessage6[] = "UART6 loop back demonstration\r\n";
#endif
#ifdef UART_7
uint8_t testMessage7[] = "UART7 loop back demonstration\r\n";
#endif
#ifdef UART_8
uint8_t testMessage8[] = "UART8 loop back demonstration\r\n";
#endif
#endif

void UARTInit() {
#ifdef UART_1
	if (HAL_UART_GetState(&huart1) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_1_RX_RING, UART_1_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_1_TX_DB, UART_1_TX_BUFFER1,UART_1_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
		UARTSetup(&UART_1_STRUCT, &huart1, &UART_1_RX_RING, &UART_1_TX_DB,ISRBuffer_1);
		if (HAL_UART_Receive_IT(UART_1_STRUCT.uartHandler, UART_1_STRUCT.ISRBuf, 1)!= HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
			printf("uart1 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
		}
	}else{
#ifdef DEBUG_TO_CONSOLE
		printf("uart1 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART1,loopBackUART1Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_1_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_1_STRUCT, testMessage1, sizeof(testMessage1) - 1);
	UARTWriteBuffer(&UART_1_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
#endif//UART_1
#ifdef UART_2
	if (HAL_UART_GetState(&huart2) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_2_RX_RING, UART_2_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_2_TX_DB, UART_2_TX_BUFFER1,UART_2_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
		UARTSetup(&UART_2_STRUCT, &huart2, &UART_2_RX_RING, &UART_2_TX_DB,ISRBuffer_2);
		if (HAL_UART_Receive_DMA(UART_2_STRUCT.uartHandler, UART_2_STRUCT.rxBuffer->buffer, 1)!= HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
			printf("uart2 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
		}
	}else{
#ifdef DEBUG_TO_CONSOLE
		printf("uart2 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART2,loopBackUART2Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_2_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_2_STRUCT, testMessage2, sizeof(testMessage2) - 1);
	UARTWriteBuffer(&UART_2_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
#endif//UART_2
#ifdef UART_3
	if (HAL_UART_GetState(&huart3) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_3_RX_RING, UART_3_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_3_TX_DB, UART_3_TX_BUFFER1,UART_3_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
		UARTSetup(&UART_3_STRUCT, &huart3, &UART_3_RX_RING, &UART_3_TX_DB,ISRBuffer_3);
		if (HAL_UART_Receive_IT(UART_3_STRUCT.uartHandler, UART_3_STRUCT.ISRBuf, 1)!= HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
			printf("uart3 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
		}
	}else{
#ifdef DEBUG_TO_CONSOLE
		printf("uart3 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART3,loopBackUART3Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_3_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_3_STRUCT, testMessage3, sizeof(testMessage3) - 1);
	UARTWriteBuffer(&UART_3_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
#endif//UART_3
#ifdef UART_4
	if (HAL_UART_GetState(&huart4) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_4_RX_RING, UART_4_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_4_TX_DB, UART_4_TX_BUFFER1,UART_4_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
		UARTSetup(&UART_4_STRUCT, &huart4, &UART_4_RX_RING, &UART_4_TX_DB,ISRBuffer_4);
		if (HAL_UART_Receive_IT(UART_4_STRUCT.uartHandler, UART_4_STRUCT.ISRBuf, 1)!= HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
			printf("uart4 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
		}
	}else{
#ifdef DEBUG_TO_CONSOLE
		printf("uart4 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART4,loopBackUART4Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_4_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_4_STRUCT, testMessage4, sizeof(testMessage4) - 1);
	UARTWriteBuffer(&UART_4_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
#endif//UART_4
#ifdef UART_5
	if (HAL_UART_GetState(&huart5) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_5_RX_RING, UART_5_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_5_TX_DB, UART_5_TX_BUFFER1,UART_5_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
		UARTSetup(&UART_5_STRUCT, &huart5, &UART_5_RX_RING, &UART_5_TX_DB,ISRBuffer_5);
		if (HAL_UART_Receive_IT(UART_5_STRUCT.uartHandler, UART_5_STRUCT.ISRBuf, 1)!= HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
			printf("uart5 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
		}
	}else{
#ifdef DEBUG_TO_CONSOLE
		printf("uart5 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART5,loopBackUART5Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_5_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_5_STRUCT, testMessage5, sizeof(testMessage5) - 1);
	UARTWriteBuffer(&UART_5_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
#endif//UART_5
#ifdef UART_6
	if (HAL_UART_GetState(&huart6) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_6_RX_RING, UART_6_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_6_TX_DB, UART_6_TX_BUFFER1,UART_6_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
		UARTSetup(&UART_6_STRUCT, &huart6, &UART_6_RX_RING, &UART_6_TX_DB,ISRBuffer_6);
		if (HAL_UART_Receive_IT(UART_6_STRUCT.uartHandler, UART_6_STRUCT.ISRBuf, 1)!= HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
			printf("uart6 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
		}
	}else{
#ifdef DEBUG_TO_CONSOLE
		printf("uart6 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART6,loopBackUART6Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_6_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_6_STRUCT, testMessage6, sizeof(testMessage6) - 1);
	UARTWriteBuffer(&UART_6_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
#endif//UART_6
#ifdef UART_7
	if (HAL_UART_GetState(&huart7) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_7_RX_RING, UART_7_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_7_TX_DB, UART_7_TX_BUFFER1,UART_7_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
		UARTSetup(&UART_7_STRUCT, &huart7, &UART_7_RX_RING, &UART_7_TX_DB,ISRBuffer_7);
		if (HAL_UART_Receive_IT(UART_7_STRUCT.uartHandler, UART_7_STRUCT.ISRBuf, 1)!= HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
			printf("uart7 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
		}
	}else{
#ifdef DEBUG_TO_CONSOLE
		printf("uart7 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART7,loopBackUART7Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_7_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_7_STRUCT, testMessage7, sizeof(testMessage7) - 1);
	UARTWriteBuffer(&UART_7_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
#endif//UART_7
#ifdef UART_8
	if (HAL_UART_GetState(&huart8) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_8_RX_RING, UART_8_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_8_TX_DB, UART_8_TX_BUFFER1,UART_8_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
		UARTSetup(&UART_8_STRUCT, &huart8, &UART_8_RX_RING, &UART_8_TX_DB,ISRBuffer_8);
		if (HAL_UART_Receive_IT(UART_8_STRUCT.uartHandler, UART_8_STRUCT.ISRBuf, 1)!= HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
			printf("uart8 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
		}
	}else{
#ifdef DEBUG_TO_CONSOLE
		printf("uart8 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART8,loopBackUART8Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_8_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_8_STRUCT, testMessage8, sizeof(testMessage8) - 1);
	UARTWriteBuffer(&UART_8_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
#endif//UART_8
}

#ifdef LOOP_BACK_DEMO
void UARTLoopDemo(){

#ifdef UART_1
	if (UARTAvailabe(&UART_1_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_1_STRUCT,loopBackBuffer,UARTAvailabe(&UART_1_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART1,loopBackBuffer,numBytes);
		}
	}
	if (RingBufferAvailable(&loopBackUART1) > 0 ){
		numBytes = RingBufferRead(&loopBackUART1,loopBackBuffer,RingBufferAvailable(&loopBackUART1));
		if (numBytes != -1){
			UARTWriteBuffer(&UART_1_STRUCT,loopBackBuffer,numBytes);
		}

	}
#endif
#ifdef UART_2
	if (UARTAvailabe(&UART_2_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_2_STRUCT,loopBackBuffer,UARTAvailabe(&UART_2_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART2,loopBackBuffer,numBytes);
		}
	}
	if (RingBufferAvailable(&loopBackUART2) > 0 ){
		numBytes = RingBufferRead(&loopBackUART2,loopBackBuffer,RingBufferAvailable(&loopBackUART2));
		if (numBytes != -1){
			UARTWriteBuffer(&UART_2_STRUCT,loopBackBuffer,numBytes);
		}

	}
#endif
#ifdef UART_3
	if (UARTAvailabe(&UART_3_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_3_STRUCT,loopBackBuffer,UARTAvailabe(&UART_3_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART3,loopBackBuffer,numBytes);
		}
	}
	if (RingBufferAvailable(&loopBackUART3) > 0 ){
		numBytes = RingBufferRead(&loopBackUART3,loopBackBuffer,RingBufferAvailable(&loopBackUART3));
		if (numBytes != -1){
			UARTWriteBuffer(&UART_3_STRUCT,loopBackBuffer,numBytes);
		}

	}
#endif
#ifdef UART_4
	if (UARTAvailabe(&UART_4_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_4_STRUCT,loopBackBuffer,UARTAvailabe(&UART_4_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART4,loopBackBuffer,numBytes);
		}
	}
	if (RingBufferAvailable(&loopBackUART4) > 0 ){
		numBytes = RingBufferRead(&loopBackUART4,loopBackBuffer,RingBufferAvailable(&loopBackUART4));
		if (numBytes != -1){
			UARTWriteBuffer(&UART_4_STRUCT,loopBackBuffer,numBytes);
		}

	}
#endif
#ifdef UART_5
	if (UARTAvailabe(&UART_5_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_5_STRUCT,loopBackBuffer,UARTAvailabe(&UART_5_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART5,loopBackBuffer,numBytes);
		}
	}
	if (RingBufferAvailable(&loopBackUART5) > 0 ){
		numBytes = RingBufferRead(&loopBackUART5,loopBackBuffer,RingBufferAvailable(&loopBackUART5));
		if (numBytes != -1){
			UARTWriteBuffer(&UART_5_STRUCT,loopBackBuffer,numBytes);
		}

	}
#endif
#ifdef UART_6
	if (UARTAvailabe(&UART_6_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_6_STRUCT,loopBackBuffer,UARTAvailabe(&UART_6_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART6,loopBackBuffer,numBytes);
		}
	}
	if (RingBufferAvailable(&loopBackUART6) > 0 ){
		numBytes = RingBufferRead(&loopBackUART6,loopBackBuffer,RingBufferAvailable(&loopBackUART6));
		if (numBytes != -1){
			UARTWriteBuffer(&UART_6_STRUCT,loopBackBuffer,numBytes);
		}

	}
#endif
#ifdef UART_6
	if (UARTAvailabe(&UART_6_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_6_STRUCT,loopBackBuffer,UARTAvailabe(&UART_6_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART6,loopBackBuffer,numBytes);
		}
	}
	if (RingBufferAvailable(&loopBackUART6) > 0 ){
		numBytes = RingBufferRead(&loopBackUART6,loopBackBuffer,RingBufferAvailable(&loopBackUART6));
		if (numBytes != -1){
			UARTWriteBuffer(&UART_6_STRUCT,loopBackBuffer,numBytes);
		}

	}
#endif
#ifdef UART_7
	if (UARTAvailabe(&UART_7_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_7_STRUCT,loopBackBuffer,UARTAvailabe(&UART_7_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART7,loopBackBuffer,numBytes);
		}
	}
	if (RingBufferAvailable(&loopBackUART7) > 0 ){
		numBytes = RingBufferRead(&loopBackUART7,loopBackBuffer,RingBufferAvailable(&loopBackUART7));
		if (numBytes != -1){
			UARTWriteBuffer(&UART_7_STRUCT,loopBackBuffer,numBytes);
		}

	}
#endif
#ifdef UART_8
	if (UARTAvailabe(&UART_8_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_8_STRUCT,loopBackBuffer,UARTAvailabe(&UART_8_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART8,loopBackBuffer,numBytes);
		}
	}
	if (RingBufferAvailable(&loopBackUART8) > 0 ){
		numBytes = RingBufferRead(&loopBackUART8,loopBackBuffer,RingBufferAvailable(&loopBackUART8));
		if (numBytes != -1){
			UARTWriteBuffer(&UART_8_STRUCT,loopBackBuffer,numBytes);
		}

	}
#endif
}
#endif
//setup
void UARTSetup(UART_STRUCT* uartS, UART_HandleTypeDef* uartH,RingBuffer_t* rbRX, DoubleBuffer_t* dbTX,uint8_t* ISRBuf) {
	uartS->uartHandler = uartH;
	uartS->rxBuffer = rbRX;
	uartS->txBuffer = dbTX;
	uartS->ISRBuf = ISRBuf;
	uartS->RXOverRun = false;
	uartS->TXOverRun = false;
}
//end setup

//byte and buffer IO
int UARTWriteBuffer(UART_STRUCT* uartS, uint8_t* buff, int n) {
	n = DoubleBufferWrite(uartS->txBuffer, buff, n);
	if (n == -1){
		uartS->TXOverRun = true;
	}
	if (DoubleBufferAvailable(uartS->txBuffer) > 0){
		if (HAL_UART_Transmit_DMA(uartS->uartHandler, uartS->txBuffer->buffer, DoubleBufferAvailable(uartS->txBuffer)) != HAL_BUSY) {
			DoubleBufferSwap(uartS->txBuffer);
		}
	}
	return n;

}
void UARTTXCallBackHandler(UART_STRUCT* uartS) {
	if (uartS->txBuffer->writing == true) {
		return;
	}
	if (DoubleBufferAvailable(uartS->txBuffer) > 0){
		if (HAL_UART_Transmit_DMA(uartS->uartHandler, uartS->txBuffer->buffer, DoubleBufferAvailable(uartS->txBuffer)) != HAL_BUSY) {
			DoubleBufferSwap(uartS->txBuffer);
		}
	}
}
int UARTAvailabe(UART_STRUCT* uartS) {
	return RingBufferAvailable(uartS->rxBuffer);
}

int UARTGetBuffer(UART_STRUCT* uartS, uint8_t* buff, int n) {
	return RingBufferRead(uartS->rxBuffer,buff,n);
}

void UARTRXCallBackHandler(UART_STRUCT* uartS) {
	//faster than copying the same byte to the ring buffer every time?
	uartS->rxBuffer->readIdxTemp = uartS->rxBuffer->readIdx;

	if (uartS->rxBuffer->readIdxTemp == ((uartS->rxBuffer->writeIdx + 1) % uartS->rxBuffer->size)){
		uartS->RXOverRun = true;
	}else{
		uartS->rxBuffer->writeIdx = (uartS->rxBuffer->writeIdx + (1)) % uartS->rxBuffer->size;

	}
	if (HAL_UART_Receive_DMA(UART_2_STRUCT.uartHandler, UART_2_STRUCT.rxBuffer->buffer + UART_2_STRUCT.rxBuffer->writeIdx, 1) != HAL_OK){
		if (UART_2_STRUCT.uartHandler->RxState == HAL_UART_STATE_READY) {
			UART_2_STRUCT.uartHandler->RxState = HAL_UART_STATE_BUSY_RX;
			UART_2_STRUCT.uartHandler->pRxBuffPtr = &UART_2_STRUCT.rxBuffer->buffer[UART_2_STRUCT.rxBuffer->writeIdx];
			UART_2_STRUCT.uartHandler->RxXferSize = 1;
			UART_2_STRUCT.uartHandler->ErrorCode = HAL_UART_ERROR_NONE;
			uint32_t *tmp = (uint32_t*) &UART_2_STRUCT.uartHandler->pRxBuffPtr;
			HAL_DMA_Start_IT(UART_2_STRUCT.uartHandler->hdmarx,(uint32_t) &UART_2_STRUCT.uartHandler->Instance->DR, *(uint32_t*) tmp,1);
			SET_BIT(UART_2_STRUCT.uartHandler->Instance->CR1, USART_CR1_PEIE);
			SET_BIT(UART_2_STRUCT.uartHandler->Instance->CR3, USART_CR3_EIE);
			SET_BIT(UART_2_STRUCT.uartHandler->Instance->CR3, USART_CR3_DMAR);
		}
	}


}

//ISR callbacks
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	//this function puts the received byte into the correct ring buffer
	switch ((uint32_t) huart->Instance) {
#ifdef USART1
	case (uint32_t) USART1:
#ifdef UART_1
		UARTRXCallBackHandler(&UART_1_STRUCT);
#endif//UART_1
		break;
#endif//USART1
#ifdef USART2
	case (uint32_t) USART2:
#ifdef UART_2
		UARTRXCallBackHandler(&UART_2_STRUCT);
#endif//UART_2
		break;
#endif//USART2
#ifdef USART3
		case (uint32_t)USART3:
#ifdef UART_3
		UARTRXCallBackHandler(&UART_3_STRUCT);
#endif//UART_3
		break;
#endif//USART3
#ifdef USART4
		case (uint32_t)USART4:
#ifdef UART_4
		UARTRXCallBackHandler(&UART_4_STRUCT);
#endif//UART_4
		break;
#endif//USART4
#ifdef UART5
		case (uint32_t)UART5:
#ifdef UART_5
		UARTRXCallBackHandler(&UART_5_STRUCT);
#endif//UART_5
		break;
#endif//USART5
#ifdef USART6
	case (uint32_t) USART6:
#ifdef UART_6
		UARTRXCallBackHandler(&UART_6_STRUCT);
#endif//UART_6
		break;
#endif//USART6
#ifdef UART7
		case (uint32_t)UART7:
#ifdef UART_7
		UARTRXCallBackHandler(&UART_7_STRUCT);
#endif//UART_7
		break;
#endif//USART7
#ifdef USART8
		case (uint32_t)USART8:
#ifdef UART_8
		UARTRXCallBackHandler(&UART_8_STRUCT);
#endif//UART_8
		break;
#endif//USART8
	}

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {

	switch ((uint32_t) huart->Instance) {
#ifdef USART1
	case (uint32_t) USART1:
#ifdef UART_1
		UARTTXCallBackHandler(&UART_1_STRUCT);
#endif//UART_1
		break;
#endif//USART1
#ifdef USART2
	case (uint32_t) USART2:
#ifdef UART_2
		UARTTXCallBackHandler(&UART_2_STRUCT);
#endif//UART_2
		break;
#endif//USART2
#ifdef USART3
		case (uint32_t)USART3:
#ifdef UART_3
		UARTTXCallBackHandler(&UART_3_STRUCT);
#endif//UART_3
		break;
#endif//USART3
#ifdef USART4
		case (uint32_t)USART4:
#ifdef UART_4
		UARTTXCallBackHandler(&UART_4_STRUCT);
#endif//UART_4
		break;
#endif//USART4
#ifdef USART5
		case (uint32_t)USART5:
#ifdef UART_5
		UARTTXCallBackHandler(&UART_5_STRUCT);
#endif//UART_5
		break;
#endif//USART5
#ifdef USART6
	case (uint32_t) USART6:
#ifdef UART_6
		UARTTXCallBackHandler(&UART_6_STRUCT);
#endif//UART_6
		break;
#endif//USART6
#ifdef USART7
		case (uint32_t)USART7:
#ifdef UART_7
		UARTTXCallBackHandler(&UART_7_STRUCT);
#endif//UART_7
		break;
#endif//USART7
#ifdef USART8
		case (uint32_t)USART8:
#ifdef UART_8
		UARTTXCallBackHandler(&UART_8_STRUCT);
#endif//UART_8
		break;
#endif//USART8
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
#ifdef DEBUG_TO_CONSOLE
	//printf("uart error: %lu\n", huart->ErrorCode);
	printf("u E: %i\nu S: %i\n", (int) HAL_UART_GetError(huart),
			(int) HAL_UART_GetState(huart));
#endif
}
void DoubleBufferCreate(DoubleBuffer_t *tb, uint8_t *buffer0, uint8_t *buffer1,int sizeOfBuffer){
	tb->buffer0 = buffer0;
	tb->buffer1 = buffer1;
	tb->buffer = tb->buffer0;
	tb->size = sizeOfBuffer;
	tb->writeIdx = 0;
	tb->useBuffer0 = true;
	tb->writing = false;
}

//called from UARTwrite when TX is in progress
int DoubleBufferWrite(DoubleBuffer_t *tb, uint8_t *in, int count){
	if (DoubleBufferFree(tb) == 0){
		return -1;
	}
	if (DoubleBufferFree(tb) < count){
		count = DoubleBufferFree(tb);
	}
	tb->writing = true;
	memcpy(&tb->buffer[tb->writeIdx], in, count);
	DoubleBufferCommitWrite(tb,count);
	tb->writing = false;
	return count;
}

//called after one of the buffers is sent with HAL_UART_Transmit_IT
void DoubleBufferSwap(DoubleBuffer_t *tb){
	tb->useBuffer0 ^= true;
	if (tb->useBuffer0 == true){
		tb->buffer = tb->buffer0;
	}else{
		tb->buffer = tb->buffer1;
	}
	tb->writeIdx = 0;
}

int RingBufferAvailable(RingBuffer_t *rb) {
	int readIndex = rb->readIdx;
	int writeIndex = rb->writeIdx;
	int available =  writeIndex - readIndex;
	if (available < 0){
		available += rb->size;
	 }
	return available;
}

void RingBufferCreate(RingBuffer_t *rb, uint8_t *buffer, int sizeOfBuffer) {
	rb->buffer = buffer;
	rb->size = sizeOfBuffer;
	rb->readIdx = 0;
	rb->writeIdx = 0;
}


int RingBufferWrite(RingBuffer_t *rb, uint8_t *in, int count) {
	rb->readIdxTemp = rb->readIdx;
	rb->availableWrite = rb->writeIdx - rb->readIdxTemp;
	if (rb->availableWrite < 0){
		rb->availableWrite += rb->size;
	}
	if (rb->availableWrite >= rb->size){
		return -1;
	}
	if(rb->availableWrite == 0){
		rb->writeIdx = rb->readIdx = 0;
	}

	if ((rb->size - rb->availableWrite) < count){
		count = (rb->size -rb->availableWrite);
	}
	if (RingWriteIdxToEnd(rb) >= count){
		memcpy(rb->buffer + rb->writeIdx, in, count);
	}else{
		memcpy(rb->buffer + rb->writeIdx, in, RingWriteIdxToEnd(rb));
		memcpy(rb->buffer, in + RingWriteIdxToEnd(rb), count - RingWriteIdxToEnd(rb));
	}
	RingBufferCommitWrite(rb, count);
	return count;
}
int RingBufferRead(RingBuffer_t *rb, uint8_t *out, int count){
	rb->writeIdxTemp = rb->writeIdx;
	rb->availableRead = rb->writeIdxTemp - rb->readIdx;
	if (rb->availableRead < 0){
		rb->availableRead += rb->size;
	}
	if (rb->availableRead == 0){
		return -1;
	}

	if (rb->availableRead < count){
		count = rb->availableRead;
	}
	if (rb->writeIdxTemp > rb->readIdx){
		memcpy(out, rb->buffer + rb->readIdx, count);
		RingBufferCommitRead(rb,count);
		return count;
	}
	if (RingReadIdxToEnd(rb) >= count){
		memcpy(out, rb->buffer + rb->readIdx, count);
		RingBufferCommitRead(rb,count);
		return count;
	}else{
		memcpy(out, rb->buffer + rb->readIdx, RingReadIdxToEnd(rb));
		memcpy(out, rb->buffer , count - RingReadIdxToEnd(rb));
	}
	RingBufferCommitRead(rb,count);
	return count;
}

