/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __interrupt_
#define __interrupt_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/*Function definitions--------------------------------------------------------*/

//IRQ handler for timer 3 overflow
void TIM3_IRQHandler(void);

//enables the NVIC for timer 3,4
void enableNVIC_Timer3(void);
void enableNVIC_Timer4(void);

//check for a rising edge on pin 8 without use of interrupt
void risingEdgeDetectorPC8(void);

//check for magnetic sensors rising or falling edge
void magneticSensorChange(void);

#ifdef __cplusplus
}
#endif

#endif /*__interrupt */