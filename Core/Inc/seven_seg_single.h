/*
 * seven_seg_single.h
 *
 *  Created on: Aug 3, 2023
 *      Author: batuh
 */

#ifndef INC_SEVEN_SEG_SINGLE_H_
#define INC_SEVEN_SEG_SINGLE_H_

typedef enum
{
  DOT_DEACTIVE = 0,
  DOT_ACTIVE
}DOT_STATE;

void SEVEN_SEG_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void sevenSegSingleWrite(GPIO_TypeDef* GPIOx, uint8_t number, uint8_t DOT_STATE);

#endif /* INC_SEVEN_SEG_SINGLE_H_ */
