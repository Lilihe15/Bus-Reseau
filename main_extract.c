#include "main.h"
#include "can.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include <string.h>
#include <stdio.h>
#include "BMP280.h"

#define BUF_SIZE 100
#define SIZE_CAN_TRANSMIT 8 // Messages sur 8 uint_8

#define ANGLE 0x61 // Arbitration ID for Angle command

#define RIGHT_TURN 90 // for 90 degrees

CAN_TxHeaderTypeDef pHeader;
uint8_t aData[2];
uint8_t buffer;
uint32_t pTxMailbox; // Sera modifie par la fonction d'envoie de messages "HAL_CAN_AddTxMessage"

void SystemClock_Config(void);

int main(void)
{
	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_UART5_Init();
	MX_TIM3_Init();
	MX_CAN1_Init();
	MX_I2C1_Init();

	printf("\r\nChecking for BMP280\r\n"); // Capteur
	BMP280_check();
	printf("\r\nConfigure BMP280\r\n");
	BMP280_init();

	HAL_CAN_Start(&hcan1); // Renvoie un HAL_StatusTypeDef

	aData[0] = RIGHT_TURN;

	aData[1] = 0x00;
	pHeader.StdId = 0x61; // Standart identifier between 0 and 0x7FF (sur 11 bits donc)
	// &pHeader->ExtId = ; // Extended identifier between 0 and 0x1FFFFFFF
	pHeader.IDE = CAN_ID_STD;
	pHeader.RTR = CAN_RTR_DATA;
	pHeader.DLC = 2;
	pHeader.TransmitGlobalTime = DISABLE;

	while (1)
	{
		BMP280_U32_t pressure_pa = bmp280_compensate_P_int64(BMP280_get_pressure());
		BMP280_S32_t temp_celsius = bmp280_compensate_T_int32(BMP280_get_temperature());

		printf("Pression : %d Pa\n\r", (int)pressure_pa/256); // Sinon trop de chiffres significatifs
		printf("Temperature : %d,%d °C\n\r", (int)temp_celsius/100, (int)temp_celsius%100);

        	aData[1] = (aData[1]+1)%2;   //Moteur rotation 90° alternance du sens de rotation

        	HAL_CAN_AddTxMessage(&hcan1, &pHeader, aData, &pTxMailbox);

        	HAL_Delay(1000);
	}
}
