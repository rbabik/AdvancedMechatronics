/**
  ******************************************************************************
  * @file    stm32f4xx_exti_mort.h
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   This file contains all the functions prototypes for the EXTI_MORT firmware
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
#ifndef __STM32F4xx_EXTI_MORT_H
#define __STM32F4xx_EXTI_MORT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup EXTI_MORT
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  EXTI_MORT mode enumeration  
  */

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef_mort;

#define IS_EXTI_MODE_MORT(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))

/** 
  * @brief  EXTI_MORT Trigger enumeration  
  */

typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef_mort;

#define IS_EXTI_TRIGGER_MORT(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) || \
                                  ((TRIGGER) == EXTI_Trigger_Falling) || \
                                  ((TRIGGER) == EXTI_Trigger_Rising_Falling))
/** 
  * @brief  EXTI_MORT Init Structure definition  
  */

typedef struct
{
  uint32_t EXTI_Line;               /*!< Specifies the EXTI_MORT lines to be enabled or disabled.
                                         This parameter can be any combination value of @ref EXTI_Lines */
   
  EXTIMode_TypeDef_mort EXTI_Mode;       /*!< Specifies the mode for the EXTI_MORT lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef_mort */

  EXTITrigger_TypeDef_mort EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI_MORT lines.
                                         This parameter can be a value of @ref EXTITrigger_TypeDef_mort */

  FunctionalState EXTI_LineCmd;     /*!< Specifies the new state of the selected EXTI_MORT lines.
                                         This parameter can be set either to ENABLE or DISABLE */ 
}EXTI_InitTypeDef_mort;

/* Exported constants --------------------------------------------------------*/

/** @defgroup EXTI_Exported_Constants
  * @{
  */

/** @defgroup EXTI_Lines 
  * @{
  */

#define EXTI_Line0_MORT       ((uint32_t)0x00001)     /*!< External interrupt line 0 */
#define EXTI_Line1_MORT       ((uint32_t)0x00002)     /*!< External interrupt line 1 */
#define EXTI_Line2_MORT       ((uint32_t)0x00004)     /*!< External interrupt line 2 */
#define EXTI_Line3_MORT       ((uint32_t)0x00008)     /*!< External interrupt line 3 */
#define EXTI_Line4_MORT       ((uint32_t)0x00010)     /*!< External interrupt line 4 */
#define EXTI_Line5_MORT       ((uint32_t)0x00020)     /*!< External interrupt line 5 */
#define EXTI_Line6_MORT       ((uint32_t)0x00040)     /*!< External interrupt line 6 */
#define EXTI_Line7_MORT       ((uint32_t)0x00080)     /*!< External interrupt line 7 */
#define EXTI_Line8_MORT       ((uint32_t)0x00100)     /*!< External interrupt line 8 */
#define EXTI_Line9_MORT       ((uint32_t)0x00200)     /*!< External interrupt line 9 */
#define EXTI_Line10_MORT      ((uint32_t)0x00400)     /*!< External interrupt line 10 */
#define EXTI_Line11_MORT      ((uint32_t)0x00800)     /*!< External interrupt line 11 */
#define EXTI_Line12_MORT      ((uint32_t)0x01000)     /*!< External interrupt line 12 */
#define EXTI_Line13_MORT      ((uint32_t)0x02000)     /*!< External interrupt line 13 */
#define EXTI_Line14_MORT      ((uint32_t)0x04000)     /*!< External interrupt line 14 */
#define EXTI_Line15_MORT      ((uint32_t)0x08000)     /*!< External interrupt line 15 */
#define EXTI_Line16_MORT      ((uint32_t)0x10000)     /*!< External interrupt line 16 Connected to the PVD Output */
#define EXTI_Line17_MORT      ((uint32_t)0x20000)     /*!< External interrupt line 17 Connected to the RTC Alarm event */
#define EXTI_Line18_MORT      ((uint32_t)0x40000)     /*!< External interrupt line 18 Connected to the USB OTG FS Wakeup from suspend event */                                    
#define EXTI_Line19_MORT      ((uint32_t)0x80000)     /*!< External interrupt line 19 Connected to the Ethernet Wakeup event */
#define EXTI_Line20_MORT      ((uint32_t)0x00100000)  /*!< External interrupt line 20 Connected to the USB OTG HS (configured in FS) Wakeup event  */
#define EXTI_Line21_MORT      ((uint32_t)0x00200000)  /*!< External interrupt line 21 Connected to the RTC Tamper and Time Stamp events */                                               
#define EXTI_Line22_MORT      ((uint32_t)0x00400000)  /*!< External interrupt line 22 Connected to the RTC Wakeup event */
#define EXTI_Line23_MORT      ((uint32_t)0x00800000)  /*!< External interrupt line 23 Connected to the LPTIM Wakeup event */

                                          
#define IS_EXTI_LINE_MORT(LINE) ((((LINE) & (uint32_t)0xFF800000) == 0x00) && ((LINE) != (uint16_t)0x00))

#define IS_GET_EXTI_LINE_MORT(LINE) (((LINE) == EXTI_Line0_MORT) || ((LINE) == EXTI_Line1_MORT) || \
                                ((LINE) == EXTI_Line2_MORT) || ((LINE) == EXTI_Line3_MORT) || \
                                ((LINE) == EXTI_Line4_MORT) || ((LINE) == EXTI_Line5_MORT) || \
                                ((LINE) == EXTI_Line6_MORT) || ((LINE) == EXTI_Line7_MORT) || \
                                ((LINE) == EXTI_Line8_MORT) || ((LINE) == EXTI_Line9_MORT) || \
                                ((LINE) == EXTI_Line10_MORT) || ((LINE) == EXTI_Line11_MORT) || \
                                ((LINE) == EXTI_Line12_MORT) || ((LINE) == EXTI_Line13_MORT) || \
                                ((LINE) == EXTI_Line14_MORT) || ((LINE) == EXTI_Line15_MORT) || \
                                ((LINE) == EXTI_Line16_MORT) || ((LINE) == EXTI_Line17_MORT) || \
                                ((LINE) == EXTI_Line18_MORT) || ((LINE) == EXTI_Line19_MORT) || \
                                ((LINE) == EXTI_Line20_MORT) || ((LINE) == EXTI_Line21_MORT) ||\
                                ((LINE) == EXTI_Line22_MORT) || ((LINE) == EXTI_Line23_MORT))
                    
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  Function used to set the EXTI_MORT configuration to the default reset state *****/
void EXTI_DeInit_mort(void);

/* Initialization and Configuration functions *********************************/
void EXTI_Init_mort(EXTI_InitTypeDef_mort* EXTI_InitStruct);
void EXTI_StructInit_mort(EXTI_InitTypeDef_mort* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt_mort(uint32_t EXTI_Line);

/* Interrupts and flags management functions **********************************/
FlagStatus EXTI_GetFlagStatus_mort(uint32_t EXTI_Line);
void EXTI_ClearFlag_mort(uint32_t EXTI_Line);
ITStatus EXTI_GetITStatus_mort(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit_mort(uint32_t EXTI_Line);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_EXTI_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/






