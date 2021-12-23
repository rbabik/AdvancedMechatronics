/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H_
#define __MAIN_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"


/*Function definitions---------------------------------------------------------*/

//debug statement
void debugPrint( uint16_t value);

//print gummy bear color
void gummyColor(char color[]);

#ifdef __cplusplus
}
#endif

#endif /*__MAIN_H */


