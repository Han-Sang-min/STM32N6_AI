#include <gui/camera_screen/CameraView.hpp>
#include <gui/camera_screen/CameraPresenter.hpp>
#include "CustomTypes.hpp"

#include "AIThread.hpp"
#include "CameraThread.hpp"
#include "drv_imx335_camera.h"
#include <type_traits>
CameraPresenter::CameraPresenter(CameraView& v)
    : view(v)
{
}

void CameraPresenter::activate()
{
    tx_event_flags_set(AIThread::getInstance().getEventGroup(), EVENT_AI_TRIGGER, TX_OR);
    tx_event_flags_set(CameraThread::getInstance().getEventGroup(), EVENT_START_CAMERA_THREAD, TX_OR);
}

void CameraPresenter::deactivate()
{

}

void CameraPresenter::tick()
{
    BitmapId id;
    static uint32_t prev_time = HAL_GetTick();
    uint32_t fps_val, frame_ms;

    if (model->isCameraRefreshNeeded()) {
        model->clearCameraRefresh();

        frame_ms = HAL_GetTick() - prev_time;
        fps_val = frame_ms ? (1000 / frame_ms) : 0;
        view.setFpsValue(fps_val);

        if (model->isAIDataReady()) {
            ai_data_ready_event();
        }
        model->getCurrBitmap(&id);
        view.swapCamBuf(id);
        camera_refrash_event();

        prev_time = HAL_GetTick();
    }
}

void CameraPresenter::camera_refrash_event()
{
    model->ProcessCameraBackground();
    view.refreshCameraArea();
}

void CameraPresenter::ai_data_ready_event()
{
    view.clearAIMarker();
    AI_Result **coor = nullptr;
    AI_Info *info = nullptr;
    model->getAICoordinates(coor);
    model->getAiInfo(&info);
    view.updateAIMarker(info, *coor);
}
