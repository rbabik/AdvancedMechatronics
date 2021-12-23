#include "main.h"
#include "GPIO.h"
#include "timer.h"
#include "Interrupt.h"

/* maacros *-------*/

//for TIM3 Registers:
#define TIM3_BASE_REGISTER (uint32_t) 0x40000400
#define TIM3_CR1 (TIM3_BASE_REGISTER + 0x00)
#define TIM3_SR (TIM3_BASE_REGISTER + 0x10)
#define TIM3_EGR (TIM3_BASE_REGISTER + 0x14)
#define TIM3_CCMR1 (TIM3_BASE_REGISTER + 0x18)
#define TIM3_CCMR2 (TIM3_BASE_REGISTER + 0x1C)
#define TIM3_CCR3 (TIM3_BASE_REGISTER + 0x3C)
#define TIM3_CCER  (TIM3_BASE_REGISTER + 0x20)
#define TIM3_PSC (TIM3_BASE_REGISTER + 0x28)
#define TIM3_ARR (TIM3_BASE_REGISTER + 0x2C)
#define TIM3_CNT (TIM3_BASE_REGISTER + 0x24)
#define TIM3_DEIR (TIM3_BASE_REGISTER + 0x0C) 

//to enable interrupt
#define TIM_INTERRUPT_ENABLE_BIT    0x01 // interrupt on overflow
#define TIM_CC_INTERRUPT_ENABLE_BIT    0x8 // interrupt on CC

//flags for TIM3_CCMR registers:
#define CLEAR_OC3M           0x70
#define SET_OC3M_MODE_1      0x60
#define CLEAR_CC3S           0x3
#define OC3PE_BIT            0x8
#define TIM_CC3E_BIT         0x100
#define TIM_CEN_BIT          0x1
#define CLEAR_SR_UIF         0x1

//for TIM4 Registers
#define TIM4_BASE_ADDRESS ((uint32_t)0x40000800)
#define TIM4_CNT (TIM4_BASE_ADDRESS+0x24)
#define TIM4_PSC (TIM4_BASE_ADDRESS+0x28)
#define TIM4_ARR (TIM4_BASE_ADDRESS+0x2C)
#define TIM4_CR1 (TIM4_BASE_ADDRESS+0X00)
#define TIM4_SR (TIM4_BASE_ADDRESS+0x10)
#define TIM4_CCR1 (TIM4_BASE_ADDRESS+0x34)
#define TIM4_CCR2 (TIM4_BASE_ADDRESS+0x38)
#define TIM4_CCR3 (TIM4_BASE_ADDRESS+0x3C)
#define TIM4_CCR4 (TIM4_BASE_ADDRESS+0x40)
#define TIM4_CCMR1 (TIM4_BASE_ADDRESS+0x40)
#define TIM4_CCMR2 (TIM4_BASE_ADDRESS+0x1C)
#define TIM4_CCER (TIM4_BASE_ADDRESS+0x20)
#define TIM4_DIER (TIM4_BASE_ADDRESS+0x0C)

//flags for timer 4
#define UIF_FLAG                        0x01
#define CC3E                            (0x0100)
#define CEN                             ((uint16_t)0x01)
#define TIM_UPDATE_INTERRUPT_ENABLE     0x01

int32_t overflow;
uint32_t Pass;
uint32_t dutyCycle = 10000; //says ms to separate target up vs down
//duty cycle can range from 0 to 20000 to give 0-100%

uint16_t arrValue = 18000; //this leads to 10s period!

uint16_t initStateStartTime = 0;  //stores the timer value when start button is first pressed

//FUNCTIONS////////////////////////////////////////

//set duty cycle for the targets
//so if it is in high state we want target upright, if its in low state we 
//want the target down
uint16_t getDutyCycleState(void)
{
    uint32_t cntVal = getTimerCNT();   
    //compare to see if we are in high or low point of duty cycle
    //and return accordingly
    if (cntVal <= dutyCycle)
    {
        return 0;
    }
    else
    {
        return 1;
    } 
}


