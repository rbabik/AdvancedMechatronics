#include "ADC.h"
#include "GPIO.h"
#include "DMA.h"
#include "timer.h"

//ADC Registers
#define ADC_BASE_ADDRESS 0x40012000
#define ADC3_BASE_ADDRESS (ADC_BASE_ADDRESS + 0x200)
#define ADC3_SR (ADC3_BASE_ADDRESS + 0x00)
#define ADC3_CR2 (ADC3_BASE_ADDRESS + 0x08)
#define ADC3_SWSTART 0x40000000
#define ADC_CCR (ADC_BASE_ADDRESS + 0x300 + 0x04)
#define ADC3_CR1 (ADC3_BASE_ADDRESS + 0x04)
#define ADC3_SQR1 (ADC3_BASE_ADDRESS + 0x2C)
#define ADC3_SMPR2 (ADC3_BASE_ADDRESS + 0x10)
#define ADC3_SQR3 (ADC3_BASE_ADDRESS + 0x34)

//bits for ADC Registers
#define ADC_PRESCALAR_4 0x10000
#define ADC_SCAN 0x100
#define ADC_EOCS 0x400
#define ADC_CONT 0x2
#define ADC_DDS 0x200
#define ADC_DMA 0x100
#define ADC_1_CONVERSION  0
#define ADC_SMP_5_MX 0x38000
#define ADC3_CHANNEL_5 ((uint32_t)5)
#define ADC3_CHANNEL_6 ((uint32_t)6)
#define ADC3_CHANNEL_7 ((uint32_t)7)
#define ADC_SQ1 0
#define ADC_SQ2 5
#define ADC_SQ3 10
#define AD_ADON 0x1

//GLOBAL VARIABLES///////////////////////////////////////////////////
uint16_t checkPotVal = 0;

//FUNCTIONS/////////////////////////////////////////////////////////

//takes the ADC pot value, uses transfer function, then writes to duty cycle
//to drive the motor 
void writePotToARR(void)
{
    if (checkPotVal > 0)
    {
        //get current value of pot from DMA
        int j = 0;
        int i;
            for(i =0; i<100000000; i++){
        j=j+1;
        }
        uint32_t currVal = returnADC3StoredValue();
        //6000 is 3s offset and then 14000 would add 7s more for 10s total max
        uint32_t arrValue = (5400.0 + ((currVal)/3700.0)*12600.0); 
        //debugPrint(arrValue);
        setARR(arrValue);
    }
}

//function to call in state machine to turn on potentiometer monitoring
void turnOnPotCheck(void)
{
    checkPotVal = 1;
}

//function to call in state machine to turn on potentiometer monitoring
void turnOffPotCheck(void)
{
    checkPotVal = 0;
}

void initADC3_5_withDMA(void)
{
    //create pointer
    uint32_t * reg_pointer;
    //turn on ADC3 bus clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    //initialize GPIO F 7 as analog
    initGPIOF7AsAnalog();
    
    //call DMA functions
    initDMAForADC3_1channel();
    enableDMAForAdc3();
    
    //setup the clock preescalar
    reg_pointer = (uint32_t *)ADC_CCR;
    *reg_pointer = ADC_PRESCALAR_4;
    
    //configure ADC 12 bit resolution
    //End of conversion interrupt disabled
    //SCAN mode enabled to be able to scan a group of channels
    reg_pointer = (uint32_t *)ADC3_CR1;
    *reg_pointer = ADC_SCAN;
    
    //config ADC external trigger disabled, right data alignment, DMA, 
    //EOC is set at the end of each regular conversation, continuous converstaion enabled
    reg_pointer = (uint32_t *)ADC3_CR2;
    *reg_pointer = ADC_EOCS + ADC_CONT + ADC_DDS + ADC_DMA;
    
    //there will be one channel in the sequence of conversions
    reg_pointer = (uint32_t *)ADC3_SQR1;
    *reg_pointer = ADC_1_CONVERSION;
    
    //configure channel 5 to max sampling time (480 cycles)
    reg_pointer = (uint32_t *)ADC3_SMPR2;
    *reg_pointer = ADC_SMP_5_MX;
    
    //configure the seuqnece of conversion for teh ADC 5
    reg_pointer = (uint32_t *)ADC3_SQR3;
    *reg_pointer = (ADC3_CHANNEL_5<<ADC_SQ1);
    
    //enable the ADC3
    reg_pointer = (uint32_t *)ADC3_CR2;
    *reg_pointer = *reg_pointer | AD_ADON;
}


//start the process of converting for the ADC
void startACDConversion(void)
{
    //create pointer and point to SR register
    uint32_t * reg_pointer;
    reg_pointer = (uint32_t *)ADC3_SR;
    //clear the register
    *reg_pointer = 0;
    //pointer to CR2 register
    reg_pointer = (uint32_t *)ADC3_CR2;
    //set the start conversion bit to 1
    *reg_pointer = *reg_pointer | ADC3_SWSTART; 
}