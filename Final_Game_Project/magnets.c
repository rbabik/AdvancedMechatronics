#include "GPIO.h"
#include "magnets.h"


//initialize all magnetic sensors 
void initMagneticSensors(void)
{
    //call GPIOB initialization for all six magnetic sensor pins
    init_GPIOB_pin_0To5();
}    

//get the state as either 0 or 1 for magnetic sensor
uint16_t getMagneticSensorState(uint16_t sensorNum)
{
    //get the state from the GPIOB pin of interest
    uint16_t state = getGPIOBpinState(sensorNum);
    //return 0 if down, 1 if up
    return state; 
}