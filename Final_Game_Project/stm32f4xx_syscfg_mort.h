/**
  ******************************************************************************
  * @file    stm32f4xx_syscfg.h
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   This file contains all the functions prototypes for the SYSCFG_MORT firmware
  *          library. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_SYSCFG_H
#define __STM32F4xx_SYSCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"



/** @defgroup SYSCFG_EXTI_Port_Sources 
  * @{
  */ 
#define EXTI_PortSourceGPIOA_MORT       ((uint8_t)0x00)
#define EXTI_PortSourceGPIOB_MORT       ((uint8_t)0x01)
#define EXTI_PortSourceGPIOC_MORT       ((uint8_t)0x02)
#define EXTI_PortSourceGPIOD_MORT       ((uint8_t)0x03)
#define EXTI_PortSourceGPIOE_MORT       ((uint8_t)0x04)
#define EXTI_PortSourceGPIOF_MORT       ((uint8_t)0x05)
#define EXTI_PortSourceGPIOG_MORT       ((uint8_t)0x06)
#define EXTI_PortSourceGPIOH_MORT       ((uint8_t)0x07)
#define EXTI_PortSourceGPIOI_MORT       ((uint8_t)0x08)
#define EXTI_PortSourceGPIOJ_MORT       ((uint8_t)0x09)
#define EXTI_PortSourceGPIOK_MORT       ((uint8_t)0x0A)

#define IS_EXTI_PORT_SOURCE_MORT(PORTSOURCE) (((PORTSOURCE) == EXTI_PortSourceGPIOA_MORT) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOB_MORT) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOC_MORT) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOD_MORT) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOE_MORT) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOF_MORT) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOG_MORT) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOH_MORT) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOI_MORT) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOJ_MORT) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOK_MORT))
                                         
/**
  * @}
  */ 


/** @defgroup SYSCFG_EXTI_Pin_Sources 
  * @{
  */ 
#define EXTI_PinSource0_MORT            ((uint8_t)0x00)
#define EXTI_PinSource1_MORT            ((uint8_t)0x01)
#define EXTI_PinSource2_MORT            ((uint8_t)0x02)
#define EXTI_PinSource3_MORT            ((uint8_t)0x03)
#define EXTI_PinSource4_MORT            ((uint8_t)0x04)
#define EXTI_PinSource5_MORT            ((uint8_t)0x05)
#define EXTI_PinSource6_MORT            ((uint8_t)0x06)
#define EXTI_PinSource7_MORT            ((uint8_t)0x07)
#define EXTI_PinSource8_MORT            ((uint8_t)0x08)
#define EXTI_PinSource9_MORT            ((uint8_t)0x09)
#define EXTI_PinSource10_MORT           ((uint8_t)0x0A)
#define EXTI_PinSource11_MORT           ((uint8_t)0x0B)
#define EXTI_PinSource12_MORT           ((uint8_t)0x0C)
#define EXTI_PinSource13_MORT           ((uint8_t)0x0D)
#define EXTI_PinSource14_MORT           ((uint8_t)0x0E)
#define EXTI_PinSource15_MORT           ((uint8_t)0x0F)
#define IS_EXTI_PIN_SOURCE_MORT(PINSOURCE) (((PINSOURCE) == EXTI_PinSource0_MORT)  || \
                                       ((PINSOURCE) == EXTI_PinSource1_MORT)  || \
                                       ((PINSOURCE) == EXTI_PinSource2_MORT)  || \
                                       ((PINSOURCE) == EXTI_PinSource3_MORT)  || \
                                       ((PINSOURCE) == EXTI_PinSource4_MORT)  || \
                                       ((PINSOURCE) == EXTI_PinSource5_MORT)  || \
                                       ((PINSOURCE) == EXTI_PinSource6_MORT)  || \
                                       ((PINSOURCE) == EXTI_PinSource7_MORT)  || \
                                       ((PINSOURCE) == EXTI_PinSource8_MORT)  || \
                                       ((PINSOURCE) == EXTI_PinSource9_MORT)  || \
                                       ((PINSOURCE) == EXTI_PinSource10_MORT) || \
                                       ((PINSOURCE) == EXTI_PinSource11_MORT) || \
                                       ((PINSOURCE) == EXTI_PinSource12_MORT) || \
                                       ((PINSOURCE) == EXTI_PinSource13_MORT) || \
                                       ((PINSOURCE) == EXTI_PinSource14_MORT) || \
                                       ((PINSOURCE) == EXTI_PinSource15_MORT))
/**
  * @}
  */ 





/** @defgroup SYSCFG_ETHERNET_Media_Interface 
  * @{
  */ 
#define SYSCFG_ETH_MediaInterface_MII_MORT    ((uint32_t)0x00000000)
#define SYSCFG_ETH_MediaInterface_RMII_MORT   ((uint32_t)0x00000001)

#define IS_SYSCFG_ETH_MEDIA_INTERFACE_MORT(INTERFACE) (((INTERFACE) == SYSCFG_ETH_MediaInterface_MII_MORT) || \
                                                 ((INTERFACE) == SYSCFG_ETH_MediaInterface_RMII_MORT))
/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
 
void       SYSCFG_DeInit_mort(void);

void       SYSCFG_EXTILineConfig_mort(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
void       SYSCFG_ETH_MediaInterfaceConfig_mort(uint32_t SYSCFG_ETH_MediaInterface); 
void       SYSCFG_CompensationCellCmd_mort(FunctionalState NewState); 
FlagStatus SYSCFG_GetCompensationCellStatus_mort(void);


#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_SYSCFG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/






