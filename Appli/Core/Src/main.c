/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "app_threadx.h"
#include "main.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CACHEAXI_HandleTypeDef hcacheaxi;

CRC_HandleTypeDef hcrc;

DCMIPP_HandleTypeDef hdcmipp;

DMA2D_HandleTypeDef hdma2d;

GPU2D_HandleTypeDef hgpu2d;

I2C_HandleTypeDef hi2c2;

JPEG_HandleTypeDef hjpeg;
DMA_HandleTypeDef handle_HPDMA1_Channel1;
DMA_HandleTypeDef handle_HPDMA1_Channel0;

LTDC_HandleTypeDef hltdc;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_HPDMA1_Init(void);
static void MX_JPEG_Init(void);
static void MX_DMA2D_Init(void);
static void MX_GPU2D_Init(void);
static void MX_I2C2_Init(void);
static void MX_ICACHE_Init(void);
static void MX_LTDC_Init(void);
static void MX_CRC_Init(void);
static void MX_CSI_Init(void);
static void MX_DCMIPP_Init(void);
static void MX_CACHEAXI_Init(void);
static void SystemIsolation_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void set_clk_sleep_mode(void)
{
  /*** Enable sleep mode support during NPU inference *************************/
  /* Configure peripheral clocks to remain active during sleep mode */
  /* Keep all IP's enabled during WFE so they can wake up CPU. Fine tune
   * this if you want to save maximum power
   */
  __HAL_RCC_XSPI1_CLK_SLEEP_ENABLE();    /* For display frame buffer */
  __HAL_RCC_XSPI2_CLK_SLEEP_ENABLE();    /* For NN weights */
  __HAL_RCC_NPU_CLK_SLEEP_ENABLE();      /* For NN inference */
  __HAL_RCC_CACHEAXI_CLK_SLEEP_ENABLE(); /* For NN inference */
  __HAL_RCC_LTDC_CLK_SLEEP_ENABLE();     /* For display */
  __HAL_RCC_DMA2D_CLK_SLEEP_ENABLE();    /* For display */
  __HAL_RCC_DCMIPP_CLK_SLEEP_ENABLE();   /* For camera configuration retention */
  __HAL_RCC_CSI_CLK_SLEEP_ENABLE();      /* For camera configuration retention */

  __HAL_RCC_FLEXRAM_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM1_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM2_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM3_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM4_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM5_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM6_MEM_CLK_SLEEP_ENABLE(); 

}

static void IAC_Config(void)
{
/* Configure IAC to trap illegal access events */
  __HAL_RCC_IAC_CLK_ENABLE();
  __HAL_RCC_IAC_FORCE_RESET();
  __HAL_RCC_IAC_RELEASE_RESET();
}
/* USER CODE END 0 */

