/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIOmotor_
#define __GPIOmotor_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"
#include "stm32f4xx_rcc_mort.h"


/*Function definitions---------------------------------------------------------*/
    // init gpio pins E 7-15 and B 9-11
void initGPIOE7_15_asOutput(void);
void initGPIOB9_11_asOutput(void);

    // pin high functions
void PE7_HIGH(void);
void PE8_HIGH(void);
void PE9_HIGH(void);
void PE10_HIGH(void);
void PE11_HIGH(void);
void PE12_HIGH(void);
void PE13_HIGH(void);
void PE14_HIGH(void);
void PE15_HIGH(void);
void PB9_HIGH(void);
void PB10_HIGH(void);
void PB11_HIGH(void);
    
    // pin low functions
void PE7_LOW(void);
void PE8_LOW(void);
void PE9_LOW(void);
void PE10_LOW(void);
void PE11_LOW(void);
void PE12_LOW(void);
void PE13_LOW(void);
void PE14_LOW(void);
void PE15_LOW(void);
void PB9_LOW(void);
void PB10_LOW(void);
void PB11_LOW(void);


#ifdef __cplusplus
}
#endif

#endif /*__GPIOmotor_ */