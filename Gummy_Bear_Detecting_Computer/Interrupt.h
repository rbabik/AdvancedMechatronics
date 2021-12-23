/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INTERRUPT_H_
#define __INTERRUPT_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*Function definitions---------------------------------------------------------*/


//enables the NVIC for timer 3
void enableNVIC_Timer3(void);

//enables the NVIC for timer 2
void enableNVIC_Timer2(void); //Mort: Name was wrong

//enables the NVIC for rising edge detection for EXTI PC8 on Port C
void enableEXTI8PortC(void);

//IRQ handler for rising edge detection
void EXTI9_5_IRQHandler(void);

//check for a rising edge on pin 8 without use of interrupt
void risingEdgeDetectorPC8(void);

//IRQ handler for timer 3 overflow
void TIM3_IRQHandler(void);

//IRQ handler for timer 2 overflow
void TIM2_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /*__INTERRUPT_H_ */