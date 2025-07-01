#include <communications.h>
extern UART_HandleTypeDef huart3;
extern FDCAN_HandleTypeDef hfdcan1;
extern ADC_HandleTypeDef hadc1;
extern SPI_HandleTypeDef hspi1;

void UART:: transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout ){
	HAL_UART_Transmit(huart, pData, Size, Timeout);
};

void UART:: receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout) {
	HAL_UART_Receive(huart, pData, Size, Timeout);
};

void UART:: test(){
};

bool UART:: testUART(UART_HandleTypeDef *huart) {
    if (HAL_UART_Transmit(huart, (const uint8_t*)"Test UART Message\r\n", strlen("Test UART Message\r\n"), HAL_MAX_DELAY) == HAL_OK){
    	return true;
	}
	else {
		return false;
	}
};

void SPI:: transmit(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size, uint32_t Timeout){

	HAL_SPI_Transmit(hspi,pData, Size, Timeout);
};

void SPI:: receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout){
	HAL_SPI_Receive(hspi,pData, Size, Timeout);
};

void SPI:: test(){
};

bool SPI :: testSPI(SPI_HandleTypeDef *hspi) {
	uint8_t txData[] = {0xAA, 0x55};
	uint8_t rxData[2] = {};
	if (HAL_SPI_Transmit(hspi, txData, rxData, sizeof(txData)) == HAL_OK) {
		return true;
	}
	else {
		return false;
	}
};

void CAN:: transmit(FDCAN_HandleTypeDef *hfdcan, const FDCAN_TxHeaderTypeDef *pTxHeader, const uint8_t *pTxData, uint32_t BufferIndex){
	HAL_FDCAN_AddMessageToTxBuffer(hfdcan, pTxHeader,pTxData, BufferIndex);
};

void CAN:: receive(FDCAN_HandleTypeDef *hfdcan, uint32_t RxLocation,FDCAN_RxHeaderTypeDef *pRxHeader, uint8_t *pRxData) {
	HAL_FDCAN_GetRxMessage(hfdcan, RxLocation,pRxHeader, pRxData);
};

void CAN:: test() {

};

bool CAN:: testCAN(FDCAN_HandleTypeDef *hfdcan){

		FDCAN_TxHeaderTypeDef TxHeader = {};
	    TxHeader.Identifier = 0x123;
	    TxHeader.IdType = FDCAN_STANDARD_ID;
	    TxHeader.TxFrameType = FDCAN_DATA_FRAME;
	    TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	    TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	    TxHeader.BitRateSwitch = FDCAN_BRS_ON;
	    TxHeader.FDFormat = FDCAN_FD_CAN;
	    TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	    TxHeader.MessageMarker = 0x0;

	    // === Configure Filter (to RX buffer 0) ===
	    FDCAN_FilterTypeDef sFilterConfig = {};
	    sFilterConfig.IdType = FDCAN_STANDARD_ID;
	    sFilterConfig.FilterIndex = 0;
	    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXBUFFER;
	    sFilterConfig.FilterID1 = 0x2;  // Accept ID 0x2 (for test or echo)
	    sFilterConfig.RxBufferIndex = 0;

	    if (HAL_FDCAN_ConfigFilter(hfdcan, &sFilterConfig) != HAL_OK) {
	       return false;
	    }

	    if (HAL_FDCAN_Start(hfdcan) != HAL_OK) {

		       return false;
	    }

	    uint8_t TxData[8] = {0x10, 0x32, 0x54, 0x76, 0x98, 0x00, 0x11, 0x22};
	    if (HAL_FDCAN_AddMessageToTxBuffer(hfdcan, &TxHeader, TxData, FDCAN_TX_BUFFER0) != HAL_OK) {
		       return false;

	    }

	    if (HAL_FDCAN_EnableTxBufferRequest(hfdcan, FDCAN_TX_BUFFER0) != HAL_OK) {
		       return false;

	    }


return true; 	};
