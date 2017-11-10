/*
 * cats_init.c
 *
 *  Created on: Oct 22, 2017
 *      Author: darklyght
 */

#include "cats_init.h"

/******************************************************************************//*
 * @brief 		Initialise all peripherals
 * @param[in]	None
 * @return 		None
 *******************************************************************************/
void init_peripherals() {
	init_ssp();
	init_i2c();
	init_uart();
	sseg_init();
	oled_init();
	oled_clearScreen(OLED_COLOR_BLACK);
	sw3_init();
	acc_calibrate();
	acc_interrupt_init();
	temperature_init();
	temperature_start();
	lights_init();
	pca9532_init();
	rgb_init();
	amp_init();
	NVIC_SetPriorityGrouping(0);
	NVIC_SetPriority(EINT0_IRQn, NVIC_EncodePriority(0, 6, 0));
	NVIC_SetPriority(EINT1_IRQn, NVIC_EncodePriority(0, 6, 0));
	NVIC_SetPriority(EINT2_IRQn, NVIC_EncodePriority(0, 6, 0));
	NVIC_SetPriority(EINT3_IRQn, NVIC_EncodePriority(0, 7, 0));
	NVIC_SetPriority(TIMER2_IRQn, NVIC_EncodePriority(0, 8, 0));
	NVIC_SetPriority(UART3_IRQn, NVIC_EncodePriority(0, 6, 0));
	NVIC_ClearPendingIRQ(EINT0_IRQn);
	NVIC_ClearPendingIRQ(EINT1_IRQn);
	NVIC_ClearPendingIRQ(EINT2_IRQn);
	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_ClearPendingIRQ(TIMER2_IRQn);
	NVIC_ClearPendingIRQ(UART3_IRQn);
	NVIC_EnableIRQ(EINT0_IRQn);
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_EnableIRQ(EINT2_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);
	NVIC_EnableIRQ(TIMER2_IRQn);
	NVIC_EnableIRQ(UART3_IRQn);
}

/******************************************************************************//*
 * @brief 		Initialise SSP1
 * @param[in]	None
 * @return 		None
 *******************************************************************************/
void init_ssp(void) {
	SSP_CFG_Type SSP_ConfigStruct;
	PINSEL_CFG_Type PinCfg;

	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 7;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Funcnum = 0;
	PinCfg.Portnum = 2;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);

	SSP_ConfigStructInit(&SSP_ConfigStruct);

	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);

	SSP_Cmd(LPC_SSP1, ENABLE);
}

/******************************************************************************//*
 * @brief 		Initialise I2C2
 * @param[in]	None
 * @return 		None
 *******************************************************************************/
void init_i2c(void) {
	PINSEL_CFG_Type PinCfg;

	PinCfg.Funcnum = 2;
	PinCfg.Pinnum = 10;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 11;
	PINSEL_ConfigPin(&PinCfg);

	I2C_Init(LPC_I2C2, 100000);

	I2C_Cmd(LPC_I2C2, ENABLE);
}

/******************************************************************************//*
 * @brief 		Initialise UART3
 * @param[in]	None
 * @return 		None
 *******************************************************************************/
void init_uart(void) {
	UART_CFG_Type uartCfg;
	PINSEL_CFG_Type PinCfg;

	uartCfg.Baud_rate = 115200;
	uartCfg.Databits = UART_DATABIT_8;
	uartCfg.Parity = UART_PARITY_NONE;
	uartCfg.Stopbits = UART_STOPBIT_1;

	PinCfg.Funcnum = 2;
	PinCfg.Pinnum = 0;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 1;
	PINSEL_ConfigPin(&PinCfg);

	UART_Init(LPC_UART3, &uartCfg);

	UART_TxCmd(LPC_UART3, ENABLE);

	UART_FIFO_CFG_Type fifoCfg;
	fifoCfg.FIFO_ResetRxBuf = ENABLE;
	fifoCfg.FIFO_ResetTxBuf = ENABLE;
	fifoCfg.FIFO_DMAMode = DISABLE;
	fifoCfg.FIFO_Level = UART_FIFO_TRGLEV0;

	UART_IntConfig(LPC_UART3, UART_INTCFG_RBR, ENABLE);
	UART_FIFOConfig(LPC_UART3, &fifoCfg);
}
