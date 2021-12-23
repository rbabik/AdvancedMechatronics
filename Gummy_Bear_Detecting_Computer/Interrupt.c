/* Includes ------------------------------------------------------------------*/
#include "Interrupt.h"
#include "Event.h"
#include "State_Machine.h"
#include "GPIO.h" 
#include "main.h"
#include "Timer.h"

/* Mactros ------------------------------------------------------------------*/
//macro for interrupt enable register for timer 1
// MACRO definitions for NVIC
#define SYSTEM_CONTROL_BASE_ADDRESS (0xE000E000)
#define NVIC_BASE_ADDRESS (SYSTEM_CONTROL_BASE_ADDRESS + 0x100)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31 (NVIC_BASE_ADDRESS)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_32_63 (NVIC_BASE_ADDRESS+0x4)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_64_95 (NVIC_BASE_ADDRESS+0x8)

//macro for interrupt enable register for timer 2
#define EXTI_9_5_INTERRUPT_BIT  (0x800000)   // position 23
#define TIM2_INTERRUPT_BIT      (0x10000000) // position 28
#define TIM3_INTERRUPT_BIT      (0x20000000) // position 29

//sysconfig macros
#define SYSCFG_EXTI_REGISTER_3  (SYSTEM_CONTROL_BASE_ADDRESS + 0x10)
#define SYSCFG_EXTI8_BITS       0xF
#define SYSCFG_EXTI8_PORTC      0x2
#define EXTI_INTERRUPT_MASK_BIT 0x100

//mask macros
#define EXTI_BASE_ADDRESS                ((uint32_t)0x40013C00)
#define EXTI_INTERRUPT_MASK_REGISTER     (EXTI_BASE_ADDRESS + 0x00)
#define EXTERNAL_INTERRUPT_CONTROLLER_RSTR (EXTI_BASE_ADDRESS + 0x08)
#define EXTERNAL_INTERRUPT_CONTROLLER_RSTR_BIT 0x100

//for IRQ EXTI9_5
#define EXTI_PENDING_REGISTER  (EXTI_BASE_ADDRESS + 0x14)
#define EXTI_PENDING_EXTI8 0x100

//timer 3 register macros
#define TIM3_BASE_REGISTER ((uint32_t)0x40000400)
#define TIM3_SR (TIM3_BASE_REGISTER + 0x10)
#define TIM3_INTERRUPT_ENABLE_REGISTER (TIM3_BASE_REGISTER + 0x0C)

//timer 2 register macros
#define TIM2_BASE_REGISTER ((uint32_t)0x40000000)
#define TIM2_SR (TIM2_BASE_REGISTER + 0x10) 
#define TIM2_INTERRUPT_ENABLE_REGISTER (TIM2_BASE_REGISTER + 0x0C)

//IRQ clear SR flags for timers
#define TIM_UIF  0x01 

//flag to check if the interrupt in the timer is set, this is the flag for the
// interrupt enable of the timers
#define TIM_UPDATE_INTERRUPT_ENABLE     0x1 


//registers for timer 3
//#define TIM3_BASE_REGISTER (uint32_t) 0x40000000 //Mort: Why declare this twice? it is also above
#define TIM3_CR1 (TIM3_BASE_REGISTER + 0x00)
#define TIM2_CR1 (TIM2_BASE_REGISTER + 0x00)

//use this variable to check for rising edges on start switch
uint16_t pin8state = 0;

/* functions ------------------------------------------------------------------*/


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

//enables the NVIC for timer 2
void enableNVIC_Timer2(void)
{ 
    //create pointer
    uint32_t * reg_pointer_32;
    //set pointer to the interrupt enable register
    reg_pointer_32 = (uint32_t *)NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31;
    //set bit for interrupt
    *reg_pointer_32 = TIM2_INTERRUPT_BIT;
}

//check for a rising edge on pin 8 without use of interrupt
void risingEdgeDetectorPC8(void)
{
    uint16_t currVal = is_GPIOC_pinPC8_high();
    if ((currVal > 0) && pin8state != currVal)
    {
        pin8state = 1;
        addToQueue(RISING_EDGE);
    }
    else if ((currVal == 0) && pin8state != currVal)
    {
        pin8state = 0;
    }
}

