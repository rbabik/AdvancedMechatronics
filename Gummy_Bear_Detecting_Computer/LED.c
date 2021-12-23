#include "GPIO.h"
#include "LED.h"


//initialize LED 1 
void initLED1(void)
{
    //call GPIOC PC9 initialization
    initialize_GPIOC_pinPC9();
}    

//initialize LED 2 
void initLED2(void)
{
    //call GPIOC PC10 initialization
    initialize_GPIOC_pinPC10();
} 

//initialize LED 3 
void initLED3(void)
{
    //call GPIOC PC9 initialization
    initialize_GPIOC_pinPC11();
} 

//turn LED 1 on
void led1on(void)
{
    //call GPIOC PC9 on
    GPIOC_pinPC9_high();
}

//turn LED 1 off
void led1off(void)
{
    //call GPIOC PC9 off
    GPIOC_pinPC9_low();
}

//turn LED 2 on
void led2on(void)
{
    //call GPIOC PC10 on
    GPIOC_pinPC10_high();
}

//turn LED 2 off
void led2off(void)
{
    //call GPIOC PC10 off
    GPIOC_pinPC10_low();
}

//turn LED 3 on
void led3on(void)
{
    //call GPIOC PC11 on
    GPIOC_pinPC11_high();
}

//turn LED 3 off
void led3off(void)
{
    //call GPIOC PC11 off
    GPIOC_pinPC11_low();
}
