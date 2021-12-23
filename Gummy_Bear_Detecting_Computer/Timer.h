/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H_
#define __TIMER_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*Function definitions---------------------------------------------------------*/

//initialize timer 1 (using timer three for what we call timer 1!)
void initialize_TIM3(void);

//intialize timer 2
void initialize_TIM2(void);

//disable timer 2
void disableTimer2(void);

uint16_t skipDelay(void);
uint16_t skipDelay2(void);

//disable timers
void diableTimers(void);

#ifdef __cplusplus
}
#endif

#endif /*__TIMER_H_ */