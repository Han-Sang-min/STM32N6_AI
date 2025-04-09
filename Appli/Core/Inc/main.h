/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined ( __ICCARM__ )
#  define CMSE_NS_CALL  __cmse_nonsecure_call
#  define CMSE_NS_ENTRY __cmse_nonsecure_entry
#else
#  define CMSE_NS_CALL  __attribute((cmse_nonsecure_call))
#  define CMSE_NS_ENTRY __attribute((cmse_nonsecure_entry))
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32n6570_discovery.h"
#include "npu_cache.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* Function pointer declaration in non-secure*/
#if defined ( __ICCARM__ )
typedef void (CMSE_NS_CALL *funcptr)(void);
#else
typedef void CMSE_NS_CALL (*funcptr)(void);
#endif

/* typedef for non-secure callback functions */
typedef funcptr funcptr_NS;

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_BL_Pin GPIO_PIN_6
#define LCD_BL_GPIO_Port GPIOQ
#define MCU_ACTIVE_Pin GPIO_PIN_9
#define MCU_ACTIVE_GPIO_Port GPIOE
#define LCD_ON_OFF_Pin GPIO_PIN_3
#define LCD_ON_OFF_GPIO_Port GPIOQ
#define TP_IRQ_Pin GPIO_PIN_4
#define TP_IRQ_GPIO_Port GPIOQ
#define TP_IRQ_EXTI_IRQn EXTI4_IRQn
#define FRAME_RATE_Pin GPIO_PIN_0
#define FRAME_RATE_GPIO_Port GPIOD
#define RENDER_TIME_Pin GPIO_PIN_5
#define RENDER_TIME_GPIO_Port GPIOD
#define USER_BUTTON_1_Pin GPIO_PIN_13
#define USER_BUTTON_1_GPIO_Port GPIOC
#define TAMP_BUTTON_Pin GPIO_PIN_0
#define TAMP_BUTTON_GPIO_Port GPIOE
#define LCD_RESET_Pin GPIO_PIN_1
#define LCD_RESET_GPIO_Port GPIOE
#define LED_GREEN_Pin GPIO_PIN_1
#define LED_GREEN_GPIO_Port GPIOO
#define VSYNC_FREQ_Pin GPIO_PIN_6
#define VSYNC_FREQ_GPIO_Port GPIOF
#define LED_RED_Pin GPIO_PIN_10
#define LED_RED_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