//enable EXTI PC8 on Port C
void enableEXTI8PortC(void)
{
    // init 32 bit pointer
    uint32_t * ptr32;
    // init gpioC pin 8 as input (call function)
    //initialize_GPIOC_pinPC8();
    //enable SYSCFG clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    //map EXTI PC8 to port C bit PC8
    ptr32 = (uint32_t *)SYSCFG_EXTI_REGISTER_3;
    //clear EXTI PC8 first four bits
    *ptr32 = *ptr32 & (~SYSCFG_EXTI8_BITS);
    //set EXTI PC8 to Port C
    *ptr32 = *ptr32 | SYSCFG_EXTI8_PORTC;
    //un-mask EXTI PC8 - point to register
    ptr32 = (uint32_t *)EXTI_INTERRUPT_MASK_REGISTER;
    *ptr32 = *ptr32 | EXTI_INTERRUPT_MASK_BIT;
    //trigger on rising edge
    //pointer to RTSR register
    ptr32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_RSTR;
    //turn bit 8 high for rising edge
    *ptr32 = *ptr32 | EXTERNAL_INTERRUPT_CONTROLLER_RSTR_BIT;
    //set the NVIC to respond to EXTI9_5 -- 5 through 9 are all same function
    ptr32 = (uint32_t *)NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31;
    //set equal to the position we want
    *ptr32 = EXTI_9_5_INTERRUPT_BIT;   
}

//IRQ handler for rising edge detection
void EXTI9_5_IRQHandler(void)
{
    //create pointers
    uint32_t *reg_pointer_32;
    //point to EXTI register
    reg_pointer_32 = (uint32_t * )EXTI_PENDING_REGISTER;
    //check if the right interrupt fired
    if ((*reg_pointer_32 & EXTI_PENDING_EXTI8) > 0)
    {
        //clear the interrupt
        *reg_pointer_32 = EXTI_PENDING_EXTI8;
        //add event to queue
        addToQueue( RISING_EDGE); 
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
  //debugPrint(30);
    // If status register says that the overflow interrupt has fired and it had beeen enabled
    if (( (*reg_pointer_16_sr & TIM_UIF) > 0) && ( (*reg_pointer_16_dier & TIM_UPDATE_INTERRUPT_ENABLE) > 0))
    {
        //clear interrupt
        *reg_pointer_16_sr = ~((uint16_t)TIM_UIF);
        //see if skip the first state fire...
        if (skipDelay() == 1)
        {
            //perform action
            addToQueue(TIM1_OVERFLOW);    
        }
    } 
}

//IRQ handler for timer 2 overflow
void TIM2_IRQHandler(void)    
{
  //create pointers
  uint16_t  * reg_pointer_16_sr;
  uint16_t  * reg_pointer_16_dier;
  uint32_t *  reg_pointer;
  //pointer to SR register
  reg_pointer_16_sr = (uint16_t *)TIM2_SR;  
  //pointer to IER register
  reg_pointer_16_dier = (uint16_t *)TIM2_INTERRUPT_ENABLE_REGISTER;
    // If status register says that the overflow interrupt has fired and it had beeen enabled
    if (( (*reg_pointer_16_sr & TIM_UIF) > 0) && ( (*reg_pointer_16_dier & TIM_UPDATE_INTERRUPT_ENABLE) > 0))
    {
        //clear interrupt
        *reg_pointer_16_sr = ~((uint16_t)TIM_UIF);
        if (skipDelay2() == 1)
        {
            //perform action
            addToQueue( TIM2_OVERFLOW);
        }
        //disable interrupt - enable it when want to start timer up again - act no
        //*reg_pointer_16_dier = ~TIM_UPDATE_INTERRUPT_BIT
        //need to only read every other timer rising edge as this timer operates at 2x frequency of other timer  
        //create pointer to CR1 to disable the timer
        reg_pointer = (uint32_t *) TIM2_CR1;
        //enable timer subsystem by setting the CEN bit to 1
        *reg_pointer = *reg_pointer & ~((uint16_t)0x01);  
    }  
}