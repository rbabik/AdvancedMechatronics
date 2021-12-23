/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H_
#define __LED_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*Function definitions---------------------------------------------------------*/

//initialize LED 1 
void initLEDstrip(void);

//turn LED strip on
void ledStripOn(void);

//turn LED strip off
void ledStripOff(void);

//set the period for LED blinking
void setBlinkPeriod(uint16_t cycleTime);

//turn on blinking for LED
void turnOnLEDblink(void);

//turn on blinking for LED
void turnOffLEDblink(void);

//blink LED at specified cycle time
void blinkLED(void);

//activate the LED blink twice because target was hit
void blinkLEDhitOn(void);

//blink the LED twice when the target is hit down during gameplay
void blinkLEDhit(void);

#ifdef __cplusplus
}
#endif

#endif /*__LED_H_ */