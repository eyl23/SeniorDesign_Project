#include "microcontroller.h"
#include "main.h"
#include <cstring>
//Changing it from the main.c file to this microcontroller.cpp file. Functions for initialization
extern UART_HandleTypeDef huart3;
extern FDCAN_HandleTypeDef hfdcan1;
extern ADC_HandleTypeDef hadc1;
extern SPI_HandleTypeDef hspi1;

extern "C" void SystemClock_Config(void);
extern "C" void MX_GPIO_Init(void);
extern "C" void MX_DMA_Init(void);
extern "C" void MX_ADC1_Init(void);
extern "C" void MX_TIM3_Init(void);
extern "C" void MX_FDCAN1_Init(void);
extern "C" void MX_SPI1_Init(void);
extern "C" void MX_USART3_UART_Init(void);
extern "C" void MPU_Config(void);



// Optional: extern declaration for HAL_ADC_Start if you're calling it

HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc1);


//Sending messages to the serial port
void UARTtxMessage(const char* msg) {
    HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}



void Microcontroller::testFDCAN() {
    MX_FDCAN1_Init();
    UARTtxMessage("Initialized FDCAN \r\n");

    // === Configure TX Header ===
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

    if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK) {
        UARTtxMessage("FDCAN Filter Config Failed\r\n");
        return;
    }

    // === Start CAN Peripheral ===
    if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK) {
        UARTtxMessage("FDCAN Start Failed\r\n");
        return;
    }

    // === Add Message to TX Buffer ===
    uint8_t TxData[8] = {0x10, 0x32, 0x54, 0x76, 0x98, 0x00, 0x11, 0x22};
    if (HAL_FDCAN_AddMessageToTxBuffer(&hfdcan1, &TxHeader, TxData, FDCAN_TX_BUFFER0) != HAL_OK) {
        UARTtxMessage("Add to TX Buffer Failed\r\n");
        return;
    }

    // === Request Transmission ===
    if (HAL_FDCAN_EnableTxBufferRequest(&hfdcan1, FDCAN_TX_BUFFER0) != HAL_OK) {
        UARTtxMessage("TX Buffer Request Failed\r\n");
        return;
    }


    UARTtxMessage("FDCAN Message Sent!\r\n");
}


void Microcontroller::testSPI() {
    MX_SPI1_Init();
	UARTtxMessage("Initialized SPI \r\n");

	uint8_t txData[] = {0xAA, 0x55};
	uint8_t rxData[2] = {};
	if (HAL_SPI_TransmitReceive(&hspi1, txData, rxData, sizeof(txData), HAL_MAX_DELAY) == HAL_OK) {
		UARTtxMessage("SPI is Working!\r\n");
	}
	else {
		UARTtxMessage("SPI is NOT Working...\r\n");
	}

}

void Microcontroller::testADC() {
	MX_ADC1_Init();
	HAL_ADC_Start(&hadc1);
	UARTtxMessage("Initialized ADC \r\n");

	if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
		UARTtxMessage("ADC is Working! \r\n");
	}
	else {
		UARTtxMessage("ADC is Working... \r\n");
	}
}

void Microcontroller::testUART() {
	MX_USART3_UART_Init();
    if (HAL_UART_Transmit(&huart3, (const uint8_t*)"Test UART Message\r\n", strlen("Test UART Message\r\n"), HAL_MAX_DELAY) == HAL_OK){
    	UARTtxMessage("UART is Working! \r\n");
	}
	else {
		UARTtxMessage("UART is NOT Working! \r\n");
	}

}

void Microcontroller:: test() {

		MPU_Config();
		HAL_Init();
		MX_GPIO_Init();
		MX_TIM3_Init();
		SystemClock_Config();
		testUART();
	    testFDCAN();
	    testSPI();
	    testADC();
		UARTtxMessage("Finished Testing \r\n");
}
