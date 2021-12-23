/* Includes ------------------------------------------------------------------*/
#include "State_Machine.h"
#include "Timer.h"
#include "LED.h"
#include "GPIO.h"

/* Mactros ------------------------------------------------------------------*/

/* Module Variables ----------------------------------------------------*/

//variable for enum machineState
machineState currState; 

//variable to store current phototransistor value
uint8_t currVal; 

//make phototransistor reading storage array
uint16_t detector_values[NUM_LEDS]; 


/* functions ------------------------------------------------------------------*/


//set state to initialize
void initStateMachine(void)
{
    //set initial lock state to INITIALIZE
    currState = INITIALIZE;
}

//state machine to receive states and change states accordingly
void stateMachine(event_type newEvent)
{
    //switch case with state
    switch (currState)
    {
        //case 1 INITIALIZE
        case INITIALIZE:
            //initialize everything
            //reset all the timers
            diableTimers();
            //turn LEDs off
            led1off();
            led2off();
            led3off();
            //set state to WAIT_STATE
            currState = WAIT_STATE;
        break;
    
        //case 2 WAIT_STATE
        case WAIT_STATE:
            //check if rising edge on input pin
            if (newEvent == RISING_EDGE)
            {
                //turn on LED1
                led1on();
                //start timer 1
                initialize_TIM3();
                //start timer 2
                initialize_TIM2();
                //set state to LED1_ON
                currState = LED1_ON;
            }
        break;
    
        //case 3 LED1_ON
        case LED1_ON:
            //check if timer 2 overflows
            if (newEvent == TIM2_OVERFLOW)
            {
                //read phototransistor input LED1 pin value
                currVal = is_GPIOC_pinPC12_high();
                //push value to storage array
                detector_values[0] = currVal;
                disableTimer2();
            }
            // check if timer 1 overflows 
            if (newEvent == TIM1_OVERFLOW)
            {
                //turn LED1 off
                led1off();
                //disable timers
                diableTimers();
                //start timer 1
                initialize_TIM3();
                //start timer 2
                initialize_TIM2();
                //turn LED2 on
                led2on();
                //set state to LED2_ON
                currState = LED2_ON;
            }
        break;
    
        //case 4 LED2_ON
        case LED2_ON:
            //check if timer 2 overflows
            if (newEvent == TIM2_OVERFLOW)
            {
                //read phototransistor input LED2 pin value
                currVal = is_GPIOC_pinPC12_high();
                //push value to storage array
                detector_values[1] = currVal;
                disableTimer2();
            }
            if (newEvent == TIM1_OVERFLOW)
            {
                // check if timer 1 overflows 
                //turn LED2 off
                led2off();
                //disable timers
                diableTimers();
               //start timer 1
                initialize_TIM3();
                //start timer 2
                initialize_TIM2();
                //turn LED3 on
                led3on();
                //set state to LED3_ON
                currState = LED3_ON;
            }
        break;

        //case 5 LED3_ON
        case LED3_ON:
            //check if timer 2 overflows
            if (newEvent == TIM2_OVERFLOW)
            {
                //read phototransistor input LED3 pin value
                currVal = is_GPIOC_pinPC12_high();
                //push value to storage array
                detector_values[2] = currVal;
                //turn LED3 off
                led3off();
                disableTimer2();
                //determine gummy color
                //print gummy color -- debugPrint();
                printGummyBearColor();
                //set state to INITIALIZE 
                currState = INITIALIZE;
            }
        break;
    }
} 

//determine gummy bear color and print answer!
void printGummyBearColor(void)
{
    //led 1 is red, led 2 is green, led3 is blue
    
    //check for red gummy bear
    if ((detector_values[0] > 0) && (detector_values[1] == 0))
    {
        //create string for gummy bear color
        char finColor[3] = {'R', 'E', 'D'};
        //print that it is a red gummy bear
        gummyColor(finColor);
    }
    //check if green gummy bear
    else if ((detector_values[0] == 0) && (detector_values[1] > 0))
    {
        //create string for gummy bear color
        char finColor[5] = {'G', 'R', 'E', 'E', 'N'};
        //print that it is a green gummy bear
        gummyColor(finColor);
    }
    //check if white gummy bear
    else if ((detector_values[0] > 0) && (detector_values[2] > 0))
    {
        //create string for gummy bear color
        char finColor[5] = {'C', 'L', 'E', 'A', 'R'};
        //print that it is a white gummy bear
        gummyColor(finColor);
    }
    //check if orange gummy bear
    else if ((detector_values[0] > 0) && (detector_values[1] > 0) && (detector_values[2] == 0))
    {
        //create string for gummy bear color
        char finColor[6] = {'O', 'R', 'A', 'N', 'G', 'E'};
        //print that it is an orange gummy bear
        gummyColor(finColor);
    }
    //or if none of the four colors
    else
    {
        //create string for not a gummy bear color
        char finColor[4] = {'N', 'O', 'N', 'E'};
        //print that it is an orange gummy bear
        gummyColor(finColor);
    }
}
