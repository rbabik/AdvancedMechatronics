/* Includes -----------------------------------------------------------------*/
#include "GPIO_motor.h"
#include "MOTOR.h"
#include "main.h"
#include "stm32f4xx_rcc_mort.h" 

/* MACROS -------------------------------------------------------------------*/

/* FUNCTIONS ----------------------------------------------------------------*/
    // ENABLES
void M1_ENABLE(void) { PE7_HIGH(); }
void M2_ENABLE(void) { PE8_HIGH(); }
void M3_ENABLE(void) { PE9_HIGH(); }
void M4_ENABLE(void) { PE10_HIGH();}
void M5_ENABLE(void) { PE11_HIGH();}
void M6_ENABLE(void) { PE12_HIGH();}


void DISABLE_ALL_MOTORS(void)
{
    M1_DISABLE(); 
    M2_DISABLE(); 
    M3_DISABLE(); 
    M4_DISABLE(); 
    M5_DISABLE();
    M6_DISABLE();
}


    // DISABLES
void M1_DISABLE(void) { PE7_LOW(); }
void M2_DISABLE(void) { PE8_LOW(); }
void M3_DISABLE(void) { PE9_LOW(); }
void M4_DISABLE(void) { PE10_LOW();}
void M5_DISABLE(void) { PE11_LOW();}
void M6_DISABLE(void) { PE12_LOW();}

    // UP FUNCTIONS
void M1_UP(void) { PE13_HIGH(); }
void M2_UP(void) { PE14_HIGH(); }
void M3_UP(void) { PE15_HIGH(); }
void M4_UP(void) { PB9_HIGH();  }
void M5_UP(void) { PB10_HIGH(); }
void M6_UP(void) { PB11_HIGH(); }

    // DOWN FUNCTIONS
void M1_DOWN(void) { PE13_LOW(); }
void M2_DOWN(void) { PE14_LOW(); }
void M3_DOWN(void) { PE15_LOW(); }
void M4_DOWN(void) { PB9_LOW();  }
void M5_DOWN(void) { PB10_LOW(); }
void M6_DOWN(void) { PB11_LOW(); }

// Function to set direction and enable of desired motor
void setMotorPosition(uint8_t motor, uint8_t position)
{
    if (motor == 1)
    {
        if (position == 1) { M1_UP();}
        if (position == 0) { M1_DOWN();}
        M1_ENABLE();
    }
    if (motor == 2)
    {
        if (position == 1) { M2_UP();}
        if (position == 0) { M2_DOWN();}
        M2_ENABLE();
    }
    if (motor == 3)
    {
        if (position == 1) { M3_UP();}
        if (position == 0) { M3_DOWN();}
        M3_ENABLE();
    }
    if (motor == 4)
    {
        if (position == 1) { M4_UP();}
        if (position == 0) { M4_DOWN();}
        M4_ENABLE();
    }
    if (motor == 5)
    {
        if (position == 1) { M5_UP();}
        if (position == 0) { M5_DOWN();}
        M5_ENABLE();
    }
    if (motor == 6)
    {
        if (position == 1) { M6_UP();}
        if (position == 0) { M6_DOWN();}
        M6_ENABLE();
    }
}
