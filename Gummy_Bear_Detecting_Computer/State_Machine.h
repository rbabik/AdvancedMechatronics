/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STATEMACHINE_H_
#define __STATEMACHINE_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Event.h" //Mort: have to include the thing that defines the events since you are using it as a parameter for the statemachine

/*State Enums/Macros---------------------------------------------------------*/

#define NUM_LEDS 3

//enumerated for the different states of the state machine
typedef enum
{
    INITIALIZE,
    WAIT_STATE,
    LED1_ON,
    LED2_ON,
    LED3_ON,
} machineState;
//make machine state enum

//enum for gummy bear colors
typedef enum
{
    GREEN,
    RED,
    ORANGE,
    CLEAR,
} gummyBearColor;

////store final gummy bear color
//gummyBearColor finalColor;

/*Initializations---------------------------------------------------------*/


/*Function definitions---------------------------------------------------------*/

//set state to initialize
void initStateMachine(void);

//state machine to receive states and change states accordingly
void stateMachine(event_type newEvent);

//function to select gummy bear color
//gummyBearColor gummyBearColorSelect(void);
void printGummyBearColor(void);

#ifdef __cplusplus
}
#endif

#endif /*__STATEMACHINE_H_ */