/* Includes ------------------------------------------------------------------*/
#include "Interrupt.h"
#include "GPIO.h" 
#include "timer.h"
#include "stm32f4xx_rcc_mort.h"
#include "LED.h"
#include "Event.h"
#include "Game.h"
#include "target.h"

/* Macros ------------------------------------------------------------------*/
//timer 3 register macros
#define TIM3_BASE_REGISTER ((uint32_t)0x40000400)
#define TIM3_SR (TIM3_BASE_REGISTER + 0x10)
#define TIM3_INTERRUPT_ENABLE_REGISTER (TIM3_BASE_REGISTER + 0x0C)

//IRQ clear SR flags for timers
#define TIM_UIF  0x01 
//flag to check if the interrupt in the timer is set, this is the flag for the
// interrupt enable of the timers
#define TIM_UPDATE_INTERRUPT_ENABLE     0x1 

#define TIM_CH3_CC3IF                   0x8
#define TIM_CH3_CC_INTERRUPT_ENABLE     0x8

//register for NVIC and bit to enable it
#define SYSTEM_CONTROL_BASE_ADDRESS                     (0xE000E000)
#define NVIC_BASE_ADDRESS                               (SYSTEM_CONTROL_BASE_ADDRESS + 0x100)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31         (NVIC_BASE_ADDRESS)
#define TIM3_INTERRUPT_BIT      (0x20000000) // position 29
#define TIM4_INTERRUPT_BIT      (0x40000000) // position 30

//use this variable to check for rising edges on start switch - initialize high
uint16_t pin8state = 1;


/* Functions ------------------------------------------------------------------*/


//enables the NVIC for timer 3
void enableNVIC_Timer3(void)
{ 
    //create pointer
    uint32_t * reg_pointer_32;
    //set pointer to the interrupt enable register
    reg_pointer_32 = (uint32_t *)NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31;
    //set bit for interrupt
    *reg_pointer_32 = TIM3_INTERRUPT_BIT;
}

//enables the NVIC for timer 4
void enableNVIC_Timer4(void)
{ 
    //create pointer
    uint32_t * reg_pointer_32;
    //set pointer to the interrupt enable register
    reg_pointer_32 = (uint32_t *)NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31;
    //set bit for interrupt
    *reg_pointer_32 = TIM4_INTERRUPT_BIT;
}

//check for a rising edge on pin 8 without use of interrupt
void risingEdgeDetectorPC8(void)
{
    uint16_t currVal = is_GPIOC_pinPC8_high();
    if ((currVal > 0) && pin8state != currVal)
    {
//        //need to set so that this only happens if we haven't started the game yet!
//        pin8state = 1;
        addToQueue(RISING_EDGE_START_BUTTON);
        //debugPrint(111);
        //set the timer variable to mark start button being pressed!
        //debugPrint(2);
    }
    else if ((currVal == 0) && pin8state != currVal)
    {
//        pin8state = 0;
        //debugPrint(3);
    }
    
    pin8state = currVal;
}

//check for magnetic sensors rising or falling edge
void magneticSensorChange(void)
{
    //need this order so that we get previous number before it is overwritten!
    uint16_t prevNum = getPrevTargetUpCount();
    uint16_t currNum = getTargetUpCount();

    //check to see if the number of targets up has changed since last check
    if (currNum < prevNum)
    {
        //check that we didn't drive it down
        if (CheckActivate() == 0)
        {
            //calc number of targets hit down
            uint16_t numHitDown = prevNum - currNum;
            //add that to the game score
            incrementScore(numHitDown);
            //send hit target count to display
            for (uint16_t i=0; i<numHitDown; i++) screenPrint('b');
        }
    }
    
}

//IRQ handler for timer 3 overflow
void TIM3_IRQHandler(void)
{
  //create pointers
  uint16_t  * reg_pointer_16_sr;
  uint16_t  * reg_pointer_16_dier;
  //pointer to SR register
  reg_pointer_16_sr = (uint16_t *)TIM3_SR; 
  //pointer to IER register
  reg_pointer_16_dier = (uint16_t *)TIM3_INTERRUPT_ENABLE_REGISTER; 
  
    // If status register says that the overflow interrupt has fired and it had beeen enabled
    if (( (*reg_pointer_16_sr & TIM_UIF) > 0) && ( (*reg_pointer_16_dier & TIM_UPDATE_INTERRUPT_ENABLE) > 0))
    {
        //clear interrupt
        *reg_pointer_16_sr = ~((uint16_t)TIM_UIF);
        //perform action
        addToQueue(TARGET_TIMER_OVERFLOW); 
        //debugPrint(1616);
    } 
    
        //check if Output Compare 3 triggered the interrupt:
    if (( (*reg_pointer_16_sr & TIM_CH3_CC3IF) >0) && ( (*reg_pointer_16_dier & TIM_CH3_CC_INTERRUPT_ENABLE) >0))
    {
        //clear interrupt
       *reg_pointer_16_sr = ~((uint16_t)TIM_CH3_CC3IF);
        //perform action
        //addToQueue(DUTY_END);
        //debugPrint(0);

   
  }
}