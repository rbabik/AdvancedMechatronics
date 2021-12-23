#include "main.h"
#include "mbed.h"
#include "GPIO.h"
#include "GPIO_motor.h"
#include "timer.h"
#include "Interrupt.h"
#include "ADC.h"
#include "DMA.h"
#include "State_Machine.h"
#include "Event.h"
#include "MOTOR.h"
#include "target.h"
#include "LED.h"
#include "Game.h"
#include "magnets.h"

Serial pc(USBTX, USBRX);


int main (void)
{    
/////////////////GPIO///////////////////////
    //initialize pin for timer output
    initialize_GPIOB_pin0();
    //initialize pin for start button
    initialize_GPIOC_pinPC8();
    //initialize the 6 digital input pins for magnetic sensors
    init_GPIOB_pin_0To5();
    //set up LED strip output pin -- Port C pin 9
    initLEDstrip();
    GPIOC_pinPC9_low();
    //motor enable and direction pins
    initGPIOE7_15_asOutput();
    initGPIOB9_11_asOutput();

/////////////////ADC DMA///////////////////////
    //initialize ADC and GPIO
    initADC3_5_withDMA();
    //create needed delay before starting conversion
    int j = 0;
    int i;
    for(i =0; i<100000; i++){
        j=j+1;
        }
    //start ADC
    startACDConversion();
    
    //for testing!! turn this off otherwise, done in state machine
    //turnOnPotCheck();
    //store the pot value for the ARR to tune difficulty
    //writePotToARR();
    
////////////////////TARGET & GAME////////////////////////
    //initialize parameters
    Targetinit();
    initGame();  //this is in init state machine too so not really needed here
    
////////////////////QUEUE////////////////////////////
    initQueue();

////////////////TIMER///////////////////////
    //setup timer for difficulty PWM -- this enables NVIC too
    initTim3Channel3forPWM();
    //initialize the global game play timer
    initTimer4NoInterrupt();
    //enable the timers for testing --- move this to state machine for real deal!
//    enableTimer3();
//    enableTimer4();
    
////////////////STATE MACHINE///////////////////////
    //initialize the state machine
    initStateMachine();
    
    
    while(1) 
    {
        
        //debugPrint(getGPIOBpinState(1));
        
        //keep checking to update ARR for pot difficulty while in WELCOME state
        writePotToARR();
        
        //debugPrint(getTimer4());  

        //check for button press to start the game
        risingEdgeDetectorPC8();
        
        //check for magnetic sensors rising or falling edge -- targets hit down!
        magneticSensorChange();
                
        //check if need to service an event from the queue
        serviceEventQueue();  
        
        //blink the LED -- function has check to see first if we act have blink turned on
        blinkLED(); 
        //blink the LED after a hit target -- function has check to see first if we act have blink turned on
        blinkLEDhit();
                
        //test the global timer for initialization state...
        if (isStateDone(0) == 1) 
        {
            debugPrint(6);
            setPassedState(0);
            addToQueue(INIT_GAME_TIMER_OVERFLOW);
        }
        
        //test the global timer for game play state...
        if (isStateDone(1) == 1) 
        {
            debugPrint(10);
            setPassedState(1);
            addToQueue(GAME_PLAY_TIMER_OVERFLOW);
        }
        
        //test the global timer for results state...
        if (isStateDone(2) == 1) 
        {
            debugPrint(11);
            setPassedState(2);
            addToQueue(RESULTS_TIMER_OVERFLOW);
        }
        
        //check to drive motors down when targets get swapped
        driveMotorsDown();
        ActivateTarget(); //call activatetarget function in the main loop
        
        if(getMagneticSensorState(0)==1)
        M1_DISABLE();
        if(getMagneticSensorState(1)==1)
        M2_DISABLE();
        if(getMagneticSensorState(2)==1)
        M3_DISABLE();
        if(getMagneticSensorState(3)==1)
        M4_DISABLE();
        if(getMagneticSensorState(4)==1)
        M5_DISABLE();
        if(getMagneticSensorState(5)==1)
        M6_DISABLE();
        
        CheckTarget();
    }
}

void debugPrint(int32_t number) 
{
    pc.printf("Go to %d\n", number);
}

void debugPrint2(int32_t number) 
{
    pc.printf("Target %d\n", number);
}

void screenPrint(char printChar)
{
    pc.printf("%c\n", printChar);
}