//get current count of timer 3
uint32_t getTimerCNT(void)
{
    uint32_t * ptr;
    uint32_t val;
    //set a pointer to get the value from the timer count
    ptr = (uint32_t *)TIM3_CNT;
    val = *ptr;
    return val;
}

//get current count of timer 4
uint32_t getTimer4CNT(void)
{
    uint32_t * ptr;
    uint32_t val;
    //set a pointer to get the value from the timer count
    ptr = (uint32_t *)TIM4_CNT;
    val = *ptr;
    return val;
}

//use pot to tune the difficulty by setting the ARR period
void setARR(uint32_t ARR)
{
    arrValue = ARR;
    //create pointer 
    uint32_t * ptr32;
    // set period value in auto reload register`
    ptr32 = (uint32_t *)TIM3_ARR;
    *ptr32 = arrValue;  //number gives percentage of 100% duty cycle - so # from 0 to 20000
}

//function to set the duty cycle on the timer to determine 
//how long targets are uprigth vs downward
void setDutyCycle(uint32_t dutyVal)
{
    dutyCycle = dutyVal;
    //create pointer 
    uint32_t * ptr32;
    // set value to compare in CCR3 register --> this sets the duty cycle
    ptr32 = (uint32_t *)TIM3_CCR3;
    *ptr32 = dutyCycle;  //number gives percentage of 100% duty cycle - so # from 0 to 20000
}


//get function for debugging
uint32_t getDutyVal(void)
{
    return dutyCycle;
}


void initTim3Channel3forPWM(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
    //enable the NVIC for timer 3
    enableNVIC_Timer3();
    
    uint32_t * ptr32;
    uint32_t prescalerValue = 44999; //want frequency of 30kHz
    
    // clear update event flag in status register
    ptr32 = (uint32_t *)TIM3_SR;
    *ptr32 = *ptr32 & (~(uint32_t)CLEAR_SR_UIF);
    
    // upload prescaler value to PSC
    ptr32 = (uint32_t *)TIM3_PSC;
    *ptr32 = prescalerValue;
    
    // set period value in auto reload register`
    ptr32 = (uint32_t *)TIM3_ARR;
    *ptr32 = arrValue;
    
    //create pointer to DIER
    ptr32 = (uint32_t *) TIM3_DEIR; 
    //enable timer to interrupt on overflow
    *ptr32 = TIM_INTERRUPT_ENABLE_BIT | TIM_CC_INTERRUPT_ENABLE_BIT; 
    
    // set output compare mode to OC3M bit fields in CCMR2 register and enable it as output
    ptr32 = (uint32_t *)(TIM3_CCMR2);
    *ptr32 = *ptr32 & (~(uint32_t)CLEAR_OC3M);
    *ptr32 = *ptr32 | SET_OC3M_MODE_1;
    *ptr32 = *ptr32 & (~(uint32_t)CLEAR_CC3S);
    
    // set value to compare in CCR3 register --> this sets the duty cycle
    ptr32 = (uint32_t *)TIM3_CCR3;
    *ptr32 = dutyCycle;  //number gives percentage of 100% duty cycle - so # from 0 to 20000
    
    // enable preload register by setting oc3pe bit in ccmr2
    ptr32 = (uint32_t *)TIM3_CCMR2;
    *ptr32 = *ptr32 | OC3PE_BIT;
    
    // enable TIM3 channel 3 by setting CC3E bit in CCER register
    ptr32 = (uint32_t *)(TIM3_CCER);
    *ptr32 = (uint32_t)TIM_CC3E_BIT;
    
    // disable timer by setting cen bit (0) in cr1
    ptr32 = (uint32_t *)TIM3_CR1;
    *ptr32 = *ptr32 & ~((uint16_t)TIM_CEN_BIT); // | TIM_CEN_BIT;
}


//disable timer 2
void disableTimer3(void)
{
    //create pointer
    uint32_t * reg_pointer;
    
    //TIMER 3 create pointer to CR1
    reg_pointer = (uint32_t *) TIM3_CR1;
    //disable timer subsystem by setting the CEN bit to 0
    *reg_pointer = *reg_pointer & ~((uint16_t)TIM_CEN_BIT);
}


