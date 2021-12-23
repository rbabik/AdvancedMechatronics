#include "DMA.h"

//MACROS//////////////////////////////////

//Registers for DMA
#define DMA2_BASE_ADDRESS               0x40026400
#define DMA2_LISR_REGISTER              (DMA2_BASE_ADDRESS + 0x00)
#define DMA2_HISR_REGISTER              (DMA2_BASE_ADDRESS + 0x04)
#define DMA2_LIFCR_REGISTER             (DMA2_BASE_ADDRESS + 0x08)
#define DMA2_HIFCR_REGISTER             (DMA2_BASE_ADDRESS + 0x0C)
#define DMA2_S0CR_REGISTER              (DMA2_BASE_ADDRESS + 0x10)
#define DMA2_S0NDTR_REGISTER            (DMA2_BASE_ADDRESS + 0x14)
#define DMA2_S0PAR_REGISTER             (DMA2_BASE_ADDRESS + 0x18)
#define DMA2_S0M0AR_REGISTER            (DMA2_BASE_ADDRESS + 0x1C)
#define DMA2_S0M1AR_REGISTER            (DMA2_BASE_ADDRESS + 0x20)
#define DMA2_S0FCR_REGISTER             (DMA2_BASE_ADDRESS + 0x24)
#define ADC_BASE_ADDRESS 0x40012000
#define ADC3_BASE_ADDRESS (ADC_BASE_ADDRESS + 0x200)

#define DMA2_SxCR_CHANNEL_2_SELECT      (((uint32_t)2)<<25)
#define DMA2_SxCR_MSIZE_HALF_WORD       (((uint32_t)1)<<13)
#define DMA2_SxCR_PSIZE_HALF_WORD       (((uint32_t)1)<<11)
#define DMA2_SxCR_MINC_INCREMENT        (((uint32_t)1)<<10)
#define DMA2_SxCR_CIRC_ENABLE           (((uint32_t)1)<<8)  
#define DMA2_SxCR_DIR_PERTOMEM          0
#define DMA2_SxCR_STREAM_ENABLE         1
#define ADC3_DR (ADC3_BASE_ADDRESS + 0x4C)

//variable to store the ADC value
uint16_t adcDmaDataStorageBuffer;

//FUNCTIONS/////////////////////////////////

//function to set up the DMA for the ADC
void initDMAForADC3_1channel(void)
{
    //create pointer
    uint32_t * reg_pointer;
    
    //start the clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    
    //configure stream 0 to use channel 2 (ADC3)
    //point the pointer to the register
    reg_pointer = (uint32_t *)DMA2_S0CR_REGISTER;
    *reg_pointer = DMA2_SxCR_CHANNEL_2_SELECT + DMA2_SxCR_MSIZE_HALF_WORD 
    + DMA2_SxCR_PSIZE_HALF_WORD + DMA2_SxCR_MINC_INCREMENT 
    + DMA2_SxCR_DIR_PERTOMEM + DMA2_SxCR_CIRC_ENABLE;
    
    //Will transfer 1 data register for 1 channel of ADC
    reg_pointer = (uint32_t *)DMA2_S0NDTR_REGISTER;
    *reg_pointer = 1;
    
    //transfer from the ADC3 register
    reg_pointer = (uint32_t *)DMA2_S0PAR_REGISTER;
    *reg_pointer = ADC3_DR;
    
    //transfer to the storage buffer
    reg_pointer = (uint32_t *)DMA2_S0M0AR_REGISTER;
    *reg_pointer = (uint32_t)&adcDmaDataStorageBuffer;
}

void enableDMAForAdc3(void)
{
    //create pointer
    uint32_t * reg_pointer;
    //point to DMA2 S0CR register
    reg_pointer = (uint32_t *)DMA2_S0CR_REGISTER;
    *reg_pointer = *reg_pointer | DMA2_SxCR_STREAM_ENABLE;
}

//return single element from buffer
uint16_t returnADC3StoredValue(void)
{
    //create a slight delay 
   
    //return the stored value
    return adcDmaDataStorageBuffer;

}
