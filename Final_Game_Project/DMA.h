/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DMA_H_
#define __DMA_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_rcc_mort.h"


/*Function definitions---------------------------------------------------------*/

//initialize ADC with DMA using channel five
void initDMAForADC3_1channel(void);


//enable DMA for ADC
void enableDMAForAdc3(void);

//return the stored ADC value
uint16_t returnADC3StoredValue(void);


#ifdef __cplusplus
}
#endif

#endif /*__GPIOTASK1_H_ */