#include "main.h"
#include "GPIO.h"
#include "stm32f4xx_rcc_mort.h"

//for GPIOB
#define GPIOB_BASE_REGISTER (uint32_t) 0x40020400
#define GPIOB_MODER (GPIOB_BASE_REGISTER + 0x00)
#define GPIOB_OTYPER (GPIOB_BASE_REGISTER + 0x04)
#define GPIOB_OSPEEDR (GPIOB_BASE_REGISTER + 0x08)
#define GPIOB_PUPDR (GPIOB_BASE_REGISTER + 0x0C)
#define GPIOB_IDR (GPIOB_BASE_REGISTER + 0x10)
#define GPIOB_ODR (GPIOB_BASE_REGISTER + 0x14)

//for GPIOC
#define GPIOC_BASE_REGISTER (uint32_t) 0x40020800
#define GPIOC_MODER (GPIOC_BASE_REGISTER + 0x00)
#define GPIOC_OTYPER (GPIOC_BASE_REGISTER + 0x04)
#define GPIOC_OSPEEDR (GPIOC_BASE_REGISTER + 0x08)
#define GPIOC_PUPDR (GPIOC_BASE_REGISTER + 0x0C)
#define GPIOC_IDR (GPIOC_BASE_REGISTER + 0x10)
#define GPIOC_ODR (GPIOC_BASE_REGISTER + 0x14)
#define GPIOC_AFRL (GPIOC_BASE_REGISTER + 0x20)

//masks

//for bit 12 - phototransistor
#define BIT24_25HI      0b11000000000000000000000000
#define BIT25HI         0b10000000000000000000000000
#define BIT12HI         0x1000

//for bit 11 - LED 3
#define BIT22_23HI      0b110000000000000000000000
#define BIT22HI         0b10000000000000000000000
#define BIT11HI         0b100000000000

//for bit 10 - LED 2
#define BIT20_21HI      0b1100000000000000000000
#define BIT20HI         0b100000000000000000000
#define BIT10HI         0b10000000000

//for bit 9 - LED 1
#define BIT18_19HI      0b11000000000000000000
#define BIT18HI         0b1000000000000000000
#define BIT9HI          0x100  
#define NATESMACRO      0x200

//for bit 8 - rising edge switch
#define BIT16_17HI      0b110000000000000000
#define BIT17HI         0b100000000000000000
#define BIT16HI         0b10000000000000000
#define BIT8HI          0b100000000


//initialize pin PC8 for RISING EDGE INPUT
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

//initialize pin PC9 for LED 1 OUTPUT
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
    
//initialize pin PC10 for LED 2 OUTPUT
void initialize_GPIOC_pinPC10(void)
{   
    //create pointer
    uint32_t * reg_pointer;
    //start the clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    
     //create pointer to moder
    reg_pointer = (uint32_t *)GPIOC_MODER;
    //clear two bits 20 and 21
    *reg_pointer = *reg_pointer & (~(uint32_t)BIT20_21HI);
    //set to output bit 20
    *reg_pointer = *reg_pointer | (uint32_t)BIT20HI;
    
    //create pointer to otyper
    reg_pointer = (uint32_t *) GPIOC_OTYPER;
    //clear bit 10 for output push-pull
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT10HI));

    //create pointer to ospeedr
    reg_pointer = (uint32_t *) GPIOC_OSPEEDR;
    //clear 20 and 21  
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT20_21HI));
    //set 20 and 21 bits for high speed 
    *reg_pointer = *reg_pointer | (uint32_t)BIT20_21HI;
    
    //create pointer to pupdr
    reg_pointer = (uint32_t *) GPIOC_PUPDR;
    //clear 20 and 21 bits for Pupdr so no pullup or pulldown
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT20_21HI));

    //create pointer to odr
    reg_pointer = (uint32_t *) GPIOC_ODR;
    //clear bit 10
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT10HI));
}

//initialize pin PC11 for LED 3 OUTPUT
void initialize_GPIOC_pinPC11(void)
{   
    //create pointer
    uint32_t * reg_pointer;
    //start the clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    
    //create pointer to moder
    reg_pointer = (uint32_t *)GPIOC_MODER;
    //clear two bits 22 and 23
    *reg_pointer = *reg_pointer & (~(uint32_t)BIT22_23HI);
    //set to output bit 22
    *reg_pointer = *reg_pointer | (uint32_t)BIT22HI;
    
    //create pointer to otyper
    reg_pointer = (uint32_t *) GPIOC_OTYPER;
    //clear bit 11 for output push-pull
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT11HI));

    //create pointer to ospeedr
    reg_pointer = (uint32_t *) GPIOC_OSPEEDR;
    //clear 22 and 23  
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT22_23HI));
    //set 22 and 23 bits for high speed 
    *reg_pointer = *reg_pointer | (uint32_t)BIT22_23HI;
    
    //create pointer to pupdr
    reg_pointer = (uint32_t *) GPIOC_PUPDR;
    //clear 22 and 23 bits for Pupdr so no pullup or pulldown
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT22_23HI));

    //create pointer to odr
    reg_pointer = (uint32_t *) GPIOC_ODR;
    //clear bit 11
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT11HI));
}