static void Reset_Peripherals(void)
{
  __HAL_RCC_JPEG_FORCE_RESET();
  __HAL_RCC_DMA2D_FORCE_RESET();
  __HAL_RCC_GPU2D_FORCE_RESET();
  __HAL_RCC_LTDC_FORCE_RESET();
  __HAL_RCC_DCMIPP_FORCE_RESET();
  __HAL_RCC_CSI_FORCE_RESET();
  __HAL_RCC_I2C2_FORCE_RESET();
  __HAL_RCC_CACHEAXI_FORCE_RESET();
  __HAL_RCC_CRC_FORCE_RESET();
  __HAL_RCC_HPDMA1_FORCE_RESET();
  __HAL_RCC_GPIOA_FORCE_RESET();
  __HAL_RCC_GPIOB_FORCE_RESET();
  __HAL_RCC_GPIOC_FORCE_RESET();
  __HAL_RCC_GPIOD_FORCE_RESET();
  __HAL_RCC_GPIOE_FORCE_RESET();
  __HAL_RCC_GPIOF_FORCE_RESET();
  __HAL_RCC_GPIOG_FORCE_RESET();
  __HAL_RCC_GPIOH_FORCE_RESET();
  __HAL_RCC_GPIOO_FORCE_RESET();
  __HAL_RCC_GPIOQ_FORCE_RESET();

  // Optional small delay
  HAL_Delay(1);

  __HAL_RCC_JPEG_RELEASE_RESET();
  __HAL_RCC_DMA2D_RELEASE_RESET();
  __HAL_RCC_GPU2D_RELEASE_RESET();
  __HAL_RCC_LTDC_RELEASE_RESET();
  __HAL_RCC_DCMIPP_RELEASE_RESET();
  __HAL_RCC_CSI_RELEASE_RESET();
  __HAL_RCC_I2C2_RELEASE_RESET();
  __HAL_RCC_CACHEAXI_RELEASE_RESET();
  __HAL_RCC_CRC_RELEASE_RESET();
  __HAL_RCC_HPDMA1_RELEASE_RESET();
  __HAL_RCC_GPIOA_RELEASE_RESET();
  __HAL_RCC_GPIOB_RELEASE_RESET();
  __HAL_RCC_GPIOC_RELEASE_RESET();
  __HAL_RCC_GPIOD_RELEASE_RESET();
  __HAL_RCC_GPIOE_RELEASE_RESET();
  __HAL_RCC_GPIOF_RELEASE_RESET();
  __HAL_RCC_GPIOG_RELEASE_RESET();
  __HAL_RCC_GPIOH_RELEASE_RESET();
  __HAL_RCC_GPIOO_RELEASE_RESET();
  __HAL_RCC_GPIOQ_RELEASE_RESET();
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  //Reset_Peripherals();
  /* USER CODE BEGIN 1 */
  __HAL_RCC_NPU_CLK_ENABLE();
  __HAL_RCC_NPU_FORCE_RESET();
  __HAL_RCC_NPU_RELEASE_RESET();
  //Enable NPU internal RAM (4x448KB)
  LL_MEM_EnableClock(LL_MEM_AXISRAM3);
  LL_MEM_EnableClock(LL_MEM_AXISRAM4);
  LL_MEM_EnableClock(LL_MEM_AXISRAM5);
  LL_MEM_EnableClock(LL_MEM_AXISRAM6);
  
  RCC->MEMENR |= RCC_MEMENR_AXISRAM3EN | RCC_MEMENR_AXISRAM4EN | RCC_MEMENR_AXISRAM5EN | RCC_MEMENR_AXISRAM6EN;
  *((uint32_t *) (RAMCFG_BASE_S + 0x080 + 0x80 * (3 - 2))) = 0x0; // AXISRAM3 memory is powered  
  *((uint32_t *) (RAMCFG_BASE_S + 0x080 + 0x80 * (4 - 2))) = 0x0; // AXISRAM4 memory is powered  
  *((uint32_t *) (RAMCFG_BASE_S + 0x080 + 0x80 * (5 - 2))) = 0x0; // AXISRAM5 memory is powered  
  *((uint32_t *) (RAMCFG_BASE_S + 0x080 + 0x80 * (6 - 2))) = 0x0; // AXISRAM6 memory is powered
  
  // loop that can be used to catch the application for debug.Set mini to 1, build and flash target as normally.
  // Set BOOT1 switch to the left position, press reset without removing cable.
  // Use the Connect to running debug config to connect, then change mini value from watch.
  // For breakpoints to work they seem to need to be manually changed to ahrdware breakpoint
  static volatile int debugFlag = 0;
  while (debugFlag == 1)
  {
    __NOP();
  }
  /* USER CODE END 1 */

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Update SystemCoreClock variable according to RCC registers values. */
  SystemCoreClockUpdate();

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Update SystemCoreClock variable */
  SystemCoreClockUpdate();

  /* USER CODE BEGIN SysInit */
  // Enable clock f\or CRC init
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_HPDMA1_Init();
  MX_JPEG_Init();
  MX_DMA2D_Init();
  MX_GPU2D_Init();
  MX_I2C2_Init();
  MX_ICACHE_Init();
  MX_LTDC_Init();
  MX_CRC_Init();
  MX_CACHEAXI_Init();
  SystemIsolation_Config();
  /* Call PreOsInit function */
  MX_TouchGFX_PreOSInit();
  /* USER CODE BEGIN 2 */
  IAC_Config();
  set_clk_sleep_mode();
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_RED);
  /* USER CODE END 2 */

  MX_ThreadX_Init();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief CACHEAXI Initialization Function
  * @param None
  * @retval None
  */
