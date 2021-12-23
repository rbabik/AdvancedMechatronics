/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GAME_H_
#define __GAME_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*Function definitions---------------------------------------------------------*/

//initialize score for game to zero and other startup stuff
void initGame(void);

//up the current score 
void incrementScore(uint16_t numHitDown);

//decrease the current score by one
void decrementScore(void);

//get back the current score
uint16_t getScore(void);

//returns the number of targets currently up
uint16_t getTargetUpCount(void);

//returns the number of targets currently up
uint16_t getPrevTargetUpCount(void);

#ifdef __cplusplus
}
#endif

#endif /*__LED_H_ */