//initialize input pin PC12 for phototransistor
void initialize_GPIOC_pinPC12(void)
{
    //create pointer
    uint32_t * reg_pointer;
    //start the clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    
    //create pointer to moder
    reg_pointer = (uint32_t *)GPIOC_MODER;
    //clear two bits 24 and 25
    *reg_pointer = *reg_pointer & (~(uint32_t)BIT24_25HI);
    
    //create pointer to otyper
    reg_pointer = (uint32_t *) GPIOC_OTYPER;
    //clear bit 12 for output push-pull
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT12HI));

    //create pointer to ospeedr
    reg_pointer = (uint32_t *) GPIOC_OSPEEDR;
    //clear 24 and 25  
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT24_25HI));
    //set 24 and 25 bits for high speed 
    *reg_pointer = *reg_pointer | (uint32_t)BIT24_25HI;
    
    //create pointer to pupdr
    reg_pointer = (uint32_t *) GPIOC_PUPDR;
    //clear 24 and 25
    *reg_pointer = *reg_pointer & (~((uint32_t)BIT24_25HI));
    //set bit 25 for pull-down
    //bits for Pupdr so no pullup or pulldown
    *reg_pointer = *reg_pointer | (uint32_t)BIT25HI;
}


//pin PC9 high - turn LED 1 on
void GPIOC_pinPC9_high(void )
{
    //create pointer
    uint32_t *reg_pointer_odr;
    //set to odr
    reg_pointer_odr = (uint32_t *) GPIOC_ODR;
    //set bit 9 to high
    *reg_pointer_odr = *reg_pointer_odr | ((uint32_t)NATESMACRO); 
    uint32_t value = *reg_pointer_odr;
}

//pin PC9 low - turn LED 1 off
void GPIOC_pinPC9_low(void )
{
    //create pointer
    uint32_t *reg_pointer_odr;
    //set to odr
    reg_pointer_odr = (uint32_t *) GPIOC_ODR;
    //set bit 9 to low
    *reg_pointer_odr = *reg_pointer_odr & (~((uint32_t)NATESMACRO));
}

//pin PC10 high - turn LED 2 on
void GPIOC_pinPC10_high(void )
{
    //create pointer
    uint32_t *reg_pointer_odr;
    //set to odr
    reg_pointer_odr = (uint32_t *) GPIOC_ODR;
    //set bit 10 to high
    *reg_pointer_odr = *reg_pointer_odr | ((uint32_t)BIT10HI); 
}

//pin PC10 low - turn LED 2 off
void GPIOC_pinPC10_low(void )
{
    //create pointer
    uint32_t *reg_pointer_odr;
    //set to odr
    reg_pointer_odr = (uint32_t *) GPIOC_ODR;
    //set bit 10 to low
    *reg_pointer_odr = *reg_pointer_odr & (~((uint32_t)BIT10HI));
}

//pin PC11 high - turn LED 3 on
void GPIOC_pinPC11_high(void )
{
    //create pointer
    uint32_t *reg_pointer_odr;
    //set to odr
    reg_pointer_odr = (uint32_t *) GPIOC_ODR;
    //set bit 11 to high
    *reg_pointer_odr = *reg_pointer_odr | ((uint32_t)BIT11HI); 
}

//pin PC11 low - turn LED 3 off
void GPIOC_pinPC11_low(void )
{
    //create pointer
    uint32_t *reg_pointer_odr;
    //set to odr
    reg_pointer_odr = (uint32_t *) GPIOC_ODR;
    //set bit 11 to low
    *reg_pointer_odr = *reg_pointer_odr & (~((uint32_t)BIT11HI));
}

//determine if pin 12 is currently high or low
uint8_t is_GPIOC_pinPC12_high(void)
{
    //create pointer to odr
    uint32_t *reg_pointer_idr = (uint32_t *) GPIOC_IDR;
    //create variable for reading value
    uint8_t value;
    //see if have high in odr bit
    value = ((*reg_pointer_idr & (uint32_t)BIT12HI)>>12);
    //if the and operator made value 1
    if (value > 0) 
        //return high
        return 1;
    else 
        //return low
        return 0;
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