/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H_
#define __TIMER_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"



/*Function definitions---------------------------------------------------------*/

//get current count of timer 3
uint32_t getTimerCNT(void);

//get current count of timer 4
uint32_t getTimer4CNT(void);

//get function for debugging
uint32_t getDutyVal(void); 

//use pot to tune the difficulty by setting the ARR period
void setARR(uint32_t ARR);

//set duty cycle for the targets
void setDutyCycle(uint32_t dutyVal);

//set duty cycle for the targets
//so if it is in high state we want target upright, if its in low state we 
//want the target down
uint16_t getDutyCycleState(void);

//initialize timer 3 for target up vs down timer
void initTim3Channel3forPWM(void);

//get the time at which the start button was first pressed
uint16_t getInitStateStartTime(void);

//set the time at which the start button was first pressed
void setInitStateStartTime(uint16_t setTime);

//disable timer 3
void disableTimer3(void);

//enable timer 3
void enableTimer3(void);

//initialize timer 4 for the global game timer
void initTimer4NoInterrupt(void);

//enable timer 4
void enableTimer4(void);

//disable timer 4
void disableTimer4(void);

//get the current time in seconds of timer 4
uint32_t getTimer4(void);

uint32_t getOverflow(void);

#ifdef __cplusplus
}
#endif

#endif /*__TIMER_H_ */