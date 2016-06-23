/*
 * UART.c
 *
 *  Created on: Jun 6, 2016
 *      Author: Michael Baker
 *      Email: mikesbaker@gmail.com
 */
#include <UART.h>
//PFP
void UARTSetup(UART_STRUCT*, UART_HandleTypeDef*, RingBuffer_t*,DoubleBuffer_t*, uint8_t*);
void UARTTXCallBackHandler(UART_STRUCT*);
void UARTRXCallBackHandler(UART_STRUCT*);
void DoubleBufferCreate(DoubleBuffer_t *, uint8_t *, uint8_t *,int );
int DoubleBufferWrite(DoubleBuffer_t *, uint8_t *, int );
void DoubleBufferSwap(DoubleBuffer_t *);
int RingBufferWriteByte(RingBuffer_t*, uint8_t*);

//END PFP-------------------------------------------------------
//PV

#ifdef LOOP_BACK_DEMO
uint8_t loopBackBuffer[UART_RING_BUF_SIZE_RX];
int numBytes;
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



//END PV-------------------------------------------------------



//uart
//init
void UARTSetup(UART_STRUCT* uartS, UART_HandleTypeDef* uartH,RingBuffer_t* rbRX, DoubleBuffer_t* dbTX,uint8_t* ISRBuf) {
	uartS->uartHandler = uartH;
	uartS->rxBuffer = rbRX;
	uartS->txBuffer = dbTX;
	uartS->ISRBuf = ISRBuf;
	uartS->RXOverRun = false;
	uartS->TXOverRun = false;

}
void UARTInit() {
#ifdef UART_1
	if (HAL_UART_GetState(&huart1) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_1_RX_RING, UART_1_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_1_TX_DB, UART_1_TX_BUFFER1,UART_1_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
#ifdef UART_1_DMA_TX
		UART_1_STRUCT.TXDMA = true;
#else
		UART_1_STRUCT.TXDMA = false;
#endif
#ifdef UART_1_DMA_RX
		UART_1_STRUCT.RXDMA = true;
#else
		UART_1_STRUCT.RXDMA = false;
#endif
		UARTSetup(&UART_1_STRUCT, &huart1, &UART_1_RX_RING, &UART_1_TX_DB,ISRBuffer_1);
		if (UART_1_STRUCT.RXDMA == true){
			HAL_UART_Receive_DMA(UART_1_STRUCT.uartHandler, ISRBuffer_1, 1);
		}else{
			HAL_UART_Receive_IT(UART_1_STRUCT.uartHandler, UART_1_STRUCT.rxBuffer->buffer, 1);
		}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART1,loopBackUART1Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_1_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_1_STRUCT, testMessage1, sizeof(testMessage1) - 1);
	UARTWriteBuffer(&UART_1_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
	}

#endif//UART_1
#ifdef UART_2
	if (HAL_UART_GetState(&huart2) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_2_RX_RING, UART_2_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_2_TX_DB, UART_2_TX_BUFFER1,UART_2_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
#ifdef UART_2_DMA_TX
		UART_2_STRUCT.TXDMA = true;
#else
		UART_2_STRUCT.TXDMA = false;
#endif
#ifdef UART_2_DMA_RX
		UART_2_STRUCT.RXDMA = true;
#else
		UART_2_STRUCT.RXDMA = false;
#endif
		UARTSetup(&UART_2_STRUCT, &huart2, &UART_2_RX_RING, &UART_2_TX_DB,ISRBuffer_2);
		if (UART_2_STRUCT.RXDMA == true){
			HAL_UART_Receive_DMA(UART_2_STRUCT.uartHandler, ISRBuffer_2, 1);
		}else{
			HAL_UART_Receive_IT(UART_2_STRUCT.uartHandler, UART_2_STRUCT.rxBuffer->buffer, 1);
		}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART2,loopBackUART2Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_2_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_2_STRUCT, testMessage2, sizeof(testMessage2) - 1);
	UARTWriteBuffer(&UART_2_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
	}

#endif//UART_2
#ifdef UART_3
	if (HAL_UART_GetState(&huart3) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_3_RX_RING, UART_3_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_3_TX_DB, UART_3_TX_BUFFER1,UART_3_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
#ifdef UART_3_DMA_TX
		UART_3_STRUCT.TXDMA = true;
#else
		UART_3_STRUCT.TXDMA = false;
#endif
#ifdef UART_3_DMA_RX
		UART_3_STRUCT.RXDMA = true;
#else
		UART_3_STRUCT.RXDMA = false;
#endif
		UARTSetup(&UART_3_STRUCT, &huart3, &UART_3_RX_RING, &UART_3_TX_DB,ISRBuffer_3);
		if (UART_3_STRUCT.RXDMA == true){
			HAL_UART_Receive_DMA(UART_3_STRUCT.uartHandler, ISRBuffer_3, 1);
		}else{
			HAL_UART_Receive_IT(UART_3_STRUCT.uartHandler, UART_3_STRUCT.rxBuffer->buffer, 1);
		}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART3,loopBackUART3Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_3_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_3_STRUCT, testMessage3, sizeof(testMessage3) - 1);
	UARTWriteBuffer(&UART_3_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
	}

#endif//UART_3
#ifdef UART_4
	if (HAL_UART_GetState(&huart4) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_4_RX_RING, UART_4_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_4_TX_DB, UART_4_TX_BUFFER1,UART_4_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
#ifdef UART_4_DMA_TX
		UART_4_STRUCT.TXDMA = true;
#else
		UART_4_STRUCT.TXDMA = false;
#endif
#ifdef UART_4_DMA_RX
		UART_4_STRUCT.RXDMA = true;
#else
		UART_4_STRUCT.RXDMA = false;
#endif
		UARTSetup(&UART_4_STRUCT, &huart4, &UART_4_RX_RING, &UART_4_TX_DB,ISRBuffer_4);
		if (UART_4_STRUCT.RXDMA == true){
			HAL_UART_Receive_DMA(UART_4_STRUCT.uartHandler, ISRBuffer_4, 1);
		}else{
			HAL_UART_Receive_IT(UART_4_STRUCT.uartHandler, UART_4_STRUCT.rxBuffer->buffer, 1);
		}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART4,loopBackUART4Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_4_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_4_STRUCT, testMessage4, sizeof(testMessage4) - 1);
	UARTWriteBuffer(&UART_4_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
	}

#endif//UART_4
#ifdef UART_5
	if (HAL_UART_GetState(&huart5) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_5_RX_RING, UART_5_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_5_TX_DB, UART_5_TX_BUFFER1,UART_5_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
#ifdef UART_5_DMA_TX
		UART_5_STRUCT.TXDMA = true;
#else
		UART_5_STRUCT.TXDMA = false;
#endif
#ifdef UART_5_DMA_RX
		UART_5_STRUCT.RXDMA = true;
#else
		UART_5_STRUCT.RXDMA = false;
#endif
		UARTSetup(&UART_5_STRUCT, &huart5, &UART_5_RX_RING, &UART_5_TX_DB,ISRBuffer_5);
		if (UART_5_STRUCT.RXDMA == true){
			HAL_UART_Receive_DMA(UART_5_STRUCT.uartHandler, ISRBuffer_5, 1);
		}else{
			HAL_UART_Receive_IT(UART_5_STRUCT.uartHandler, UART_5_STRUCT.rxBuffer->buffer, 1);
		}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART5,loopBackUART5Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_5_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_5_STRUCT, testMessage5, sizeof(testMessage5) - 1);
	UARTWriteBuffer(&UART_5_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
	}

#endif//UART_5
#ifdef UART_6
	if (HAL_UART_GetState(&huart6) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_6_RX_RING, UART_6_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_6_TX_DB, UART_6_TX_BUFFER1,UART_6_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
#ifdef UART_6_DMA_TX
		UART_6_STRUCT.TXDMA = true;
#else
		UART_6_STRUCT.TXDMA = false;
#endif
#ifdef UART_6_DMA_RX
		UART_6_STRUCT.RXDMA = true;
#else
		UART_6_STRUCT.RXDMA = false;
#endif
		UARTSetup(&UART_6_STRUCT, &huart6, &UART_6_RX_RING, &UART_6_TX_DB,ISRBuffer_6);
		if (UART_6_STRUCT.RXDMA == true){
			HAL_UART_Receive_DMA(UART_6_STRUCT.uartHandler, ISRBuffer_6, 1);
		}else{
			HAL_UART_Receive_IT(UART_6_STRUCT.uartHandler, UART_6_STRUCT.rxBuffer->buffer, 1);
		}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART6,loopBackUART6Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_6_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_6_STRUCT, testMessage6, sizeof(testMessage6) - 1);
	UARTWriteBuffer(&UART_6_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
	}

#endif//UART_6
#ifdef UART_7
	if (HAL_UART_GetState(&huart7) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_7_RX_RING, UART_7_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_7_TX_DB, UART_7_TX_BUFFER1,UART_7_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
#ifdef UART_7_DMA_TX
		UART_7_STRUCT.TXDMA = true;
#else
		UART_7_STRUCT.TXDMA = false;
#endif
#ifdef UART_7_DMA_RX
		UART_7_STRUCT.RXDMA = true;
#else
		UART_7_STRUCT.RXDMA = false;
#endif
		UARTSetup(&UART_7_STRUCT, &huart7, &UART_7_RX_RING, &UART_7_TX_DB,ISRBuffer_7);
		if (UART_7_STRUCT.RXDMA == true){
			HAL_UART_Receive_DMA(UART_7_STRUCT.uartHandler, ISRBuffer_7, 1);
		}else{
			HAL_UART_Receive_IT(UART_7_STRUCT.uartHandler, UART_7_STRUCT.rxBuffer->buffer, 1);
		}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART7,loopBackUART7Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_7_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_7_STRUCT, testMessage7, sizeof(testMessage7) - 1);
	UARTWriteBuffer(&UART_7_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
	}

#endif//UART_7
#ifdef UART_8
	if (HAL_UART_GetState(&huart8) != HAL_UART_STATE_RESET){
		RingBufferCreate(&UART_8_RX_RING, UART_8_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
		DoubleBufferCreate(&UART_8_TX_DB, UART_8_TX_BUFFER1,UART_8_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
#ifdef UART_8_DMA_TX
		UART_8_STRUCT.TXDMA = true;
#else
		UART_8_STRUCT.TXDMA = false;
#endif
#ifdef UART_8_DMA_RX
		UART_8_STRUCT.RXDMA = true;
#else
		UART_8_STRUCT.RXDMA = false;
#endif
		UARTSetup(&UART_8_STRUCT, &huart8, &UART_8_RX_RING, &UART_8_TX_DB,ISRBuffer_8);
		if (UART_8_STRUCT.RXDMA == true){
			HAL_UART_Receive_DMA(UART_8_STRUCT.uartHandler, ISRBuffer_8, 1);
		}else{
			HAL_UART_Receive_IT(UART_8_STRUCT.uartHandler, UART_8_STRUCT.rxBuffer->buffer, 1);
		}
#ifdef LOOP_BACK_DEMO
	RingBufferCreate(&loopBackUART8,loopBackUART8Buffer,UART_RING_BUF_SIZE_RX);
	UARTWriteBuffer(&UART_8_STRUCT, testMessage0, sizeof(testMessage0) - 1);
	UARTWriteBuffer(&UART_8_STRUCT, testMessage8, sizeof(testMessage8) - 1);
	UARTWriteBuffer(&UART_8_STRUCT, testMessage0, sizeof(testMessage0) - 1);
#endif
	}

#endif//UART_8
}
//general
int UARTWriteBuffer(UART_STRUCT* uartS, uint8_t* buff, int n) {
	n = DoubleBufferWrite(uartS->txBuffer, buff, n);

	if (n == -1){
		uartS->TXOverRun = true;
		return n;
	}
	if (DoubleBufferAvailable(uartS->txBuffer) > 0){
		if (uartS->TXDMA == true){
			if (HAL_UART_Transmit_DMA(uartS->uartHandler, uartS->txBuffer->buffer, DoubleBufferAvailable(uartS->txBuffer)) != HAL_BUSY) {
				DoubleBufferSwap(uartS->txBuffer);
			}
		}else{
			if (HAL_UART_Transmit_IT(uartS->uartHandler, uartS->txBuffer->buffer, DoubleBufferAvailable(uartS->txBuffer)) != HAL_BUSY) {
				DoubleBufferSwap(uartS->txBuffer);
			}
		}

	}
	return n;

}

int UARTAvailabe(UART_STRUCT* uartS) {
	return RingBufferAvailable(uartS->rxBuffer);
}

int UARTGetBuffer(UART_STRUCT* uartS, uint8_t* buff, int n) {
	return RingBufferRead(uartS->rxBuffer,buff,n);
}

//call backs
void UARTTXCallBackHandler(UART_STRUCT* uartS) {
	if (uartS->txBuffer->writing == true) {
		return;
	}
	if (DoubleBufferAvailable(uartS->txBuffer) > 0){
		if (uartS->TXDMA == true){
			if (HAL_UART_Transmit_DMA(uartS->uartHandler, uartS->txBuffer->buffer, DoubleBufferAvailable(uartS->txBuffer)) != HAL_BUSY) {
				DoubleBufferSwap(uartS->txBuffer);
			}
		}else{
			if (HAL_UART_Transmit_IT(uartS->uartHandler, uartS->txBuffer->buffer, DoubleBufferAvailable(uartS->txBuffer)) != HAL_BUSY) {
				DoubleBufferSwap(uartS->txBuffer);
			}
		}
	}
}
void UARTRXCallBackHandler(UART_STRUCT* uartS) {

	if (uartS->RXDMA == true){
		RingBufferWriteByte(uartS->rxBuffer,uartS->ISRBuf);

	}else{
		uartS->rxBuffer->readIdxTemp = uartS->rxBuffer->readIdx;
		if (uartS->rxBuffer->readIdxTemp == ((uartS->rxBuffer->writeIdx + 1) % uartS->rxBuffer->size)){
			uartS->rxBuffer->full = true;
		}

		if (uartS->rxBuffer->readIdxTemp == ((uartS->rxBuffer->writeIdx + 1) % uartS->rxBuffer->size)){
			uartS->RXOverRun = true;
		}else{
			uartS->rxBuffer->writeIdx = (uartS->rxBuffer->writeIdx + (1)) % uartS->rxBuffer->size;

		}
		if (uartS->uartHandler->RxState == HAL_UART_STATE_READY){
			uartS->uartHandler->RxState = HAL_UART_STATE_BUSY_RX;
			uartS->uartHandler->pRxBuffPtr = uartS->rxBuffer->buffer + uartS->rxBuffer->writeIdx;
			uartS->uartHandler->RxXferSize = 1;
			uartS->uartHandler->RxXferCount = 1;
			uartS->uartHandler->ErrorCode = HAL_UART_ERROR_NONE;
			SET_BIT(uartS->uartHandler->Instance->CR1, USART_CR1_PEIE);
			SET_BIT(uartS->uartHandler->Instance->CR3, USART_CR3_EIE);
			SET_BIT(uartS->uartHandler->Instance->CR1, USART_CR1_RXNEIE);
		  }
		__HAL_UART_FLUSH_DRREGISTER(uartS->uartHandler);
	}



}
//TX
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

//RX
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
//end call back
//loop back demo
#ifdef LOOP_BACK_DEMO
void UARTLoopDemo(){
	int bytesOut;
#ifdef UART_1
	static uint32_t uart1Timer;

	if (UARTAvailabe(&UART_1_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_1_STRUCT,loopBackBuffer,UARTAvailabe(&UART_1_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART1,loopBackBuffer,numBytes);
			uart1Timer = HAL_GetTick();
		}
	}
	if ((RingBufferAvailable(&loopBackUART1) > (UART_RING_BUF_SIZE_RX / 2)) || ((HAL_GetTick() - uart1Timer) > 100)  ){
		if (RingBufferAvailable(&loopBackUART1) > 0){
			numBytes = RingBufferRead(&loopBackUART1,loopBackBuffer,RingBufferAvailable(&loopBackUART1));
			if (numBytes > 0){
				bytesOut = UARTWriteBuffer(&UART_1_STRUCT,loopBackBuffer,numBytes);
				if (bytesOut < 0){
					RingBufferWrite(&loopBackUART1,loopBackBuffer,numBytes);
				}else{
					RingBufferWrite(&loopBackUART1,loopBackBuffer + bytesOut,numBytes - bytesOut);
				}

			}
		}
	}
#endif
#ifdef UART_2
	static uint32_t uart2Timer;

	if (UARTAvailabe(&UART_2_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_2_STRUCT,loopBackBuffer,UARTAvailabe(&UART_2_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART2,loopBackBuffer,numBytes);
			uart2Timer = HAL_GetTick();
		}
	}
	if ((RingBufferAvailable(&loopBackUART2) > (UART_RING_BUF_SIZE_RX / 2)) || ((HAL_GetTick() - uart2Timer) > 100)  ){
		if (RingBufferAvailable(&loopBackUART2) > 0){
			numBytes = RingBufferRead(&loopBackUART2,loopBackBuffer,RingBufferAvailable(&loopBackUART2));
			if (numBytes != -1){
				bytesOut = UARTWriteBuffer(&UART_2_STRUCT,loopBackBuffer,numBytes);
				if (numBytes < 0){
					RingBufferWrite(&loopBackUART2,loopBackBuffer,numBytes);
				}else{
					RingBufferWrite(&loopBackUART2,loopBackBuffer + bytesOut,numBytes - bytesOut);
				}

			}
		}
	}
#endif
#ifdef UART_3
	static uint32_t uart3Timer;

	if (UARTAvailabe(&UART_3_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_3_STRUCT,loopBackBuffer,UARTAvailabe(&UART_3_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART3,loopBackBuffer,numBytes);
			uart3Timer = HAL_GetTick();
		}
	}
	if ((RingBufferAvailable(&loopBackUART3) > (UART_RING_BUF_SIZE_RX / 2)) || ((HAL_GetTick() - uart3Timer) > 100)  ){
		if (RingBufferAvailable(&loopBackUART3) > 0){
			numBytes = RingBufferRead(&loopBackUART3,loopBackBuffer,RingBufferAvailable(&loopBackUART3));
			if (numBytes != -1){
				bytesOut = UARTWriteBuffer(&UART_3_STRUCT,loopBackBuffer,numBytes);
				if (numBytes < 0){
					RingBufferWrite(&loopBackUART3,loopBackBuffer,numBytes);
				}else{
					RingBufferWrite(&loopBackUART3,loopBackBuffer + bytesOut,numBytes - bytesOut);
				}

			}
		}
	}
#endif
#ifdef UART_4
	static uint32_t uart4Timer;

	if (UARTAvailabe(&UART_4_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_4_STRUCT,loopBackBuffer,UARTAvailabe(&UART_4_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART4,loopBackBuffer,numBytes);
			uart4Timer = HAL_GetTick();
		}
	}
	if ((RingBufferAvailable(&loopBackUART4) > (UART_RING_BUF_SIZE_RX / 2)) || ((HAL_GetTick() - uart4Timer) > 100)  ){
		if (RingBufferAvailable(&loopBackUART4) > 0){
			numBytes = RingBufferRead(&loopBackUART4,loopBackBuffer,RingBufferAvailable(&loopBackUART4));
			if (numBytes != -1){
				bytesOut = UARTWriteBuffer(&UART_4_STRUCT,loopBackBuffer,numBytes);
				if (numBytes < 0){
					RingBufferWrite(&loopBackUART4,loopBackBuffer,numBytes);
				}else{
					RingBufferWrite(&loopBackUART4,loopBackBuffer + bytesOut,numBytes - bytesOut);
				}

			}
		}
	}
#endif
#ifdef UART_5
	static uint32_t uart5Timer;

	if (UARTAvailabe(&UART_5_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_5_STRUCT,loopBackBuffer,UARTAvailabe(&UART_5_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART5,loopBackBuffer,numBytes);
			uart5Timer = HAL_GetTick();
		}
	}
	if ((RingBufferAvailable(&loopBackUART5) > (UART_RING_BUF_SIZE_RX / 2)) || ((HAL_GetTick() - uart5Timer) > 100)  ){
		if (RingBufferAvailable(&loopBackUART5) > 0){
			numBytes = RingBufferRead(&loopBackUART5,loopBackBuffer,RingBufferAvailable(&loopBackUART5));
			if (numBytes != -1){
				bytesOut = UARTWriteBuffer(&UART_5_STRUCT,loopBackBuffer,numBytes);
				if (numBytes < 0){
					RingBufferWrite(&loopBackUART5,loopBackBuffer,numBytes);
				}else{
					RingBufferWrite(&loopBackUART5,loopBackBuffer + bytesOut,numBytes - bytesOut);
				}

			}
		}
	}
#endif
#ifdef UART_6
	static uint32_t uart6Timer;

	if (UARTAvailabe(&UART_6_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_6_STRUCT,loopBackBuffer,UARTAvailabe(&UART_6_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART6,loopBackBuffer,numBytes);
			uart6Timer = HAL_GetTick();
		}
	}
	if ((RingBufferAvailable(&loopBackUART6) > (UART_RING_BUF_SIZE_RX / 2)) || ((HAL_GetTick() - uart6Timer) > 100)  ){
		if (RingBufferAvailable(&loopBackUART6) > 0){
			numBytes = RingBufferRead(&loopBackUART6,loopBackBuffer,RingBufferAvailable(&loopBackUART6));
			if (numBytes != -1){
				bytesOut = UARTWriteBuffer(&UART_6_STRUCT,loopBackBuffer,numBytes);
				if (numBytes < 0){
					RingBufferWrite(&loopBackUART6,loopBackBuffer,numBytes);
				}else{
					RingBufferWrite(&loopBackUART6,loopBackBuffer + bytesOut,numBytes - bytesOut);
				}

			}
		}
	}
#endif
#ifdef UART_7
	static uint32_t uart7Timer;

	if (UARTAvailabe(&UART_7_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_7_STRUCT,loopBackBuffer,UARTAvailabe(&UART_7_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART7,loopBackBuffer,numBytes);
			uart7Timer = HAL_GetTick();
		}
	}
	if ((RingBufferAvailable(&loopBackUART7) > (UART_RING_BUF_SIZE_RX / 2)) || ((HAL_GetTick() - uart7Timer) > 100)  ){
		if (RingBufferAvailable(&loopBackUART7) > 0){
			numBytes = RingBufferRead(&loopBackUART7,loopBackBuffer,RingBufferAvailable(&loopBackUART7));
			if (numBytes != -1){
				bytesOut = UARTWriteBuffer(&UART_7_STRUCT,loopBackBuffer,numBytes);
				if (numBytes < 0){
					RingBufferWrite(&loopBackUART7,loopBackBuffer,numBytes);
				}else{
					RingBufferWrite(&loopBackUART7,loopBackBuffer + bytesOut,numBytes - bytesOut);
				}

			}
		}
	}
#endif
#ifdef UART_8
	static uint32_t uart8Timer;

	if (UARTAvailabe(&UART_8_STRUCT) > 0){
		numBytes = UARTGetBuffer(&UART_8_STRUCT,loopBackBuffer,UARTAvailabe(&UART_8_STRUCT));
		if (numBytes != -1){
			RingBufferWrite(&loopBackUART8,loopBackBuffer,numBytes);
			uart8Timer = HAL_GetTick();
		}
	}
	if ((RingBufferAvailable(&loopBackUART8) > (UART_RING_BUF_SIZE_RX / 2)) || ((HAL_GetTick() - uart8Timer) > 100)  ){
		if (RingBufferAvailable(&loopBackUART8) > 0){
			numBytes = RingBufferRead(&loopBackUART8,loopBackBuffer,RingBufferAvailable(&loopBackUART8));
			if (numBytes != -1){
				bytesOut = UARTWriteBuffer(&UART_8_STRUCT,loopBackBuffer,numBytes);
				if (numBytes < 0){
					RingBufferWrite(&loopBackUART8,loopBackBuffer,numBytes);
				}else{
					RingBufferWrite(&loopBackUART8,loopBackBuffer + bytesOut,numBytes - bytesOut);
				}

			}
		}
	}
#endif
}
#endif
//end uart-------------------------------------------------------
//buffers
void DoubleBufferCreate(DoubleBuffer_t *tb, uint8_t *buffer0, uint8_t *buffer1,int sizeOfBuffer){
	tb->buffer0 = buffer0;
	tb->buffer1 = buffer1;
	tb->buffer = tb->buffer0;
	tb->size = sizeOfBuffer;
	tb->writeIdx = 0;
	tb->useBuffer0 = true;
	tb->writing = false;
}
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
void DoubleBufferSwap(DoubleBuffer_t *tb){
	tb->writeIdx = 0;
	tb->useBuffer0 ^= true;
	if (tb->useBuffer0 == true){
		tb->buffer = tb->buffer0;
	}else{
		tb->buffer = tb->buffer1;
	}

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
	rb->reading = false;
	rb->full = false;
}
int RingBufferWriteByte(RingBuffer_t *rb, uint8_t *in) {
	if (rb->full == true){
		return -1;
	}
	if (rb->reading == false){
		if (rb->writeIdx == rb->readIdxTemp){
			rb->writeIdx = rb->readIdx = 0;
		}
	}
	rb->buffer[rb->writeIdx] = in[0];
	if (rb->readIdxTemp == ((rb->writeIdx + 1) % rb->size)){
		rb->full = true;
	}
	rb->writeIdx = (rb->writeIdx + (1)) % rb->size;
	return 1;

}


int RingBufferWrite(RingBuffer_t *rb, uint8_t *in, int count) {
	if ((count <= 0) || (count > UART_RING_BUF_SIZE_RX)){
		return -2;//check for bad requested size
	}
	rb->readIdxTemp = rb->readIdx;
	if (rb->full == true){
		return -1;
	}
	//get # available to write
	rb->availableWrite = rb->writeIdx - rb->readIdxTemp;
	if (rb->availableWrite <= 0){
		rb->availableWrite += rb->size;
	}
	if ((rb->availableWrite == rb->size) && (rb->reading == false)){
		rb->writeIdx = rb->readIdx = 0;//if buffer empty reset pointers to start of buffer
	}
	if (count >= rb->availableWrite){//requested to write more bytes than space
		count = rb->availableWrite;
		if (RingWriteIdxToEnd(rb) >= count){//write to buffer
			memcpy(rb->buffer + rb->writeIdx, in, count);
		}else{//handle wrap
			memcpy(rb->buffer + rb->writeIdx, in, RingWriteIdxToEnd(rb));
			memcpy(rb->buffer, in + RingWriteIdxToEnd(rb), count - RingWriteIdxToEnd(rb));
		}
		rb->full = true;

	}else{
		if (RingWriteIdxToEnd(rb) >= count){//write to buffer
			memcpy(rb->buffer + rb->writeIdx, in, count);
		}else{//handle wrap
			memcpy(rb->buffer + rb->writeIdx, in, RingWriteIdxToEnd(rb));
			memcpy(rb->buffer, in + RingWriteIdxToEnd(rb), count - RingWriteIdxToEnd(rb));
		}
	}
	RingBufferCommitWrite(rb, count);
	return count;

}
int RingBufferRead(RingBuffer_t *rb, uint8_t *out, int count){
	if ((count <= 0) || (count > UART_RING_BUF_SIZE_RX)){
		return -2;//check for bad requested size
	}
	rb->reading = true;
	rb->writeIdxTemp = rb->writeIdx;
	if (rb->full == true){
		rb->availableRead = rb->size;
	}else{
		if (rb->writeIdxTemp == rb->readIdx){
			return -1;
		}
		rb->availableRead = rb->writeIdxTemp - rb->readIdx;
		if (rb->availableRead < 0){//get number of bytes in buffer
			rb->availableRead += rb->size;
		}
	}
	if (count > rb->availableRead){
		count = rb->availableRead;
	}
	if (rb->readIdx < rb->writeIdxTemp){
		memcpy(out, rb->buffer + rb->readIdx, count);
		RingBufferCommitRead(rb,count);
	}else{
		if (RingReadIdxToEnd(rb) >= count){
			memcpy(out, rb->buffer + rb->readIdx, count);
		}else{
			memcpy(out, rb->buffer + rb->readIdx, RingReadIdxToEnd(rb));
			memcpy(out, rb->buffer , count - RingReadIdxToEnd(rb));
		}
	}
	RingBufferCommitRead(rb,count);
	rb->full = false;
	rb->reading = false;
	return count;

}

//end buffers-------------------------------------------------------
//ERROR CB
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
	//printf("u E: %i\nu S: %i\n", (int) HAL_UART_GetError(huart),(int) HAL_UART_GetState(huart));

}
