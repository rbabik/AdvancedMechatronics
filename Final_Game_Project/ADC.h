/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H_
#define __ADC_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_rcc_mort.h"


/*Function definitions---------------------------------------------------------*/

//takes the ADC pot value, uses transfer function, then writes to duty cycle
//to drive the motor 
void writePotToARR(void);

//initialize ADC with DMA using channel five
void initADC3_5_withDMA(void);

//start the process of converting for the ADC
void startACDConversion(void);

//function to call in state machine to turn on potentiometer monitoring
void turnOnPotCheck(void);

//function to call in state machine to turn on potentiometer monitoring
void turnOffPotCheck(void);

#ifdef __cplusplus
}
#endif

#endif /*__GPIOTASK1_H_ */