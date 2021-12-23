/**
  ******************************************************************************
  * @file    stm32f4xx_exti.c
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the EXTI_MORT peripheral:
  *           + Initialization and Configuration
  *           + Interrupts and flags management
  *
@verbatim  

 ===============================================================================
                              ##### EXTI_MORT features #####
 ===============================================================================

 [..] External interrupt/event lines are mapped as following:
   (#) All available GPIO pins are connected to the 16 external 
       interrupt/event lines from EXTI0 to EXTI15.
   (#) EXTI_MORT line 16 is connected to the PVD Output
   (#) EXTI_MORT line 17 is connected to the RTC Alarm event
   (#) EXTI_MORT line 18 is connected to the USB OTG FS Wakeup from suspend event
   (#) EXTI_MORT line 19 is connected to the Ethernet Wakeup event
   (#) EXTI_MORT line 20 is connected to the USB OTG HS (configured in FS) Wakeup event 
   (#) EXTI_MORT line 21 is connected to the RTC Tamper and Time Stamp events
   (#) EXTI_MORT line 22 is connected to the RTC Wakeup event
   (#) EXTI_MORT line 23 is connected to the LPTIM Wakeup event 

                       ##### How to use this driver #####
 ===============================================================================
 
 [..] In order to use an I/O pin as an external interrupt source, follow steps 
      below:
   (#) Configure the I/O in input mode using GPIO_Init()
   (#) Select the input source pin for the EXTI_MORT line using SYSCFG_EXTILineConfig()
   (#) Select the mode(interrupt, event) and configure the trigger 
       selection (Rising, falling or both) using EXTI_Init_mort()
   (#) Configure NVIC IRQ channel mapped to the EXTI_MORT line using NVIC_Init()

 [..]     
   (@) SYSCFG APB clock must be enabled to get write access to SYSCFG_EXTICRx
       registers using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

@endverbatim
  *
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_exti_mort.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup EXTI_MORT 
  * @brief EXTI_MORT driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define EXTI_LINENONE_MORT    ((uint32_t)0x00000)  /* No interrupt selected */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup EXTI_Private_Functions
  * @{
  */

/** @defgroup EXTI_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
             ##### Initialization and Configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the EXTI_MORT peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void EXTI_DeInit_mort(void)
{
  EXTI_MORT->IMR = 0x00000000;
  EXTI_MORT->EMR = 0x00000000;
  EXTI_MORT->RTSR = 0x00000000;
  EXTI_MORT->FTSR = 0x00000000;
  EXTI_MORT->PR = 0x007FFFFF;
}

/**
  * @brief  Initializes the EXTI_MORT peripheral according to the specified
  *         parameters in the EXTI_InitStruct.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef_mort structure
  *         that contains the configuration information for the EXTI_MORT peripheral.
  * @retval None
  */
void EXTI_Init_mort(EXTI_InitTypeDef_mort* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_EXTI_MODE_MORT(EXTI_InitStruct->EXTI_Mode));
  assert_param(IS_EXTI_TRIGGER_MORT(EXTI_InitStruct->EXTI_Trigger));
  assert_param(IS_EXTI_LINE_MORT(EXTI_InitStruct->EXTI_Line));  
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));

  tmp = (uint32_t)EXTI_BASE_MORT;
     
  if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
  {
    /* Clear EXTI_MORT line configuration */
    EXTI_MORT->IMR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI_MORT->EMR &= ~EXTI_InitStruct->EXTI_Line;
    
    tmp += EXTI_InitStruct->EXTI_Mode;

    *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;

    /* Clear Rising Falling edge configuration */
    EXTI_MORT->RTSR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI_MORT->FTSR &= ~EXTI_InitStruct->EXTI_Line;
    
    /* Select the trigger for the selected external interrupts */
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      /* Rising Falling edge */
      EXTI_MORT->RTSR |= EXTI_InitStruct->EXTI_Line;
      EXTI_MORT->FTSR |= EXTI_InitStruct->EXTI_Line;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE_MORT;
      tmp += EXTI_InitStruct->EXTI_Trigger;

      *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->EXTI_Mode;

    /* Disable the selected external lines */
    *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
  }
}

/**
  * @brief  Fills each EXTI_InitStruct member with its reset value.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef_mort structure which will
  *         be initialized.
  * @retval None
  */
void EXTI_StructInit_mort(EXTI_InitTypeDef_mort* EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_Line = EXTI_LINENONE_MORT;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
  * @brief  Generates a Software interrupt on selected EXTI_MORT line.
  * @param  EXTI_Line: specifies the EXTI_MORT line on which the software interrupt
  *         will be generated.
  *         This parameter can be any combination of EXTI_Linex where x can be (0..22)
  * @retval None
  */
void EXTI_GenerateSWInterrupt_mort(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE_MORT(EXTI_Line));
  
  EXTI_MORT->SWIER |= EXTI_Line;
}

/**
  * @}
  */

/** @defgroup EXTI_Group2 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim   
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified EXTI_MORT line flag is set or not.
  * @param  EXTI_Line: specifies the EXTI_MORT line flag to check.
  *          This parameter can be EXTI_Linex where x can be(0..22)
  * @retval The new state of EXTI_Line (SET or RESET).
  */
FlagStatus EXTI_GetFlagStatus_mort(uint32_t EXTI_Line)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE_MORT(EXTI_Line));
  
  if ((EXTI_MORT->PR & EXTI_Line) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the EXTI_MORT's line pending flags.
  * @param  EXTI_Line: specifies the EXTI_MORT lines flags to clear.
  *          This parameter can be any combination of EXTI_Linex where x can be (0..22)
  * @retval None
  */
void EXTI_ClearFlag_mort(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE_MORT(EXTI_Line));
  
  EXTI_MORT->PR = EXTI_Line;
}

/**
  * @brief  Checks whether the specified EXTI_MORT line is asserted or not.
  * @param  EXTI_Line: specifies the EXTI_MORT line to check.
  *          This parameter can be EXTI_Linex where x can be(0..22)
  * @retval The new state of EXTI_Line (SET or RESET).
  */
ITStatus EXTI_GetITStatus_mort(uint32_t EXTI_Line)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE_MORT(EXTI_Line));
  
  if ((EXTI_MORT->PR & EXTI_Line) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
  
}

/**
  * @brief  Clears the EXTI_MORT's line pending bits.
  * @param  EXTI_Line: specifies the EXTI_MORT lines to clear.
  *          This parameter can be any combination of EXTI_Linex where x can be (0..22)
  * @retval None
  */
void EXTI_ClearITPendingBit_mort(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE_MORT(EXTI_Line));
  
  EXTI_MORT->PR = EXTI_Line;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/






