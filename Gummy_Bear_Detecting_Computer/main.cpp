#include "mbed.h"
#include "GPIO.h"
#include "main.h"
#include "Timer.h"
#include "State_Machine.h"
#include "LED.h"
#include "Interrupt.h"


//Cannot print without declaring the serial interface
Serial pc(USBTX, USBRX);


int main()
{
    
    //Initialize GPIO pin for switch input
    initialize_GPIOC_pinPC8();
   
    //Initialize GPIO pin for LED output 1
    initialize_GPIOC_pinPC9();

    //Initialize GPIO pin for LED output 2
    initialize_GPIOC_pinPC10();

    //Initialize GPIO pin for LED output 3
    initialize_GPIOC_pinPC11();

    //initialize GPIO pin for Phototransistor input
    initialize_GPIOC_pinPC12();
    
    //initialize EXTI enable
    //enableEXTI8PortC();

    //Initialize Timer 1 -- happens in state machine!
    //initialize_TIM3();

    //Initialize Timer 2 -- happens in state machine!
    //initialize_TIM2();
    
    //Initialize Event Queue
    initQueue();
    
    //initialize state machine
    initStateMachine();
    
    //Start continuous loop
    while(1)
    {
        //check for start switch
        risingEdgeDetectorPC8();
         //call service function to handle from event queue
        serviceEventQueue();
    }
}

//debug function to print something
void debugPrint( uint16_t value)
{
    pc.printf("Got to %u\n",value);    
}

//function to print gummy bear color
void gummyColor(char color[])
{
   pc.printf("Gummy Bear Color: %c\n", color[0] ); //Mort: I would recommend not trying to do this.
}