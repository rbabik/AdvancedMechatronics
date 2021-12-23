/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STATEMACHINE_H_
#define __STATEMACHINE_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Event.h" 

/*State Enums/Macros---------------------------------------------------------*/

#define NUM_LEDS 3

//enumerated for the different states of the state machine
typedef enum
{
    WELCOME,
    INITIALIZE,
    GAME_PLAY,
    RESULTS,
} machineState;
//make machine state enum

/*Initializations---------------------------------------------------------*/


/*Function definitions---------------------------------------------------------*/

//set state to initialize
void initStateMachine(void);

//state machine to receive states and change states accordingly
void stateMachine(event_type newEvent);

//function to return 1 (true) if state time has passed or 0 (false) if not 
uint16_t isStateDone(uint16_t state_idx);

//add event to queue and set boolean variable to denote past state
void setPassedState(uint16_t state_idx);

//reset the state booleans to specify that we have not passed any states yet
void resetAllPassedState(void);

#ifdef __cplusplus
}
#endif

#endif /*__STATEMACHINE_H_ */