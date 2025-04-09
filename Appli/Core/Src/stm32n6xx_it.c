/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32n6xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32n6xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmw_camera.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern DCMIPP_HandleTypeDef hcamera_dcmipp;
extern LTDC_HandleTypeDef  hlcd_ltdc;
extern DMA2D_HandleTypeDef hlcd_dma2d;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA2D_HandleTypeDef hdma2d;
extern GPU2D_HandleTypeDef hgpu2d;
extern DMA_HandleTypeDef handle_HPDMA1_Channel1;
extern DMA_HandleTypeDef handle_HPDMA1_Channel0;
extern JPEG_HandleTypeDef hjpeg;
extern LTDC_HandleTypeDef hltdc;
extern TIM_HandleTypeDef htim2;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */
  
  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Secure fault.
  */
void SecureFault_Handler(void)
{
  /* USER CODE BEGIN SecureFault_IRQn 0 */

  /* USER CODE END SecureFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SecureFault_IRQn 0 */
    /* USER CODE END W1_SecureFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32N6xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32n6xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI Line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(TP_IRQ_Pin);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles DMA2D global interrupt.
  */
void DMA2D_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2D_IRQn 0 */

  /* USER CODE END DMA2D_IRQn 0 */
  HAL_DMA2D_IRQHandler(&hdma2d);
  /* USER CODE BEGIN DMA2D_IRQn 1 */

  /* USER CODE END DMA2D_IRQn 1 */
}

/**
  * @brief This function handles JPEG global interrupt.
  */
void JPEG_IRQHandler(void)
{
  /* USER CODE BEGIN JPEG_IRQn 0 */

  /* USER CODE END JPEG_IRQn 0 */
  HAL_JPEG_IRQHandler(&hjpeg);
  /* USER CODE BEGIN JPEG_IRQn 1 */

  /* USER CODE END JPEG_IRQn 1 */
}

/**
  * @brief This function handles GPU2D global interrupt.
  */
void GPU2D_IRQHandler(void)
{
  /* USER CODE BEGIN GPU2D_IRQn 0 */

  /* USER CODE END GPU2D_IRQn 0 */
  HAL_GPU2D_IRQHandler(&hgpu2d);
  /* USER CODE BEGIN GPU2D_IRQn 1 */

  /* USER CODE END GPU2D_IRQn 1 */
}

/**
  * @brief This function handles GPU2D Error interrupt.
  */
void GPU2D_ER_IRQHandler(void)
{
  /* USER CODE BEGIN GPU2D_ER_IRQn 0 */

  /* USER CODE END GPU2D_ER_IRQn 0 */
  HAL_GPU2D_ER_IRQHandler(&hgpu2d);
  /* USER CODE BEGIN GPU2D_ER_IRQn 1 */

  /* USER CODE END GPU2D_ER_IRQn 1 */
}

/**
  * @brief This function handles GPU2D cache interrupt.
  */
void ICACHE_IRQHandler(void)
{
  /* USER CODE BEGIN ICACHE_IRQn 0 */

  /* USER CODE END ICACHE_IRQn 0 */
  HAL_ICACHE_IRQHandler();
  /* USER CODE BEGIN ICACHE_IRQn 1 */

  /* USER CODE END ICACHE_IRQn 1 */
}

/**
  * @brief This function handles HPDMA1 Channel 0 global interrupt.
  */
void HPDMA1_Channel0_IRQHandler(void)
{
  /* USER CODE BEGIN HPDMA1_Channel0_IRQn 0 */

  /* USER CODE END HPDMA1_Channel0_IRQn 0 */
  HAL_DMA_IRQHandler(&handle_HPDMA1_Channel0);
  /* USER CODE BEGIN HPDMA1_Channel0_IRQn 1 */

  /* USER CODE END HPDMA1_Channel0_IRQn 1 */
}

/**
  * @brief This function handles HPDMA1 Channel 1 global interrupt.
  */
void HPDMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN HPDMA1_Channel1_IRQn 0 */

  /* USER CODE END HPDMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&handle_HPDMA1_Channel1);
  /* USER CODE BEGIN HPDMA1_Channel1_IRQn 1 */

  /* USER CODE END HPDMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles LTDC global interrupt.
  */
void LTDC_UP_IRQHandler(void)
{
  /* USER CODE BEGIN LTDC_UP_IRQn 0 */

  /* USER CODE END LTDC_UP_IRQn 0 */
  HAL_LTDC_IRQHandler(&hltdc);
  /* USER CODE BEGIN LTDC_UP_IRQn 1 */

  /* USER CODE END LTDC_UP_IRQn 1 */
}

/**
  * @brief This function handles LTDC error interrupt.
  */
void LTDC_UP_ERR_IRQHandler(void)
{
  /* USER CODE BEGIN LTDC_UP_ERR_IRQn 0 */

  /* USER CODE END LTDC_UP_ERR_IRQn 0 */
  HAL_LTDC_IRQHandler(&hltdc);
  /* USER CODE BEGIN LTDC_UP_ERR_IRQn 1 */

  /* USER CODE END LTDC_UP_ERR_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void SVC_Handler(void)
{
}

// void SysTick_Handler(void)
// {
//   HAL_IncTick();
// }

void CSI_IRQHandler(void)
{
  DCMIPP_HandleTypeDef *hcamera_dcmipp = CMW_CAMERA_GetDCMIPPHandle();
  HAL_DCMIPP_CSI_IRQHandler(hcamera_dcmipp);
}

void DCMIPP_IRQHandler(void)
{
  DCMIPP_HandleTypeDef *hcamera_dcmipp = CMW_CAMERA_GetDCMIPPHandle();
  HAL_DCMIPP_IRQHandler(hcamera_dcmipp);
}
/* USER CODE END 1 */
