/*
 * led.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */



#include "led.h"


typedef struct
{
	GPIO_TypeDef 	*port;
	uint16_t     	 pin;
	GPIO_PinState	 on_state;
	GPIO_PinState	 off_state;

}led_tbl_t;



led_tbl_t led_tbl[LED_MAX_CH] =
{
         /* LED을 사용할 Port와 Pin을 입력하세요.*/
		{GPIOB, GPIO_PIN_12, GPIO_PIN_RESET, GPIO_PIN_RESET}
};




bool LedInit(void)
{
	bool ret = true;

	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /*Configure GPIO pin : PtPin */
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;


	  for (int i =0; i<LED_MAX_CH; i++)
	  {

		  GPIO_InitStruct.Pin = led_tbl[i].pin;
		  HAL_GPIO_Init(led_tbl[i].port, &GPIO_InitStruct);

		  LedOff(i);

	  }
	return ret;
}



void LedOn(uint8_t ch)
{
	if (ch >= LED_MAX_CH) return;
	HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].on_state);

}



void LedOff(uint8_t ch)
{
	if (ch >= LED_MAX_CH) return;
	HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].off_state);

}



void LedToggle(uint8_t ch)
{
	if (ch >= LED_MAX_CH) return;
	HAL_GPIO_TogglePin(led_tbl[ch].port, led_tbl[ch].pin);

}


