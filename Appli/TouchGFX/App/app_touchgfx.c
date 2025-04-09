/**
  ******************************************************************************
  * File Name          : app_touchgfx.c
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.24.2. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tx_api.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/
#define TOUCHGFX_STACK_SIZE          (4080)

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
static TX_THREAD TouchGFXThread;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void touchgfx_init(void);
void touchgfx_components_init(void);
void touchgfx_taskEntry(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
 * PreOS Initialization function
 */
void MX_TouchGFX_PreOSInit(void)
{
    // Calling forward to touchgfx_init in C++ domain
    touchgfx_components_init();
    touchgfx_init();
}

/**
 * Create TouchGFX Thread
 */
UINT MX_TouchGFX_Init(VOID* memory_ptr)
{
    UINT ret = TX_SUCCESS;
    CHAR* pointer = 0;

    /* Allocate the stack for TouchGFX Thread.  */
    if (tx_byte_allocate((TX_BYTE_POOL*)memory_ptr, (VOID**) &pointer,
                         TOUCHGFX_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
        ret = TX_POOL_ERROR;
    }

    /* Create TouchGFX Thread */
    else if (tx_thread_create(&TouchGFXThread, (CHAR*)"TouchGFX", TouchGFX_Task, 0,
                              pointer, TOUCHGFX_STACK_SIZE,
                              5, 5,
                              TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
    {
        ret = TX_THREAD_ERROR;
    }

    return ret;
}

/**
 * TouchGFX application entry function
 */
void MX_TouchGFX_Process(void)
{
    // Calling forward to touchgfx_taskEntry in C++ domain
    touchgfx_taskEntry();
}

/**
 * TouchGFX application thread
 */
void TouchGFX_Task(unsigned long thread_input)
{
    // Calling forward to touchgfx_taskEntry in C++ domain
    touchgfx_taskEntry();
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
