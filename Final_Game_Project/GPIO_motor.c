/* Includes -----------------------------------------------------------------*/
#include "GPIO_motor.h"
#include "main.h"
#include "stm32f4xx_rcc_mort.h" //Mort: missing the clock functions
/* MACROS -------------------------------------------------------------------*/

//Port E addresses:
#define PORTE_BASE_ADDRESS ((uint32_t)0x40021000)
#define PORTE_MODER_REGISTER (PORTE_BASE_ADDRESS + 0x00)
#define PORTE_OTYPER_REGISTER (PORTE_BASE_ADDRESS + 0x04)
#define PORTE_OSPEEDR_REGISTER (PORTE_BASE_ADDRESS + 0x08)
#define PORTE_PUPDR_REGISTER (PORTE_BASE_ADDRESS + 0x0C)
#define PORTE_ODR_REGISTER (PORTE_BASE_ADDRESS + 0x14)

//Port B addresses:
#define PORTB_BASE_ADDRESS ((uint32_t)0x40020400)
#define PORTB_MODER_REGISTER (PORTB_BASE_ADDRESS + 0x00)
#define PORTB_OTYPER_REGISTER (PORTB_BASE_ADDRESS + 0x04)
#define PORTB_OSPEEDR_REGISTER (PORTB_BASE_ADDRESS + 0x08)
#define PORTB_PUPDR_REGISTER (PORTB_BASE_ADDRESS + 0x0C)
#define PORTB_ODR_REGISTER (PORTB_BASE_ADDRESS + 0x14)

//moder macros
#define GPIO_7_MODER_OUT            (uint32_t)(0x01<<14)
#define GPIO_8_MODER_OUT            (uint32_t)(0x01<<16)
#define GPIO_9_MODER_OUT            (uint32_t)(0x01<<18)
#define GPIO_10_MODER_OUT            (uint32_t)(0x01<<20)
#define GPIO_11_MODER_OUT            (uint32_t)(0x01<<22)
#define GPIO_12_MODER_OUT            (uint32_t)(0x01<<24)
#define GPIO_13_MODER_OUT            (uint32_t)(0x01<<26)
#define GPIO_14_MODER_OUT            (((uint32_t)0x01)<<28)
#define GPIO_15_MODER_OUT            (((uint32_t)0x01)<<30)

//otyper macros
#define GPIO_7_OTYPER_PP            0x00
#define GPIO_8_OTYPER               (((uint32_t)0x01)<<8)
#define GPIO_8_OTYPER_PP            0x00
#define GPIO_9_OTYPER               (((uint32_t)0x01)<<9)
#define GPIO_9_OTYPER_PP            0x00
#define GPIO_10_OTYPER               (((uint32_t)0x01)<<10)
#define GPIO_10_OTYPER_PP            0x00
#define GPIO_11_OTYPER               (((uint32_t)0x01)<<11)
#define GPIO_11_OTYPER_PP            0x00
#define GPIO_12_OTYPER               (((uint32_t)0x01)<<12)
#define GPIO_12_OTYPER_PP            0x00
#define GPIO_13_OTYPER               (((uint32_t)0x01)<<13)
#define GPIO_13_OTYPER_PP            0x00
#define GPIO_14_OTYPER               (((uint32_t)0x01)<<14)
#define GPIO_14_OTYPER_PP            0x00
#define GPIO_15_OTYPER               (((uint32_t)0x01)<<15)
#define GPIO_15_OTYPER_PP            0x00

//ospeedr macros
#define GPIO_7_OSPEEDR_HIGH_SPEED   (((uint32_t)0x3)<<14) 
#define GPIO_8_OSPEEDR_HIGH_SPEED   (((uint32_t)0x3)<<16) 
#define GPIO_9_OSPEEDR_HIGH_SPEED   (((uint32_t)0x3)<<18) 
#define GPIO_10_OSPEEDR_HIGH_SPEED   (((uint32_t)0x3)<<20) 
#define GPIO_11_OSPEEDR_HIGH_SPEED   (((uint32_t)0x3)<<22) 
#define GPIO_12_OSPEEDR_HIGH_SPEED   (((uint32_t)0x3)<<24) 
#define GPIO_13_OSPEEDR_HIGH_SPEED   (((uint32_t)0x3)<<26) 
#define GPIO_14_OSPEEDR_HIGH_SPEED   (((uint32_t)0x3)<<28) 
#define GPIO_15_OSPEEDR_HIGH_SPEED   (((uint32_t)0x3)<<30) 

