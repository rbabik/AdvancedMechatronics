/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H_
#define __MAIN_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"



/*Function definitions---------------------------------------------------------*/
void debugPrint(int32_t number) ;
void debugPrint2(int32_t number);
void screenPrint(char printChar);
#ifdef __cplusplus
}
#endif

#endif /*__MAIN_H */
