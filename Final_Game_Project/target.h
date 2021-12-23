/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TARGET_H_
#define __TARGET_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*Function definitions---------------------------------------------------------*/

//initialize score for game to zero and other startup stuff
void RandomTargetUp(void);
void HowmanyTarget(void);
void NumTarget(void);
void ActivateTarget(void);
void Targetinit(void);
void CheckTarget(void);
void Activate(void);
void Deactivate(void);
uint8_t CheckActivate(void);
void driveMotorsDown(void);

void ActivateUp(void);
void DeactivateUp(void);
uint8_t CheckActivateUp(void);

#ifdef __cplusplus
}
#endif

#endif 