//pupdr macros
#define GPIO_7_PUPDR                (((uint32_t)0x03)<<14)
#define GPIO_8_PUPDR                (uint32_t)(0x03<<16)
#define GPIO_9_PUPDR                (uint32_t)(0x03<<18)
#define GPIO_10_PUPDR                (uint32_t)(0x03<<20)
#define GPIO_11_PUPDR                (uint32_t)(0x03<<22)
#define GPIO_12_PUPDR                (uint32_t)(0x03<<22)
#define GPIO_13_PUPDR                (uint32_t)(0x03<<22)
#define GPIO_14_PUPDR                (((uint32_t)0x03)<<28)
#define GPIO_15_PUPDR                (((uint32_t)0x03)<<30)

//odr macros
#define GPIO_7_ODR_HIGH               (uint32_t)(0x01<<7)
#define GPIO_8_ODR_HIGH               (uint32_t)(0x01<<8)
#define GPIO_9_ODR_HIGH               (uint32_t)(0x01<<9)
#define GPIO_10_ODR_HIGH              (uint32_t)(0x01<<10)
#define GPIO_11_ODR_HIGH              (uint32_t)(0x01<<11)
#define GPIO_12_ODR_HIGH              (uint32_t)(0x01<<12)
#define GPIO_13_ODR_HIGH              (uint32_t)(0x01<<13)
#define GPIO_14_ODR_HIGH              (uint32_t)(0x01<<14)
#define GPIO_15_ODR_HIGH              (uint32_t)(0x01<<15)



/* FUNCTIONS ----------------------------------------------------------------*/

// Initialize E7-15 pins as output pins
void initGPIOE7_15_asOutput(void) {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    
    uint32_t * ptr32;
    // moder -- set to output
    ptr32 = (uint32_t *)PORTE_MODER_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_7_MODER_OUT | GPIO_8_MODER_OUT | GPIO_9_MODER_OUT
                                | GPIO_10_MODER_OUT | GPIO_11_MODER_OUT | GPIO_12_MODER_OUT
                                | GPIO_13_MODER_OUT | GPIO_14_MODER_OUT | GPIO_15_MODER_OUT));
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_7_MODER_OUT | GPIO_8_MODER_OUT | GPIO_9_MODER_OUT
                                | GPIO_10_MODER_OUT | GPIO_11_MODER_OUT | GPIO_12_MODER_OUT
                                | GPIO_13_MODER_OUT | GPIO_14_MODER_OUT | GPIO_15_MODER_OUT));
    
    // otyper -- set to push pull 
    ptr32 = (uint32_t *)PORTE_OTYPER_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_7_OTYPER_PP | GPIO_8_OTYPER_PP | GPIO_9_OTYPER_PP
                                | GPIO_10_OTYPER_PP | GPIO_11_OTYPER_PP | GPIO_12_OTYPER_PP
                                | GPIO_13_OTYPER_PP | GPIO_14_OTYPER_PP | GPIO_15_OTYPER_PP));
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_7_OTYPER_PP | GPIO_8_OTYPER_PP | GPIO_9_OTYPER_PP
                                | GPIO_10_OTYPER_PP | GPIO_11_OTYPER_PP | GPIO_12_OTYPER_PP
                                | GPIO_13_OTYPER_PP | GPIO_14_OTYPER_PP | GPIO_15_OTYPER_PP));
   
    // ospeedr -- set to high speed
    ptr32 = (uint32_t *)PORTE_OSPEEDR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_7_OSPEEDR_HIGH_SPEED | GPIO_8_OSPEEDR_HIGH_SPEED
                                | GPIO_9_OSPEEDR_HIGH_SPEED | GPIO_10_OSPEEDR_HIGH_SPEED
                                | GPIO_11_OSPEEDR_HIGH_SPEED | GPIO_12_OSPEEDR_HIGH_SPEED
                                | GPIO_13_OSPEEDR_HIGH_SPEED | GPIO_14_OSPEEDR_HIGH_SPEED
                                | GPIO_15_OSPEEDR_HIGH_SPEED));
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_7_OSPEEDR_HIGH_SPEED | GPIO_8_OSPEEDR_HIGH_SPEED
                                | GPIO_9_OSPEEDR_HIGH_SPEED | GPIO_10_OSPEEDR_HIGH_SPEED
                                | GPIO_11_OSPEEDR_HIGH_SPEED | GPIO_12_OSPEEDR_HIGH_SPEED
                                | GPIO_13_OSPEEDR_HIGH_SPEED | GPIO_14_OSPEEDR_HIGH_SPEED
                                | GPIO_15_OSPEEDR_HIGH_SPEED));

    // pupdr -- set to no pull up no pull down
    ptr32 = (uint32_t *)PORTE_PUPDR_REGISTER;
    *ptr32 = *ptr32 & ((uint32_t)(GPIO_7_PUPDR | GPIO_8_PUPDR | GPIO_9_PUPDR
                                | GPIO_10_PUPDR | GPIO_11_PUPDR | GPIO_12_PUPDR
                                | GPIO_13_PUPDR | GPIO_14_PUPDR | GPIO_15_PUPDR)); 
    *ptr32 = *ptr32 | ((uint32_t)(0x00)); // 00 for no pull

    // odr -- set to low (clear)
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 & ((uint32_t)(GPIO_7_ODR_HIGH | GPIO_8_ODR_HIGH | GPIO_9_ODR_HIGH
                                | GPIO_10_ODR_HIGH | GPIO_11_ODR_HIGH | GPIO_12_ODR_HIGH
                                | GPIO_13_ODR_HIGH | GPIO_14_ODR_HIGH | GPIO_15_ODR_HIGH));
}

