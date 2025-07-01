#ifndef SYSTEM_H
#define SYSTEM_H
#include "main.h"

class Initializations{
private:
void GPIO_Init();
void DMA_Init();
void ADC_Init();
void TIM_Init();
void FDCAN_Init();
void SPI_Init();
void USART_Init();
};

class Configurations {
private:
void SystemClock_Config();
void MPU_Config();
};

#endif
