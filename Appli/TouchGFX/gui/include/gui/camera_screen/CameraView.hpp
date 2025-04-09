#ifndef CAMERAVIEW_HPP
#define CAMERAVIEW_HPP

#include <gui_generated/camera_screen/CameraViewBase.hpp>
#include <gui/camera_screen/CameraPresenter.hpp>
#include "UTIL_Draw.h"

#ifndef SIMULATOR
#include "IMX335CameraDriver.hpp"
#endif

class CameraView : public CameraViewBase
{
public:
    CameraView();
    virtual ~CameraView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void clearAIMarker();
    void updateAIMarker(AI_Info *info, AI_Result *coor);
    void refreshCameraArea();
    void swapCamBuf(BitmapId id);
    void setFpsValue(uint32_t fps_val);

protected:
private:
    UTIL_Draw drawTool;
    
    inline static uint8_t isInit = false;
    uint32_t W_VAL = 640;
    uint32_t H_VAL = 480;
};

#endif // CAMERAVIEW_HPP
