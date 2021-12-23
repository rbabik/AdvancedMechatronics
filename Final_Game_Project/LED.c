#include "GPIO.h"
#include "LED.h"
#include "timer.h"

//boolean to set if LED should be blinking
uint16_t blink = 0;

//boolean to set if LED should blink twice because target hit
uint16_t blinkHit = 0;

//set blink hit count that we will decrement as we blink each time
uint16_t blinkHitCount = 2;

//variable to store time of last flip while blinking
uint32_t prevBlinkTime = 0;

//variable to store time of last flip while blinking after hit
uint32_t prevBlinkHitTime = 0;

//store the period for LED blinking
uint16_t blinkPeriod = 0;

/////////////////////////FUNCTIONS////////////////////////////////

//initialize LED 1 
void initLEDstrip(void)
{
    //call GPIOC PC9 initialization
    initialize_GPIOC_pinPC9();
}    

//turn LED strip on
void ledStripOn(void)
{
    //call GPIOC PC9 on
    GPIOC_pinPC9_high();
}

//turn LED 1 off
void ledStripOff(void)
{
    //call GPIOC PC9 off
    GPIOC_pinPC9_low();
}

//turn on blinking for LED
void turnOnLEDblink(void)
{
    blink = 1;
}

//turn on blinking for LED
void turnOffLEDblink(void)
{
    blink = 0;
}

//set the period for LED blinking
void setBlinkPeriod(uint16_t cycleTime)
{
    blinkPeriod = cycleTime;
}

//blink LED at specified cycle time
void blinkLED(void)
{
    //make sure we have blinking turned on
    if (blink == 1)
    {
        //get the current time
        uint32_t currTime = getTimer4();
        
        //if period is up and time to switch LED state
        //divided by two because want half the full on/off period
        if ((currTime - prevBlinkTime) >= (blinkPeriod/2.0))
        {
            //if LED is currently on, turn off
            if (is_GPIOC_pinPC9_high()) ledStripOff();
            //otherwise, it is off and now turn on
            else ledStripOn();
            
            //update the previous time for blink check
            prevBlinkTime = currTime;
        }
    }
}

//activate the LED blink twice because target was hit
void blinkLEDhitOn(void)
{
    blinkHit = 1;
    blinkHitCount = 2;
}

//blink the LED twice when the target is hit down during gameplay
void blinkLEDhit(void)
{
    //check to see if blink hit is turned on
    if (blinkHit == 1)
    {
        //if we haven't already done both blinks
        if (blinkHitCount > 0)
        {
            //get the current time
            uint32_t currTime = getTimer4();
            
            //if 1s is up and time to switch LED state
            if ((currTime - prevBlinkHitTime) > 1)
            {
                //if LED is currently on, turn off
                if (is_GPIOC_pinPC9_high()) ledStripOff();
                //otherwise, it is off and now turn on
                else ledStripOn();
    
                //update the previous time for blink check
                prevBlinkTime = currTime;
                
                //decrement the blink hit count 
                blinkHitCount = blinkHitCount - 1;
            }
        }
        
        //if we completed both blinks 
        else
        {
            //turn blink LED hit off
            blinkHit = 0;
            //turn the LED back on for gameplay mode
            turnOnLEDblink();
        }
    }
}