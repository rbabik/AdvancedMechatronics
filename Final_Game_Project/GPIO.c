/* Includes -----------------------------------------------------------------*/
#include "GPIO.h"
#include "main.h"
#include "stm32f4xx_rcc_mort.h" //Mort: missing the clock functions

/* MACROS ------------------------------------------------=------------------*/

//for GPIOF for analog input
#define GPIOF_BASE_REGISTER (uint32_t) 0x40021400
#define GPIOF_MODER (GPIOF_BASE_REGISTER + 0x00)
#define GPIOF_OTYPER (GPIOF_BASE_REGISTER + 0x04)
#define GPIOF_PUPDR (GPIOF_BASE_REGISTER + 0x0C)
//bits for the registers
#define GPIO7_MODER_ANALOG (((uint32_t)0x03)<<14)
#define GPIO7_OTYPER_PUSH_PULL 0x80
#define GPIO7_PUPDR_NO_PUPD 0xC000

#define GPIO8_MODER_ANALOG (((uint32_t)0x03)<<16)
#define GPIO8_OTYPER_PUSH_PULL 0x100
#define GPIO8_PUPDR_NO_PUPD 0x30000

#define GPIO9_MODER_ANALOG (((uint32_t)0x03)<<18)
#define GPIO9_OTYPER_PUSH_PULL 0x200
#define GPIO9_PUPDR_NO_PUPD 0xC0000

//PORT B
#define GPIOB_BASE_ADDRESS      0x40020400
#define MODER_REGISTER          (GPIOB_BASE_ADDRESS + 0x00)
#define OTYPER_REGISTER         (GPIOB_BASE_ADDRESS + 0x04)
#define OSPEEDR_REGISTER        (GPIOB_BASE_ADDRESS + 0x08)
#define PUPDR_REGISTER          (GPIOB_BASE_ADDRESS + 0x0C)
#define ODR_REGISTER            (GPIOB_BASE_ADDRESS + 0x14)
#define IDR_REGISTER            (GPIOB_BASE_ADDRESS + 0x10)
#define AFRL_REGISTER           (GPIOB_BASE_ADDRESS + 0x20)
#define AFRH_REGISTER           (GPIOB_BASE_ADDRESS + 0x24)

//flags for PORT B
#define CLEAR_MODER0            0x3
#define MODER0_ALT_FUNC         0x2
#define OTYPER0_PUSH_PULL       0x1
#define OSPEEDR0_HIGH           0x3
#define PUPDR0_NPU_NPD          0x3
#define CLEAR_AFRL0             0xF
#define AFRL0_AF2               0x2

//for GPIOC
#define GPIOC_BASE_REGISTER (uint32_t) 0x40020800
#define GPIOC_MODER (GPIOC_BASE_REGISTER + 0x00)
#define GPIOC_OTYPER (GPIOC_BASE_REGISTER + 0x04)
#define GPIOC_OSPEEDR (GPIOC_BASE_REGISTER + 0x08)
#define GPIOC_PUPDR (GPIOC_BASE_REGISTER + 0x0C)
#define GPIOC_IDR (GPIOC_BASE_REGISTER + 0x10)
#define GPIOC_ODR (GPIOC_BASE_REGISTER + 0x14)
#define GPIOC_AFRL (GPIOC_BASE_REGISTER + 0x20)
#define GPIOC_AFRH (GPIOC_BASE_REGISTER + 0x24)

//for PORT B pins 0-5 -- digital input pins for magnetic sensors
#define GPIO_012345_MODER           0b111111111111
#define GPIO_012345_MODER_IN        0b000000
#define GPIO_012345_MODER_OUT       0b010101010101
#define GPIO_012345_OTYPER          0b111111
#define GPIO_012345_OTYPER_PP       0b000000
#define GPIO_012345_OSPEEDR         0b111111111111
#define GPIO_012345_OSPEEDR_HI      0b111111111111
#define GPIO_012345_PUPDR           0b111111111111
#define GPIO_PUPDR_NOPULL           0b00
#define GPIO_012345_PUPDR_PD        0b101010101010

