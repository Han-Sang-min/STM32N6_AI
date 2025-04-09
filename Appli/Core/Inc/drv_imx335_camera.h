#ifndef PROC_MAIN_H
#define PROC_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
#include "cmw_camera.h"
#include <assert.h>

void IMX335_Init_Camera(void);
void IMX335_StartCamera(uint32_t pipe, uint8_t *pbuff, uint32_t mode);
void IMX335_DoubleBufferStart(uint32_t pipe, uint8_t *pbuff1, uint8_t *pbuff2, uint32_t Mode);
void IMX335_BackgroundProcess(void);
void IMX335_CAMERA_Resume(void);
void IMX335_CAMERA_Suspend(void);

/* Not used internally; appears to be initialized to a default value of 30 during hardware initialization */
#define CAMERA_FPS      30

#define CAMERA_FLIP     CMW_MIRRORFLIP_NONE
/* Leave the driver use the default resolution */
#define CAMERA_WIDTH    0 // 2592
#define CAMERA_HEIGHT   0 // 1944

#define FRAME_WIDTH     640
#define FRAME_HEIGHT    480

#define NN_WIDTH    224
#define NN_HEIGHT   224
#define NN_BPP      3

#define COLOR_BGR   (0)
#define COLOR_RGB   (1)
#define COLOR_MODE  COLOR_BGR

#define CAPTURE_FORMAT      DCMIPP_PIXEL_PACKER_FORMAT_RGB565_1
#define CAPTURE_BPP         2
#define GAMMA_CONVERSION    0

#ifdef __cplusplus
}
#endif
#endif