/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTOR_
#define __MOTOR_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"
#include "stm32f4xx_rcc_mort.h"


/*Function definitions---------------------------------------------------------*/

// Functions to turn motors on individually
void M1_ENABLE(void);
void M2_ENABLE(void);
void M3_ENABLE(void);
void M4_ENABLE(void);
void M5_ENABLE(void);
void M6_ENABLE(void);

// Functions to turn all motors off at once
void DISABLE_ALL_MOTORS(void);

// Functions to turn motors off individually
void M1_DISABLE(void);
void M2_DISABLE(void);
void M3_DISABLE(void);
void M4_DISABLE(void);
void M5_DISABLE(void);
void M6_DISABLE(void);

// Functions to set directions of individual motors to up
void M1_UP(void);
void M2_UP(void);
void M3_UP(void);
void M4_UP(void);
void M5_UP(void);
void M6_UP(void);

// Functions to set directions of individual motors to down
void M1_DOWN(void);
void M2_DOWN(void);
void M3_DOWN(void);
void M4_DOWN(void);
void M5_DOWN(void);
void M6_DOWN(void);

// Function to set direction and enable of desired motor
void setMotorPosition(uint8_t motor, uint8_t position);

#ifdef __cplusplus
}
#endif

#endif /*__MOTOR_ */