// Pin 8 -- rising edge input
#define CLEAR_MODER_8           (uint32_t)0x30000 // leave cleared to set to input
#define CLEAR_OTYPER_8          (uint32_t)0x100   // leave cleared to set to push-pull
#define CLEAR_OSPEEDR_8         (uint32_t)0x30000
#define SET_OSPEEDR_8_HIGH      (uint32_t)0x30000 // 11 for high speed
#define CLEAR_PUPDR_8           (uint32_t)0x30000 
#define SET_PUPDR_8_PU          (uint32_t)0x10000 // 01 for pull up
#define SET_PUPDR_8_PD          (uint32_t)0x20000
#define IDR_8                   (uint32_t)0x100   // bit 8 (9th) for input data reg 8

//for bit 8 - rising edge start switch
#define BIT16_17HI      0x30000
#define BIT17HI         0x20000
#define BIT16HI         0x10000
#define BIT8HI          0x100

//define bits for pin PC9 LED strip
#define BIT18_19HI      0xC0000
#define BIT18HI         0x40000
#define BIT9HI          0x200  
#define BIT4_7HI        0xF0
#define BIT5HI          0x20
#define MOTOR_DIR      0x200


//set up GPIO B pin 0 to test PWM
void initialize_GPIOB_pin0(void)
{
    uint32_t * ptr32;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
    // config as output by setting 01;
    ptr32 = (uint32_t *)MODER_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)CLEAR_MODER0);
    *ptr32 = *ptr32 | MODER0_ALT_FUNC;
    
    // config as push pull by clearing to 00;
    ptr32 = (uint32_t *)OTYPER_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)OTYPER0_PUSH_PULL);
    
    // config to high speed by setting 11;
    ptr32 = (uint32_t *)OSPEEDR_REGISTER;
    *ptr32 = *ptr32 | OSPEEDR0_HIGH;
    
    // config to npu npd by clearing to 00;
    ptr32 = (uint32_t *)PUPDR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)PUPDR0_NPU_NPD);
    
    // config pin in alternative function 2 by setting 0010;
    ptr32 = (uint32_t *)AFRL_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)CLEAR_AFRL0);
    *ptr32 = *ptr32 | AFRL0_AF2;
}


//initialize GPIO F pin 7 as analog
void initGPIOF7AsAnalog(void)
{
    //create pointer   
    uint32_t * reg_pointer;
    //start the clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    
    //create pointer to moder
    reg_pointer = (uint32_t *)GPIOF_MODER;
    //set to analog
    *reg_pointer = *reg_pointer | ((uint32_t)GPIO7_MODER_ANALOG);
    
    //create pointer to otyper
    reg_pointer = (uint32_t *) GPIOF_OTYPER;
    //output push-pull
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO7_OTYPER_PUSH_PULL));

    //create pointer to pupdr
    reg_pointer = (uint32_t *) GPIOF_PUPDR;
    //set for Pupdr so no pullup or pulldown
    *reg_pointer = *reg_pointer & (~(uint32_t)GPIO7_PUPDR_NO_PUPD);
} 


//initialize pin PC8 for start button rising edge input
void initialize_GPIOC_pinPC8(void)
{
    //create pointer   
    uint32_t * reg_pointer;
    //start the clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    
    //create pointer to moder
    reg_pointer = (uint32_t *)GPIOC_MODER;
    //clear two bits - this sets to input
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT16_17HI));
    
    //create pointer to otyper
    reg_pointer = (uint32_t *) GPIOC_OTYPER;
    //clear bit for output push-pull
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT8HI));
    
    //create pointer to pupdr
    reg_pointer = (uint32_t *) GPIOC_PUPDR;
    //clear 16 and 17 bits 
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT16_17HI));
    //set bit 17 for Pupdr so pulldown
    *reg_pointer = *reg_pointer | (uint32_t)BIT17HI;
}     


//determine if pin 8 is currently high or low
uint8_t is_GPIOC_pinPC8_high(void)
{
    //create pointer to odr
    uint32_t *reg_pointer_idr = (uint32_t *) GPIOC_IDR;
    //create variable for reading value
    uint8_t value;
    //see if have high in odr bit
    value = ((*reg_pointer_idr & (uint32_t)BIT8HI)>>8);
    //if the and operator made value 1
    if (value > 0) 
        //return high
        return 1;
    else 
        //return low
        return 0;
} 

