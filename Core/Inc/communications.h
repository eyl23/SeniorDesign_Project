#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H
#include "main.h"
#include <cstring>

class UART {
public:
	uint8_t buffer_uart[128];
	void transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
	void receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	void test();
private:
	bool testUART(UART_HandleTypeDef *huart);
};

class SPI{
public:
	uint16_t data;
	void transmit(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
	void receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	void test();
private:
	bool testSPI(SPI_HandleTypeDef *hspi);
};

class CAN {
public:
	uint16_t data[128];
	void transmit(FDCAN_HandleTypeDef *hfdcan, const FDCAN_TxHeaderTypeDef *pTxHeader, const uint8_t *pTxData, uint32_t BufferIndex);
	void receive(FDCAN_HandleTypeDef *hfdcan, uint32_t RxLocation,FDCAN_RxHeaderTypeDef *pRxHeader, uint8_t *pRxData);
	void test();
private:
	bool testCAN(FDCAN_HandleTypeDef *hfdcan);

};



#endif