//enable timer 2
void enableTimer3(void)
{
    //create pointer
    uint32_t * reg_pointer;
    
    //TIMER 3 create pointer to CR1
    reg_pointer = (uint32_t *) TIM3_CR1;
    //enable timer subsystem by setting the CEN bit to 1
    *reg_pointer = *reg_pointer | ((uint16_t)TIM_CEN_BIT);
    
    // set period value in auto reload register`
    reg_pointer = (uint32_t *)TIM3_ARR;
    //debugPrint(55555);
    debugPrint(*reg_pointer);

}

//initialize the global timer 4
void initTimer4NoInterrupt(void)
{
    uint16_t * reg_pointer_16;
    
    /* Timer 4 APB clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    
    /*enable the interrupt that would go to timer 4*/
    enableNVIC_Timer4();
    
    /* Compute Prescale and Autorreload */
    
    /* Clear any pending flags in the status register */
    reg_pointer_16 = (uint16_t *)TIM4_SR;
    *reg_pointer_16 =  ~((uint16_t)UIF_FLAG);
    
    /* Set Prescale and Autorreload */
    reg_pointer_16 = (uint16_t *)TIM4_PSC;
    *reg_pointer_16 = 44999;//Prescaler 2000hZ;
    reg_pointer_16 =(uint16_t *)TIM4_ARR;
    *reg_pointer_16 = 60000;//Auto, interrupt every 30 secs;
    
    /*enable interrupt on overflow timer 4*/
    reg_pointer_16 = (uint16_t *)TIM4_DIER;
    *reg_pointer_16 = TIM_UPDATE_INTERRUPT_ENABLE;
    overflow = 0;
    Pass = 1;
}


//This function starts timer4
void enableTimer4(void)
{
    //Time = 0;  //uncomment this once we create a global variable!!!!
    uint16_t *reg_pointer_16;
    
    /*Enable Timer*/
    reg_pointer_16 = (uint16_t*)TIM4_CR1;
    *reg_pointer_16 = *reg_pointer_16 | CEN;
    overflow = 0;
    //debugStartTimer(); //print that we started the timer!
}


//This function disables timer4
void disableTimer4(void) 
{
    uint16_t *reg_pointer_16;
    uint32_t *reg_pointer_32;
    //clear timer counter
    reg_pointer_32 = (uint32_t*)TIM4_CNT;
    *reg_pointer_32 = 0;
    reg_pointer_16 = (uint16_t*)TIM4_CR1;
    *reg_pointer_16 = *reg_pointer_16 & ~((uint16_t)CEN);

}


//this function gets the current time elapsed in seconds
uint32_t getTimer4(void)
{
    uint32_t *reg_pointer_32;
    uint32_t second;
    reg_pointer_32 = (uint32_t*)TIM4_CNT;
    //compute the timer counter and return secs. Overflow is tracked by using the variable overflow
    second = (uint32_t)(*reg_pointer_32/2000) + (uint32_t)(30*(overflow)); 
    return second;
}

//get the time at which the start button was first pressed
uint16_t getInitStateStartTime(void)
{
    return initStateStartTime;
}

//set the time at which the start button was first pressed
void setInitStateStartTime(uint16_t setTime)
{
    initStateStartTime = setTime;
}

void TIM4_IRQHandler(void)
{
     uint16_t * reg_pointer_16_sr;
     uint16_t * reg_pointer_16_dier;
     //uint16_t timeout = 2;
     reg_pointer_16_sr = (uint16_t *)TIM4_SR;
     reg_pointer_16_dier = (uint16_t *)TIM4_DIER;
     //check if Overflow triggered the interrupt: I.e. Timer Counter 3 >= Autorreload value
     if (( (*reg_pointer_16_sr & UIF_FLAG) >0) && ( (*reg_pointer_16_dier & TIM_UPDATE_INTERRUPT_ENABLE) >0))
     {
         //clear interrupt
         if (Pass ==1)
         {
             //guard control
             overflow = overflow - 1;
             Pass = Pass -1;
         }
         *reg_pointer_16_sr = ~((uint16_t)UIF_FLAG);
         overflow = overflow +1;
     }
}


uint32_t getOverflow(void){
    return overflow;
    }

