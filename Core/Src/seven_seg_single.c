
#include "stm32f4xx_hal.h"
#include "stm32f407xx.h"
#include <math.h>
/*	
 * --*--*--*--*--*--*--*--*--*--
  GPIOx: x------> A,B,C,D,E,F
  For example, if x equals to A, for anode seven segment display pins should be that 
  a---> PA7
  b---> PA6
  c---> PA5
  d---> PA4
  e---> PA3
  f---> PA2
  g---> PA1
  .---> PA0
  --*--*--*--*--*--*--*--*--*--
  GPIO_Pin: x------> GPIO_PIN_0, GPIO_PIN_1, ..., GPIO_PIN_N
  a---> PA7 ---> GPIO_Pin = GPIO_PIN_7
  b---> PA6 ---> GPIO_Pin = GPIO_PIN_6
  c---> PA5 ---> GPIO_Pin = GPIO_PIN_5
  d---> PA4 ---> GPIO_Pin = GPIO_PIN_4
  e---> PA3 ---> GPIO_Pin = GPIO_PIN_3
  f---> PA2 ---> GPIO_Pin = GPIO_PIN_2
  g---> PA1 ---> GPIO_Pin = GPIO_PIN_1
  .---> PA0 ---> GPIO_Pin = GPIO_PIN_0
*/

extern uint16_t pinNumb;
uint16_t pinNumbs;

uint8_t numbs[11]= {
		0x7E,0x30,			// 0 1
		0x6D,0x79,			// 2 3
		0x33,0x5B,			// 4 5
		0x5F,0x70,			// 6 7
		0x7F,0x73,			// 8 9
		0x80				// dot
};



	
void SEVEN_SEG_Init(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  if(GPIOx == GPIOA)
	  __HAL_RCC_GPIOA_CLK_ENABLE();
  if(GPIOx == GPIOB)
	  __HAL_RCC_GPIOB_CLK_ENABLE();
  if(GPIOx == GPIOC)
	  __HAL_RCC_GPIOC_CLK_ENABLE();
  if(GPIOx == GPIOD)
	  __HAL_RCC_GPIOD_CLK_ENABLE();
  if(GPIOx == GPIOE)
	  __HAL_RCC_GPIOE_CLK_ENABLE();
  if(GPIOx == GPIOF)
	  __HAL_RCC_GPIOF_CLK_ENABLE();
  if(GPIOx == GPIOG)
	  __HAL_RCC_GPIOG_CLK_ENABLE();
  if(GPIOx == GPIOH)
	  __HAL_RCC_GPIOH_CLK_ENABLE();
  if(GPIOx == GPIOI)
	  __HAL_RCC_GPIOI_CLK_ENABLE();

  /*Find GPIO_Pin number*/
  for(int i = 0; i < GPIO_Pin; i++){
	  if( pow(2,i) == GPIO_Pin )
	  {
		  pinNumb = i;
	  }
  }
  pinNumbs = pinNumb;
  /*Configure GPIO pin Output Level */
  for(int i= pinNumb; i < pinNumb+8; i++){
	  HAL_GPIO_WritePin(GPIOx, (uint16_t)(pow(2,i)) , GPIO_PIN_SET);
	  GPIO_InitStruct.Pin |= (uint16_t)(pow(2,i));
  }
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void sevenSegSingleWrite(GPIO_TypeDef* GPIOx, uint8_t number, uint8_t DOT_STATE){//DOT_STATE = DOT_DEACTIVE or DOT_ACTİVE

		  for(int k = 0; k<7;k++){
			  if((numbs[number] & (1<<k)) > 0){
				  GPIOx->ODR &= ~(1<<(pinNumb+k+1));
			  }
			  if((numbs[number] & (1<<k)) == 0){
				  GPIOx->ODR |= (1<<(pinNumb+k+1));
			  }

		  }

		  if(DOT_STATE)
			  GPIOx->ODR &= ~(1<<pinNumbs);
		  else
			  GPIOx->ODR |= (1<<pinNumbs);
		  pinNumb=pinNumbs;
  }
