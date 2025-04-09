#ifndef SIMULATOR
#include "IMX335CameraDriver.hpp"
#include "drv_imx335_camera.h"

void IMX335CameraDriver::Init()
{
    IMX335_Init_Camera();
}

void IMX335CameraDriver::Start(uint32_t pipe, uint8_t *pbuff, uint32_t mode)
{
    IMX335_StartCamera(pipe, pbuff, mode);
}

void IMX335CameraDriver::DoubleBufferStart(uint32_t pipe, uint8_t *pbuff1, uint8_t *pbuff2, uint32_t mode)
{
    IMX335_DoubleBufferStart(pipe, pbuff1, pbuff2, mode);
}

void IMX335CameraDriver::BackgroundProcess()
{
    IMX335_BackgroundProcess();
}

void IMX335CameraDriver::Resume()
{
    IMX335_CAMERA_Resume();
}

void IMX335CameraDriver::Suspend()
{
    IMX335_CAMERA_Suspend();
}

#endif // SIMULATOR
