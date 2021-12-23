/* Includes ------------------------------------------------------------------*/
#include "State_Machine.h"
#include "timer.h"
#include "GPIO.h"
#include "ADC.h"
#include "LED.h"
#include "target.h"
#include "LED.h"
#include "Game.h"

/* Mactros ------------------------------------------------------------------*/

/* Module Variables ----------------------------------------------------*/

//variable for enum machineState
machineState currState; 

////set global variables for the length of time spent in each state...
//uint16_t initStateTime = 5; //seconds
//uint16_t gamePlayTime = 90 + 5; //seconds
//uint16_t resultsTime = 10 + 90 + 5; //seconds
//
//uint16_t finishInitState = 0; //boolean 0 false 1 true
//uint16_t finishGamePlayState = 0; //boolean 0 false 1 true
//uint16_t finishResultsState = 0; //boolean 0 false 1 true

uint16_t stateEndTime[3] = {5,65, 70}; //seconds
uint16_t finishedStateTracker[3] = {0,0,0};  //boolean 0 false 1 true
uint16_t initStateStarted = 0; //boolean to store whether the initialization state has started yet or not

/* functions ------------------------------------------------------------------*/

//function to return 1 (true) if five seconds have passed or 0 (false) if not
//for state_idx, 0 is INITIALIZE, 1 is GAME_PLAY, 2 is RESULTS 
uint16_t isStateDone(uint16_t state_idx)
{
    //see if we haven't already passed this state
    if (finishedStateTracker[state_idx] == 0)
    {
        uint32_t time = getTimer4();
        
        //check to see if we even started the game yet
        if (initStateStarted > 0)
        {
            //debugPrint(time - getInitStateStartTime());
            //check to see if we did indeed just pass this state end time
            if ((time - getInitStateStartTime()) > stateEndTime[state_idx])
            {
                //debugPrint(9999);
                return 1;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

//set the boolean to specify that we have passed a state!
void setPassedState(uint16_t state_idx)
{
    finishedStateTracker[state_idx] = 1;
}

//reset the state booleans to specify that we have not passed any states yet
void resetAllPassedState(void)
{
    finishedStateTracker[0] = 0;
    finishedStateTracker[1] = 0;
    finishedStateTracker[2] = 0;

}


////add event to queue and set boolean variable to denote past initialization state
//void passInitState(void)
//{
//    finishInitState == 1;
//}

//set state to initialize
void initStateMachine(void)
{
    //initialize the game and set score to 0
    initGame();
    //set initial state to WELCOME
    currState = WELCOME;
    //reset the timers
    disableTimer3();
    disableTimer4();
    //specify that no states have been executed yet
    resetAllPassedState();
    //set boolean for initialization state completion to false
    initStateStarted = 0;
    //add event to push us into next state after doing initialization
    addToQueue(NO_EVENT);
}

//state machine to receive states and change states accordingly
void stateMachine(event_type newEvent)
{
    //switch case with state
    switch (currState)
    {
        //case 1 WELCOME 
        case WELCOME:
        //debugPrint(4);
        
        //set slow blink period
        setBlinkPeriod(4);
        //start LED blinking
        turnOnLEDblink();
        
        //start the game play timer
        enableTimer4();
        //debugPrint(4);
        
        //turn on check for reading difficulty potentiometer
        turnOnPotCheck();
        
        //initialize everything and move on to rest state
        //set the state to rest state
        if (newEvent == RISING_EDGE_START_BUTTON)
        {            
            //enableTimer3(); -- this was only here for testing!!
            
            //speed up the LED blinking to signify initialization state
            setBlinkPeriod(2);
            
            //debugPrint(5);
            //turn off check for potentiometer level setting
            turnOffPotCheck();
            //debugPrint(5);
            //move game onto initialize state
            currState = INITIALIZE;
            
            //set the initialization game start time
            setInitStateStartTime(getTimer4());
            
            //set boolean variable to store that initialization state has been started
            initStateStarted = 1;
            
            //Screen1 displays “get ready” and initialization stuff
            screenPrint('a');
            
        }
        break;
        
        //case 2 GAME_INITIALIZE
        case INITIALIZE:
        
        //check to see if the game timer for initializing has overflowed 
        if (newEvent == INIT_GAME_TIMER_OVERFLOW)
        {
            //debugPrint(7);
                  
            //start the target timer
            enableTimer3();
            
            //stop LED blinking 
            turnOffLEDblink();
            //and just turn on steady state
            ledStripOn();
            
            //Activate(); 
            //set a random number of targets up
            //ActivateTarget(); old
            //ActivateUp();

            //add NO_EVENT so that we can push into GAME_PLAY state
            addToQueue(NO_EVENT);
                        
            //update the current state to playing
            currState = GAME_PLAY;
        }
        break;
    
        //case 3 GAME_PLAY
        case GAME_PLAY:
        
        //check to see if add targets event occured
        if (newEvent == TARGET_TIMER_OVERFLOW)
        {
            //drive down currently up targets
            Activate(); //function activates the drive down -- UNCOMMENT ONCE HAVE HARDWARE
            //drive up more random targets
            //ActivateTarget(); old
            ActivateUp();
            //debugPrint(4444);
        }
        
        //turn on check for targets being hit down (which will increment score if so)
        //see if event is target being hit down
        if (newEvent == RISING_EDGE_SENSOR)
        {
            //check if we brought it down or if it was hit down
            //if hit down...
            //flash LED strip if target gets hit down
            blinkLEDhitOn();
            //play music if target gets hit down
            //debugPrint(12);
        }
        
        //if game timer overflows
        if(newEvent == GAME_PLAY_TIMER_OVERFLOW)
        {
            //debugPrint(8);
            //turn off screen 2 time remaining
            
            //disable game play timer 3
            disableTimer3();          
            
            //set LED strip to blink at fast pulse while in RESULTS state
            setBlinkPeriod(2);  
            //start LED blinking
            turnOnLEDblink();
            
            //add to queue a NO_EVENT to push us into the results state
            addToQueue(NO_EVENT);
            
            //update to results state
            currState = RESULTS;  
            Activate();
        }
        break;
    
        //case 4 RESULTS
        case RESULTS:
        
        //if the results timer overflows...
        if (newEvent == RESULTS_TIMER_OVERFLOW)
        {
            //debugPrint(14);
 
            //turn off LED blinking
            turnOffLEDblink();
            
            //reset everything for new game

            initStateMachine();
            Activate();
        }
        break;
    }
} 