//determine if pin 9 is currently high or low
uint8_t is_GPIOC_pinPC9_high(void)
{
    //create pointer to odr
    uint32_t *reg_pointer_idr = (uint32_t *) GPIOC_IDR;
    //create variable for reading value
    uint8_t value;
    //see if have high in odr bit
    value = ((*reg_pointer_idr & (uint32_t)BIT9HI)>>9);
    //if the and operator made value 1
    if (value > 0) 
        //return high
        return 1;
    else 
        //return low
        return 0;
} 


//initialize pin PC9 for LED strip
void initialize_GPIOC_pinPC9(void)
{   
    //create pointer
    uint32_t * reg_pointer;
    //start the clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    
     //create pointer to moder
    reg_pointer = (uint32_t *)GPIOC_MODER;
    //clear two bits 18 and 19
    *reg_pointer = *reg_pointer & (~(uint32_t)BIT18_19HI);
    //set to output bit 18
    *reg_pointer = *reg_pointer | (uint32_t)BIT18HI;
    
    //create pointer to otyper
    reg_pointer = (uint32_t *) GPIOC_OTYPER;
    //clear bit 9 for output push-pull
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT9HI));

    //create pointer to ospeedr
    reg_pointer = (uint32_t *) GPIOC_OSPEEDR;
    //clear 18 and 19  
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT18_19HI));
    //set 18 and 19 bits for high speed 
    *reg_pointer = *reg_pointer | (uint32_t)BIT18_19HI;
    
    //create pointer to pupdr
    reg_pointer = (uint32_t *) GPIOC_PUPDR;
    //clear 18 and 19 bits for Pupdr so no pullup or pulldown
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT18_19HI));

    //create pointer to odr
    reg_pointer = (uint32_t *) GPIOC_ODR;
    //clear bit 9
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT9HI));
}


//pin PC9 high - drive LED strip on
void GPIOC_pinPC9_high(void )
{
    //create pointer
    uint32_t *reg_pointer_odr;
    //set to odr
    reg_pointer_odr = (uint32_t *) GPIOC_ODR;
    //set bit 9 to high
    *reg_pointer_odr = *reg_pointer_odr | ((uint32_t)BIT9HI); 
}


//pin PC9 low - drive LED strip off
void GPIOC_pinPC9_low(void )
{
    //create pointer
    uint32_t *reg_pointer_odr;
    //set to odr
    reg_pointer_odr = (uint32_t *) GPIOC_ODR;
    //set bit 9 to low
    *reg_pointer_odr = *reg_pointer_odr & (~((uint32_t)BIT9HI));
}


//initialize the 6 digital input pins for magnetic sensors
void init_GPIOB_pin_0To5(void)
{
    uint32_t * reg_pointer;
    
    /* GPIOC Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
    /* GPIOC Pin 6 as input*/
    reg_pointer = (uint32_t *)MODER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_012345_MODER));
    *reg_pointer = *reg_pointer | GPIO_012345_MODER_IN;
    
    /*PUSH-PULL Pin*/
    reg_pointer = (uint32_t *)OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_012345_OTYPER));
    *reg_pointer = *reg_pointer | GPIO_012345_OTYPER_PP;
    
    /*GPIOC pin 6 high speed */
    reg_pointer = (uint32_t *)OSPEEDR_REGISTER;
    *reg_pointer = *reg_pointer | GPIO_012345_OSPEEDR_HI;
    
    /*Configure floating*/
    reg_pointer = (uint32_t *)PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_012345_PUPDR));
    *reg_pointer = *reg_pointer | GPIO_PUPDR_NOPULL;
}


//get the 0 or 1 state of the specified pin 
//give index from 0 to 5
uint16_t getGPIOBpinState(uint16_t index)
{
    //create return variable and pointer
    uint16_t output;
    uint32_t * reg_pointer;
    
    //point to the IDR register
    reg_pointer = (uint32_t *)IDR_REGISTER;
    output = *reg_pointer;
    //mask other bits and shift the wanted bit
    output = (((output & (1<<index)))>>index);
    //invert the bit because we want it to be high when the targets are up
    output = (output ^ 1);
    return output;
}