// Initialize B9-11 pins as output pins
void initGPIOB9_11_asOutput(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
    uint32_t * ptr32;
    // moder -- set to output
    ptr32 = (uint32_t *)PORTB_MODER_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_9_MODER_OUT | GPIO_10_MODER_OUT | GPIO_11_MODER_OUT));
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_9_MODER_OUT | GPIO_10_MODER_OUT | GPIO_11_MODER_OUT));
    
    // otyper -- set to push pull 
    ptr32 = (uint32_t *)PORTB_OTYPER_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_9_OTYPER_PP | GPIO_10_OTYPER_PP | GPIO_11_OTYPER_PP));
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_9_OTYPER_PP | GPIO_10_OTYPER_PP | GPIO_11_OTYPER_PP));
   
    // ospeedr -- set to high speed
    ptr32 = (uint32_t *)PORTB_OSPEEDR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_9_OSPEEDR_HIGH_SPEED | GPIO_10_OSPEEDR_HIGH_SPEED | GPIO_11_OSPEEDR_HIGH_SPEED));
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_9_OSPEEDR_HIGH_SPEED | GPIO_10_OSPEEDR_HIGH_SPEED | GPIO_11_OSPEEDR_HIGH_SPEED));

    // pupdr -- set to no pull up no pull down
    ptr32 = (uint32_t *)PORTB_PUPDR_REGISTER;
    *ptr32 = *ptr32 & ((uint32_t)(GPIO_9_PUPDR | GPIO_10_PUPDR | GPIO_11_PUPDR)); 
    *ptr32 = *ptr32 | ((uint32_t)(0x00)); // 00 for no pull

    // odr -- set to low (clear)
    ptr32 = (uint32_t *)PORTB_ODR_REGISTER;
    *ptr32 = *ptr32 & ((uint32_t)(GPIO_9_ODR_HIGH | GPIO_10_ODR_HIGH | GPIO_11_ODR_HIGH));
}

void PE7_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_7_ODR_HIGH));
}

void PE8_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_8_ODR_HIGH));   
}

void PE9_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_9_ODR_HIGH));    
}

void PE10_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_10_ODR_HIGH));    
}

void PE11_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_11_ODR_HIGH));    
}

void PE12_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_12_ODR_HIGH));    
}

void PE13_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_13_ODR_HIGH));    
}

void PE14_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_14_ODR_HIGH));    
}

void PE15_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_15_ODR_HIGH));    
}

void PB9_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTB_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_9_ODR_HIGH));     
}

void PB10_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTB_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_10_ODR_HIGH));    
}

void PB11_HIGH(void)
{
    uint32_t * ptr32; 
    // odr -- clear and then set high
    ptr32 = (uint32_t *)PORTB_ODR_REGISTER;
    *ptr32 = *ptr32 | ((uint32_t)(GPIO_11_ODR_HIGH));    
}

void PE7_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_7_ODR_HIGH)); 
}

void PE8_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_8_ODR_HIGH));    
}

void PE9_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_9_ODR_HIGH));    
}

void PE10_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_10_ODR_HIGH));    
}

void PE11_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_11_ODR_HIGH));    
}

void PE12_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_12_ODR_HIGH));
}

void PE13_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_13_ODR_HIGH));    
}

void PE14_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_14_ODR_HIGH));    
}

void PE15_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTE_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_15_ODR_HIGH));
}

void PB9_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTB_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_9_ODR_HIGH));    
}

void PB10_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTB_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_10_ODR_HIGH));    
}

void PB11_LOW(void)
{
    uint32_t * ptr32;
    // odr -- clear
    ptr32 = (uint32_t *)PORTB_ODR_REGISTER;
    *ptr32 = *ptr32 & (~(uint32_t)(GPIO_11_ODR_HIGH));   
}