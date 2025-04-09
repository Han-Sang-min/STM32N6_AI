#include <gui/camera_screen/CameraView.hpp>
#include "BitmapManager.hpp"

#include <cstring>

#ifndef SIMULATOR
#include "stm32n6xx_hal.h"
#endif // SIMULATOR

CameraView::CameraView()
{

}

void CameraView::setupScreen()
{
    CameraViewBase::setupScreen();

#ifndef SIMULATOR
    BitmapId bmpId;
    uint8_t *aiBufAddr;
    uint32_t aiFrameWidth, aiFrameHeight;

    bmpId = BitmapManager::getBitmapId(BitmapManager::AI);
    aiScreen.setBitmap(bmpId);
    bmpId = BitmapManager::getBitmapId(BitmapManager::CAMERA1);
    cameraScreen.setBitmap(bmpId);

    aiFrameWidth = 640; // TODO: get 구조로 변경
    aiFrameHeight = 480; // TODO: get 구조로 변경

    aiBufAddr = BitmapManager::getBitmapAddr(BitmapManager::AI);
    drawTool.setBuffer((uint32_t *)aiBufAddr, aiFrameWidth, aiFrameHeight, UTIL_Draw::PF_ARGB8888);
    drawTool.clearBuffer();
#endif // SIMULATOR
}

void CameraView::tearDownScreen()
{
    CameraViewBase::tearDownScreen();
}

void CameraView::updateAIMarker(AI_Info *info, AI_Result *coor)
{
#ifndef SIMULATOR
    uint32_t nb_rois = info->nb_rois;

    for (int32_t i = 0; i < nb_rois; i++) {
        uint16_t RectWidth = coor[i].width;
        uint16_t RectHeight = coor[i].height;
        uint16_t Xpos = coor[i].x;
        uint16_t Ypos = coor[i].y;
        drawTool.drawRectangle(Xpos, Ypos, RectWidth, RectHeight, UTIL_Draw::COLOR_WHITE);
    }
#endif // SIMULATOR
}

void CameraView::clearAIMarker()
{
#ifndef SIMULATOR
    drawTool.clearBuffer();
#endif // SIMULATOR
}

void CameraView::refreshCameraArea()
{
#ifndef SIMULATOR
    invalidate();
#endif // SIMULATOR
}

void CameraView::swapCamBuf(BitmapId id)
{
    cameraScreen.setBitmap(id);
}

void CameraView::setFpsValue(uint32_t fps_val)
{
    Unicode::snprintf(FPStextBuffer, FPSTEXT_SIZE, "%d", fps_val);
}
