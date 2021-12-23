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
void initLED1(void);

//initialize LED 2
void initLED2(void);

//initialize LED 3
void initLED3(void);

//turn LED 1 on
void led1on(void);

//turn LED 1 off
void led1off(void);

//turn LED 2 on
void led2on(void);

//turn LED 2 off
void led2off(void);

//turn LED 3 on
void led3on(void);

//turn LED 3 off
void led3off(void); //Mort: same

#ifdef __cplusplus
}
#endif

#endif /*__LED_H_ */