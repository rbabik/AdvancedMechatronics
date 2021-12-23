/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H_
#define __GPIO_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_rcc_mort.h"


/*Function definitions---------------------------------------------------------*/

//initialize pin PC8 for switch rising edge
void initialize_GPIOC_pinPC8(void);

//initialize pin PC9 for LED input 1
void initialize_GPIOC_pinPC9(void);

//initialize pin PC10 for LED input 2
void initialize_GPIOC_pinPC10(void);

//initialize pin PC11 for LED input 3
void initialize_GPIOC_pinPC11(void);

//initialize pin PC12 for phototransistor
void initialize_GPIOC_pinPC12(void);

//pin PC9 high
void GPIOC_pinPC9_high(void);

//pin PC9 low
void GPIOC_pinPC9_low(void);

//pin PC10 high
void GPIOC_pinPC10_high(void);

//pin PC10 low
void GPIOC_pinPC10_low(void);

//pin PC11 high
void GPIOC_pinPC11_high(void);

//pin PC11 low
void GPIOC_pinPC11_low(void);

//determine if pin 12 is currently high or low
uint8_t is_GPIOC_pinPC12_high(void);

//determine if pin 8 is currently high or low
uint8_t is_GPIOC_pinPC8_high(void);

#ifdef __cplusplus
}
#endif

#endif /*__GPIOTASK1_H_ */