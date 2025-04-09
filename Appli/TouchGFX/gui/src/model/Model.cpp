#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "BitmapManager.hpp"

#ifndef SIMULATOR
#include "stm32n6xx_hal.h"
#endif

using namespace touchgfx;

Model::Model() : modelListener(0)
{
#ifndef SIMULATOR    
    cameraDriver.Init();
    Init_AI();
#endif
}

void Model::setupModel()
{
#ifndef SIMULATOR
    uint8_t *bgBufAddr1, *bgBufAddr2;

    BitmapManager::createBitmap(W_VAL, H_VAL, Bitmap::ARGB8888, BitmapManager::AI);
    BitmapManager::createBitmap(W_VAL, H_VAL, Bitmap::RGB565, BitmapManager::CAMERA1);
    BitmapManager::createBitmap(W_VAL, H_VAL, Bitmap::RGB565, BitmapManager::CAMERA2);

    bgBufAddr1 = BitmapManager::getBitmapAddr(BitmapManager::CAMERA1);
    bgBufAddr1 = (uint8_t*)(((uint32_t)bgBufAddr1 + 0xFE) & ~0xFF);

    bgBufAddr2 = BitmapManager::getBitmapAddr(BitmapManager::CAMERA2);
    bgBufAddr2 = (uint8_t*)(((uint32_t)bgBufAddr2 + 0xFE) & ~0xFF);

    cameraDriver.DoubleBufferStart(DCMIPP_PIPE1, bgBufAddr1, bgBufAddr2, DCMIPP_MODE_CONTINUOUS);
    // cameraDriver.Start(DCMIPP_PIPE1, bgBufAddr, DCMIPP_MODE_CONTINUOUS);
#endif
}

Model::~Model()
{
#ifndef SIMULATOR
    // BitmapManager::releaseBitmap(BitmapManager::AI);
    // BitmapManager::releaseBitmap(BitmapManager::CAMERA);
#endif
}

void Model::StartAiCapture()
{
#ifndef SIMULATOR
    Start_Capture();
#endif    
}

void Model::StartAiPostProcess()
{
#ifndef SIMULATOR
    Process_AI();
#endif
}

void Model::getAiInfo(AI_Info **out)
{
    // uint8_t* BufAddr;
        
    *out = &aiInfo;
    
    // BufAddr = BitmapManager::getBitmapAddr(BitmapManager::AI);
    // SCB_InvalidateDCache_by_Addr(BufAddr, 480*640*4);
}

void Model::swap_bitmap()
{
    static int32_t sm_switch = 0;
    BitmapManager::BitmapIndex idx;
    // uint8_t* BufAddr;
    BitmapId id;

    idx = sm_switch ? BitmapManager::CAMERA1 : BitmapManager::CAMERA2;
    
    id = BitmapManager::getBitmapId(idx);
    camData.curr_id = id;

    // BufAddr = BitmapManager::getBitmapAddr(BitmapManager::CAMERA1);
    // SCB_InvalidateDCache_by_Addr(BufAddr, 480*640*2);
    // BufAddr = BitmapManager::getBitmapAddr(BitmapManager::CAMERA2);
    // SCB_InvalidateDCache_by_Addr(BufAddr, 480*640*2);
    
    sm_switch = !sm_switch;
}

void Model::ProcessCameraBackground()
{
#ifndef SIMULATOR
    cameraDriver.BackgroundProcess();
#endif
}
