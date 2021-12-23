/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAGNETS_H_
#define __MAGNETS_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*Function definitions---------------------------------------------------------*/

//initialize all magnetic sensors 
void initMagneticSensors(void);

//get the state as either 0 or 1 for magnetic sensor
uint16_t getMagneticSensorState(uint16_t sensorNum);

#ifdef __cplusplus
}
#endif

#endif /*__MAGNETS_H_ */