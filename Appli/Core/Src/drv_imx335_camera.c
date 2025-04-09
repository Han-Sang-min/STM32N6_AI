#include "drv_imx335_camera.h"
#include "thread_helper_c.h"

static volatile int32_t cameraFrameReceived;

static void Configure_IC11_IC2(void);
static void DCMIPP_PipeInitDisplay(void);
static void DCMIPP_PipeInitNn(uint32_t *pitch);

void IMX335_Init_Camera(void) {
    Configure_IC11_IC2();
    int ret;
    CMW_CameraInit_t cam_conf;
  
    cam_conf.width = CAMERA_WIDTH;
    cam_conf.height = CAMERA_HEIGHT;
    cam_conf.fps = CAMERA_FPS;
    cam_conf.pixel_format = 0; /* Hardcoded as Raw Bayer Pattern 10(DCMIPP_DT_RAW10) */
    cam_conf.anti_flicker = 0;
    cam_conf.mirror_flip = CAMERA_FLIP;
    ret = CMW_CAMERA_Init(&cam_conf);
    assert(ret == CMW_ERROR_NONE);

    DCMIPP_PipeInitDisplay();
    uint32_t pitch_nn = 0;
    DCMIPP_PipeInitNn(&pitch_nn); /* Use pitch_nn if needed later */
}

static void DCMIPP_PipeInitDisplay(void) {
    CMW_DCMIPP_Conf_t dcmipp_conf;
    int ret;

    dcmipp_conf.output_width = FRAME_WIDTH;
    dcmipp_conf.output_height = FRAME_HEIGHT;
    dcmipp_conf.output_format = CAPTURE_FORMAT;
    dcmipp_conf.output_bpp = CAPTURE_BPP;
    dcmipp_conf.mode = CMW_Aspect_ratio_fullscreen;
    dcmipp_conf.enable_swap = 0;
    dcmipp_conf.enable_gamma_conversion = GAMMA_CONVERSION;
    uint32_t pitch;
    ret = CMW_CAMERA_SetPipeConfig(DCMIPP_PIPE1, &dcmipp_conf, &pitch);
    assert(ret == HAL_OK);
    if (dcmipp_conf.output_width*dcmipp_conf.output_bpp != pitch) {
        assert(0); /* not aligned to a 16-bit boundary */
    }
}

static void DCMIPP_PipeInitNn(uint32_t *pitch) {
    CMW_DCMIPP_Conf_t dcmipp_conf;
    int ret;

    dcmipp_conf.output_width = NN_WIDTH;
    dcmipp_conf.output_height = NN_HEIGHT;
    dcmipp_conf.output_format = DCMIPP_PIXEL_PACKER_FORMAT_RGB888_YUV444_1;
    dcmipp_conf.output_bpp = NN_BPP;
    dcmipp_conf.mode = CMW_Aspect_ratio_fit;
    dcmipp_conf.enable_swap = COLOR_RGB;
    dcmipp_conf.enable_gamma_conversion = GAMMA_CONVERSION;
    ret = CMW_CAMERA_SetPipeConfig(DCMIPP_PIPE2, &dcmipp_conf, pitch);
    assert(ret == HAL_OK);
}

void IMX335_StartCamera(uint32_t pipe, uint8_t *pbuff, uint32_t mode) {
    int ret;

    ret = CMW_CAMERA_Start(pipe, (void*)pbuff, mode);
    assert(ret == CMW_ERROR_NONE);
}

void IMX335_DoubleBufferStart(uint32_t pipe, uint8_t *pbuff1, uint8_t *pbuff2, uint32_t Mode)
{
    CMW_CAMERA_DoubleBufferStart(pipe, pbuff1, pbuff2, Mode);    
}

void IMX335_BackgroundProcess(void) {
    int ret;

    ret = CMW_CAMERA_Run();
    assert(ret == CMW_ERROR_NONE);
}

void IMX335_CAMERA_Resume(void) {
    CMW_CAMERA_Resume(DCMIPP_PIPE1);
}

void IMX335_CAMERA_Suspend(void) {
    CMW_CAMERA_Suspend(DCMIPP_PIPE1);
}

/* 
    PLL1 = 800Mhz 
    PLL2 = 600Mhz
    PLL3 = 900Mhz
    PLL4 = 1000Mhz
*/
static void Configure_IC11_IC2(void) {
    RCC_ICInitTypeDef Ic11Init = {0};
    RCC_ICInitTypeDef Ic1Init = {0};
    RCC_ICInitTypeDef Ic2Init = {0};

    /* IC1 configuration */
    Ic1Init.ClockSelection = RCC_ICCLKSOURCE_PLL2;
    Ic1Init.ClockDivider = 1;
    MODIFY_REG(RCC->IC1CFGR, RCC_IC1CFGR_IC1SEL | RCC_IC1CFGR_IC1INT,
            Ic1Init.ClockSelection | \
            ((Ic1Init.ClockDivider - 1U) << RCC_IC1CFGR_IC1INT_Pos));

    /* IC11 configuration */
    Ic11Init.ClockSelection = RCC_ICCLKSOURCE_PLL1;
    Ic11Init.ClockDivider = 2;
    MODIFY_REG(RCC->IC11CFGR, RCC_IC11CFGR_IC11SEL | RCC_IC11CFGR_IC11INT,
            Ic11Init.ClockSelection | \
            ((Ic11Init.ClockDivider - 1U) << RCC_IC11CFGR_IC11INT_Pos));
    
    /* IC2 configuration */
    Ic2Init.ClockSelection = RCC_ICCLKSOURCE_PLL1;
    Ic2Init.ClockDivider = 2;
    MODIFY_REG(RCC->IC2CFGR, RCC_IC2CFGR_IC2SEL | RCC_IC2CFGR_IC2INT,
            Ic2Init.ClockSelection | \
            ((Ic2Init.ClockDivider - 1U) << RCC_IC2CFGR_IC2INT_Pos));
}

HAL_StatusTypeDef MX_DCMIPP_ClockConfig(DCMIPP_HandleTypeDef *hdcmipp) {
    UNUSED(hdcmipp);
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_DCMIPP;
    PeriphClkInitStruct.DcmippClockSelection = RCC_DCMIPPCLKSOURCE_IC17;
    PeriphClkInitStruct.ICSelection[RCC_IC17].ClockSelection = RCC_ICCLKSOURCE_PLL4;
    PeriphClkInitStruct.ICSelection[RCC_IC17].ClockDivider = 3; // 1000/3 = 333.Mhz
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        return HAL_ERROR;
    }

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CSI;
    PeriphClkInitStruct.ICSelection[RCC_IC18].ClockSelection = RCC_ICCLKSOURCE_PLL4;
    PeriphClkInitStruct.ICSelection[RCC_IC18].ClockDivider = 50; // 1000/50 = 20Mhz
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

int CMW_CAMERA_PIPE_FrameEventCallback(uint32_t pipe) {
  switch (pipe)
  {
    TX_EVENT_FLAGS_GROUP* evnets;
    case DCMIPP_PIPE1 :
        evnets = get_camera_events();
        tx_event_flags_set(evnets, 1 << 1, TX_OR);
        break;
    case DCMIPP_PIPE2 :
        evnets  = get_ai_events();
        tx_event_flags_set(evnets, 1 << 1, TX_OR);
        break;
  }
  return 0;
}
