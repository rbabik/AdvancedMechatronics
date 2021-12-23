#include "Timer.h"
#include "Interrupt.h"
#include "stm32f4xx_rcc_mort.h"

/* Macros ------------------------------------------------------------------*/

//registers for timer 3
#define TIM3_BASE_REGISTER (uint32_t) 0x40000400
#define TIM3_CR1 (TIM3_BASE_REGISTER + 0x00)
#define TIM3_SR (TIM3_BASE_REGISTER + 0x10)
#define TIM3_PSC (TIM3_BASE_REGISTER + 0x28)
#define TIM3_ARR (TIM3_BASE_REGISTER + 0x2C)
#define TIM3_DEIR (TIM3_BASE_REGISTER + 0x0C) 

//registers for timer 2
#define TIM2_BASE_REGISTER (uint32_t) 0x40000000
#define TIM2_CR1 (TIM2_BASE_REGISTER + 0x00)
#define TIM2_SR (TIM2_BASE_REGISTER + 0x10)
#define TIM2_PSC (TIM2_BASE_REGISTER + 0x28)
#define TIM2_ARR (TIM2_BASE_REGISTER + 0x2C)
#define TIM2_DEIR (TIM2_BASE_REGISTER + 0x0C) 

//to enable interrupt
#define TIM_INTERRUPT_ENABLE_BIT    0x01// interrupt on overflow
//to enable counter
#define COUNTER_ENABLE_BIT          0x01

#define TIM3_EGR (TIM3_BASE_REGISTER + 0x14)
#define TIM3_CCMR1 (TIM3_BASE_REGISTER + 0x18)
#define TIM3_CCMR2 (TIM3_BASE_REGISTER + 0x1C)
//flags for TIM3_CCMR registers:
#define TIM_CCMR13_OC1M_0 (0b00010000)
#define TIM_CCMR13_OC1M_1 (0b00100000)
#define TIM_CCMR13_OC1M_2 (0b01000000)
#define TIM_CCMR13_OCPE (0b00001000)
#define TIM_CCMR13_OUTPUT 0x00
#define TIM3_CCER (TIM3_BASE_REGISTER + 0x20)
#define TIM3_CNT (TIM3_BASE_REGISTER + 0x24)
#define TIM3_PSC (TIM3_BASE_REGISTER + 0x28)
#define TIM3_CCR1 (TIM3_BASE_REGISTER + 0x34)
#define TIM3_CCR2 (TIM3_BASE_REGISTER + 0x38)
#define TIM3_CCR3 (TIM3_BASE_REGISTER + 0x3C)
#define TIM3_CCR4 (TIM3_BASE_REGISTER + 0x40)

//timer 3 interrupt enable register
# define TIM3_IER (TIM3_BASE_REGISTER + 0x0C)
//flags for interrupt enable register:
#define TIM_CH3_CC_IE 0x8 //timer channel 3 capture/compare interrupt
#define TIM_UPDATE_IE 0x1 //timer overflow or event interrup

uint16_t skipState = 0;
uint16_t skipState2 = 0;
    
/*Function definitions---------------------------------------------------------*/

//initialize timer 1 (using timer three for what we call timer 1!)
void initialize_TIM3(void)
{
    //create pointer
    uint32_t * reg_pointer;
    //create prescalar variable
    uint16_t prescalerValue = 9999;  //9kHz
    //create arr value
    uint16_t autoReloadValue = 18000; //2s

    //enable the clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
    //enable the NVIC for timer 3 -- doing this in main!
    enableNVIC_Timer3();

    //create pointer to sr and clear update event flag
    reg_pointer = (uint32_t *)TIM3_SR;
    //clear first two bits
    *reg_pointer = ~((uint16_t)0x01);

    //create pointer to PSC
    reg_pointer = (uint32_t *) TIM3_PSC;
    //uploading the prescale value - determined based on chosen ARR value
    *reg_pointer = prescalerValue;

    //create pointer to ARR
    reg_pointer = (uint32_t *) TIM3_ARR;
    //set the wanted ARR value for a period of 2s
    *reg_pointer = autoReloadValue; 
    
    //create pointer to DIER
    reg_pointer = (uint32_t *) TIM3_DEIR; 
    //enable timer to interrupt on overflow
    *reg_pointer = TIM_INTERRUPT_ENABLE_BIT; 

    //create pointer to CR1
    reg_pointer = (uint32_t *) TIM3_CR1;
    //enable timer subsystem by setting the CEN bit to 1
    *reg_pointer = *reg_pointer | (uint16_t)0x01;
}

//intialize timer 2
void initialize_TIM2(void)
{
    //create pointer
    uint32_t * reg_pointer;
    //create prescalar variable
    uint16_t prescalerValue = 9999;  //9kHz
    //create arr value
    uint16_t autoReloadValue = 9000; //1s

    //enable the clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    //enable the NVIC for timer 2 -- doing this in main!
    enableNVIC_Timer2();

    //create pointer to sr and clear update event flag
    reg_pointer = (uint32_t *)TIM2_SR;
    //clear first two bits
    *reg_pointer = ~((uint32_t)0x01);

    //create pointer to PSC
    reg_pointer = (uint32_t *)TIM2_PSC;
    //uploading the prescale value - determined based on chosen ARR value
    *reg_pointer = prescalerValue;

    //create pointer to ARR
    reg_pointer = (uint32_t *) TIM2_ARR;
    //set the wanted ARR value for a period of 1s
    *reg_pointer = autoReloadValue; 
    
    //create pointer to DIER
    reg_pointer = (uint32_t *) TIM2_DEIR;
    //enable timer to interrupt on overflow
    *reg_pointer = TIM_INTERRUPT_ENABLE_BIT; //Mort: Missing dereferencer
    
    //create pointer to CR1
    reg_pointer = (uint32_t *) TIM2_CR1;
    //enable timer subsystem by setting the CEN bit to 1
    *reg_pointer = *reg_pointer | (uint16_t)0x01;
}

//disable timers - called in state machine at initialize
void diableTimers(void)
{
    //create pointer
    uint32_t * reg_pointer;
    
    //TIMER 3 create pointer to CR1
    reg_pointer = (uint32_t *) TIM3_CR1;
    //enable timer subsystem by setting the CEN bit to 1
    *reg_pointer = *reg_pointer & ~((uint16_t)0x01);
    
    //TIMER 2 create pointer to CR1
    reg_pointer = (uint32_t *) TIM2_CR1;
    //enable timer subsystem by setting the CEN bit to 1
    *reg_pointer = *reg_pointer & ~((uint16_t)0x01);
}

void disableTimer2(void)
{
    //create pointer
    uint32_t * reg_pointer;
    
    //TIMER 2 create pointer to CR1
    reg_pointer = (uint32_t *) TIM2_CR1;
    //enable timer subsystem by setting the CEN bit to 1
    *reg_pointer = *reg_pointer & ~((uint16_t)0x01);
}

uint16_t skipDelay(void)
{
    uint16_t currSkip = skipState;
    if (skipState == 0)
    { 
        skipState = 1;
    }
    return currSkip;
}

uint16_t skipDelay2(void)
{
    uint16_t currSkip = skipState2;
    if (skipState2 == 0)
    { 
        skipState2 = 1;
    }
    return currSkip;
}