static void MX_CACHEAXI_Init(void)
{

  /* USER CODE BEGIN CACHEAXI_Init 0 */

  /* USER CODE END CACHEAXI_Init 0 */

  /* USER CODE BEGIN CACHEAXI_Init 1 */

  /* USER CODE END CACHEAXI_Init 1 */
  npu_cache_init();
  npu_cache_enable();
  /* USER CODE END CACHEAXI_Init 2 */
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief CSI Initialization Function
  * @param None
  * @retval None
  */
static void MX_CSI_Init(void)
{

  /* USER CODE BEGIN CSI_Init 0 */

  /* USER CODE END CSI_Init 0 */

  /* USER CODE BEGIN CSI_Init 1 */

  /* USER CODE END CSI_Init 1 */
  /* USER CODE BEGIN CSI_Init 2 */

  /* USER CODE END CSI_Init 2 */

}

/**
  * @brief DCMIPP Initialization Function
  * @param None
  * @retval None
  */
static void MX_DCMIPP_Init(void)
{

  /* USER CODE BEGIN DCMIPP_Init 0 */

  /* USER CODE END DCMIPP_Init 0 */

  // DCMIPP_PipeConfTypeDef pPipeConfig = {0};

  /* USER CODE BEGIN DCMIPP_Init 1 */

  /* USER CODE END DCMIPP_Init 1 */
  // hdcmipp.Instance = DCMIPP;

  // if (HAL_DCMIPP_Init(&hdcmipp) != HAL_OK)
  // {
  //   Error_Handler();
  // }

  // /** Pipe 1 Config
  // */
  // pPipeConfig.FrameRate = DCMIPP_FRAME_RATE_ALL;
  // pPipeConfig.PixelPipePitch = 10;
  // pPipeConfig.PixelPackerFormat = DCMIPP_PIXEL_PACKER_FORMAT_RGB888_YUV444_1;
  // if (HAL_DCMIPP_PIPE_SetConfig(&hdcmipp, DCMIPP_PIPE1, &pPipeConfig) != HAL_OK)
  // {
  //   Error_Handler();
  // }
  /* USER CODE BEGIN DCMIPP_Init 2 */

  /* USER CODE END DCMIPP_Init 2 */

}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief GPU2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPU2D_Init(void)
{

  /* USER CODE BEGIN GPU2D_Init 0 */

  /* USER CODE END GPU2D_Init 0 */

  /* USER CODE BEGIN GPU2D_Init 1 */

  /* USER CODE END GPU2D_Init 1 */
  hgpu2d.Instance = GPU2D;
  if (HAL_GPU2D_Init(&hgpu2d) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN GPU2D_Init 2 */

  /* USER CODE END GPU2D_Init 2 */

}

/**
  * @brief HPDMA1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_HPDMA1_Init(void)
{

  /* USER CODE BEGIN HPDMA1_Init 0 */

  /* USER CODE END HPDMA1_Init 0 */

  /* Peripheral clock enable */
  __HAL_RCC_HPDMA1_CLK_ENABLE();

  /* HPDMA1 interrupt Init */
    HAL_NVIC_SetPriority(HPDMA1_Channel0_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(HPDMA1_Channel0_IRQn);
    HAL_NVIC_SetPriority(HPDMA1_Channel1_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(HPDMA1_Channel1_IRQn);

  /* USER CODE BEGIN HPDMA1_Init 1 */

  /* USER CODE END HPDMA1_Init 1 */
  /* USER CODE BEGIN HPDMA1_Init 2 */

  /* USER CODE END HPDMA1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x109035B7;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
static void MX_ICACHE_Init(void)
{

  /* USER CODE BEGIN ICACHE_Init 0 */

  /* USER CODE END ICACHE_Init 0 */

  /* USER CODE BEGIN ICACHE_Init 1 */

  /* USER CODE END ICACHE_Init 1 */

  /** Enable instruction cache (default 2-ways set associative cache)
  */
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

/**
  * @brief JPEG Initialization Function
  * @param None
  * @retval None
  */
static void MX_JPEG_Init(void)
{

  /* USER CODE BEGIN JPEG_Init 0 */

  /* USER CODE END JPEG_Init 0 */

  /* USER CODE BEGIN JPEG_Init 1 */

  /* USER CODE END JPEG_Init 1 */
  hjpeg.Instance = JPEG;
  if (HAL_JPEG_Init(&hjpeg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN JPEG_Init 2 */

  /* USER CODE END JPEG_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 4;
  hltdc.Init.VerticalSync = 4;
  hltdc.Init.AccumulatedHBP = 12;
  hltdc.Init.AccumulatedVBP = 12;
  hltdc.Init.AccumulatedActiveW = 812;
  hltdc.Init.AccumulatedActiveH = 492;
  hltdc.Init.TotalWidth = 820;
  hltdc.Init.TotalHeigh = 506;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 800;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 480;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0;
  pLayerCfg.ImageWidth = 800;
  pLayerCfg.ImageHeight = 480;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief RIF Initialization Function
  * @param None
  * @retval None
  */
  static void SystemIsolation_Config(void)
{

  /* USER CODE BEGIN RIF_Init 0 */

  /* USER CODE END RIF_Init 0 */

  /* set all required IPs as secure privileged */
  __HAL_RCC_RIFSC_CLK_ENABLE();
  RIMC_MasterConfig_t RIMC_master = {0};
  RIMC_master.MasterCID = RIF_CID_1;
  RIMC_master.SecPriv = RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV;

  /*RIMC configuration*/
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_DCMIPP, &RIMC_master);
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_DMA2D, &RIMC_master);
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_GPU2D, &RIMC_master);
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_LTDC1, &RIMC_master);
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_NPU, &RIMC_master);

  /*RISUP configuration*/
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_CRC , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_DMA2D , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_GPU2D , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_I2C2 , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_ICACHE , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_JPEG , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_LTDC , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_LTDCL1 , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_TIM2 , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_XSPI1 , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_XSPI2 , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);

  /* RIF-Aware IPs Config */

  /* set up PWR configuration */
  HAL_PWR_ConfigAttributes(PWR_ITEM_WKUP1,PWR_SEC_NPRIV);

  /* set up HPDMA configuration */
  /* set HPDMA1 channel 0 */
  if (HAL_DMA_ConfigChannelAttributes(&handle_HPDMA1_Channel0,DMA_CHANNEL_SEC|DMA_CHANNEL_PRIV)!= HAL_OK )
  {
    Error_Handler();
  }
  /* set HPDMA1 channel 1 */
  if (HAL_DMA_ConfigChannelAttributes(&handle_HPDMA1_Channel1,DMA_CHANNEL_SEC|DMA_CHANNEL_PRIV)!= HAL_OK )
  {
    Error_Handler();
  }

  /* set up GPIO configuration */
  HAL_GPIO_ConfigPinAttributes(GPIOC,GPIO_PIN_13,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOD,GPIO_PIN_0,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOD,GPIO_PIN_4,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOD,GPIO_PIN_5,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOD,GPIO_PIN_14,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOE,GPIO_PIN_0,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOE,GPIO_PIN_1,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOE,GPIO_PIN_9,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOF,GPIO_PIN_4,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOF,GPIO_PIN_6,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOG,GPIO_PIN_10,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOO,GPIO_PIN_1,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOQ,GPIO_PIN_3,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOQ,GPIO_PIN_4,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOQ,GPIO_PIN_6,GPIO_PIN_SEC|GPIO_PIN_NPRIV);

  /* USER CODE BEGIN RIF_Init 1 */
  // HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_DCMIPP, &RIMC_master);
  // HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_LTDC2 , &RIMC_master);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_NPU , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_DCMIPP , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_CSI    , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_LTDCL2 , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  /* USER CODE END RIF_Init 1 */
  /* USER CODE BEGIN RIF_Init 2 */
  /* USER CODE END RIF_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOQ_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOO_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MCU_ACTIVE_GPIO_Port, MCU_ACTIVE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_ON_OFF_GPIO_Port, LCD_ON_OFF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, FRAME_RATE_Pin|RENDER_TIME_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(VSYNC_FREQ_GPIO_Port, VSYNC_FREQ_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD_BL_Pin LCD_ON_OFF_Pin */
  GPIO_InitStruct.Pin = LCD_BL_Pin|LCD_ON_OFF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOQ, &GPIO_InitStruct);

  /*Configure GPIO pins : MCU_ACTIVE_Pin LCD_RESET_Pin */
  GPIO_InitStruct.Pin = MCU_ACTIVE_Pin|LCD_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : TP_IRQ_Pin */
  GPIO_InitStruct.Pin = TP_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TP_IRQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : FRAME_RATE_Pin RENDER_TIME_Pin */
  GPIO_InitStruct.Pin = FRAME_RATE_Pin|RENDER_TIME_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : USER_BUTTON_1_Pin */
  GPIO_InitStruct.Pin = USER_BUTTON_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(USER_BUTTON_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TAMP_BUTTON_Pin */
  GPIO_InitStruct.Pin = TAMP_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(TAMP_BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : VSYNC_FREQ_Pin */
  GPIO_InitStruct.Pin = VSYNC_FREQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(VSYNC_FREQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_RED_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_RED_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};
  MPU_Attributes_InitTypeDef MPU_AttributesInit = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region 0 and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x34100000;
  MPU_InitStruct.LimitAddress = 0x34248FFF;
  MPU_InitStruct.AttributesIndex = MPU_ATTRIBUTES_NUMBER0;
  MPU_InitStruct.AccessPermission = MPU_REGION_ALL_RW;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  MPU_AttributesInit.Number = MPU_ATTRIBUTES_NUMBER0;
  MPU_AttributesInit.Attributes = MPU_DEVICE_GRE;

  HAL_MPU_ConfigMemoryAttributes(&MPU_AttributesInit);

  /** Initializes and configures the Region 1 and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.BaseAddress = 0x34249000;
  MPU_InitStruct.LimitAddress = 0x343BFFFF;
  MPU_InitStruct.AttributesIndex = MPU_ATTRIBUTES_NUMBER1;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  MPU_AttributesInit.Number = MPU_ATTRIBUTES_NUMBER1;
  MPU_AttributesInit.Attributes = MPU_DEVICE_NGNRNE;

  HAL_MPU_ConfigMemoryAttributes(&MPU_AttributesInit);

  /** Initializes and configures the Region 2 and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER2;
  MPU_InitStruct.BaseAddress = 0x70100400;
  MPU_InitStruct.LimitAddress = 0x701FFFFF;
  MPU_InitStruct.AttributesIndex = MPU_ATTRIBUTES_NUMBER2;
  MPU_InitStruct.AccessPermission = MPU_REGION_ALL_RO;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  MPU_AttributesInit.Number = MPU_ATTRIBUTES_NUMBER2;
  MPU_AttributesInit.Attributes = INNER_OUTER(MPU_WRITE_BACK|MPU_NON_TRANSIENT
                              |MPU_R_ALLOCATE);

  HAL_MPU_ConfigMemoryAttributes(&MPU_AttributesInit);

  /** Initializes and configures the Region 3 and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER3;
  MPU_InitStruct.BaseAddress = 0x70200000;
  MPU_InitStruct.LimitAddress = 0x73FFFFFF;
  MPU_InitStruct.AttributesIndex = MPU_ATTRIBUTES_NUMBER3;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  MPU_AttributesInit.Number = MPU_ATTRIBUTES_NUMBER3;
  MPU_AttributesInit.Attributes = INNER_OUTER(MPU_WRITE_BACK|MPU_TRANSIENT
                              |MPU_R_ALLOCATE);

  HAL_MPU_ConfigMemoryAttributes(&MPU_AttributesInit);

    /** Initializes and configures the Region 3 and the memory to be protected
  */
//   MPU_InitStruct.Number = MPU_REGION_NUMBER4;
//   MPU_InitStruct.BaseAddress = 0x90000000;
//   MPU_InitStruct.LimitAddress = 0x93FFFFFF;
//   MPU_InitStruct.AttributesIndex = MPU_ATTRIBUTES_NUMBER4;
//   MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

//   HAL_MPU_ConfigRegion(&MPU_InitStruct);
//   MPU_AttributesInit.Number = MPU_ATTRIBUTES_NUMBER4;
//   MPU_AttributesInit.Attributes = INNER_OUTER(MPU_WRITE_BACK|MPU_NON_TRANSIENT
//                               |MPU_RW_ALLOCATE);

//  HAL_MPU_ConfigMemoryAttributes(&MPU_AttributesInit);

  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
    BSP_LED_Toggle(LED_RED);
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
