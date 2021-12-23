/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_
#define __GPIO_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"
#include "stm32f4xx_rcc_mort.h"


/*Function definitions---------------------------------------------------------*/

//initialize pin 0 as PWM
void initialize_GPIOB_pin0(void);

//initialize gpioF7
void initGPIOF7AsAnalog(void);

//initialize pin PC8 for switch rising edge
void initialize_GPIOC_pinPC8(void);

//determine if pin 8 is currently high or low
uint8_t is_GPIOC_pinPC8_high(void);

//determine if pin 9 is currently high or low
uint8_t is_GPIOC_pinPC9_high(void);

//initialize pin PC9 for LED strip
void initialize_GPIOC_pinPC9(void); 

//pin PC9 high
void GPIOC_pinPC9_high(void);

//pin PC9 low
void GPIOC_pinPC9_low(void);

//get the 0 or 1 state of the specified pin 
uint16_t getGPIOBpinState(uint16_t index);

//initialize the 6 digital input pins for magnetic sensors
void init_GPIOB_pin_0To5( void );


#ifdef __cplusplus
}
#endif

#endif /*__GPIO */