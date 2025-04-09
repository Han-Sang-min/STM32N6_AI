#ifndef MODEL_HPP
#define MODEL_HPP

#ifndef SIMULATOR
#include "IMX335CameraDriver.hpp"
#include "ai_component.h"
#include "CustomTypes.hpp"
#include <touchgfx/Bitmap.hpp>
#endif // SIMULATOR
#include <stdint.h>

class ModelListener;

class Model
{
public:
    Model();
    void setupModel();
    ~Model();
    
    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }
    
    /* AI */
    void StartAiCapture();
    void StartAiPostProcess();
    void setAiInfo(uint16_t nb_rois) {
        aiInfo.nb_rois = nb_rois;
        aiInfo.ready = true;
    }
    void setAICoordinates(int index, AI_Result res) {
        aiRes[index].x = res.x;
        aiRes[index].y = res.y;
        aiRes[index].width = res.width;
        aiRes[index].height = res.height;
    }
    bool isAIDataReady() const { return aiInfo.ready; }
    void getAICoordinates(AI_Result **out) {
        *out = aiRes;
        aiInfo.ready = false;
    }
    void getAiInfo(AI_Info **out);

    /* Camera */
    void setCameraRefreshRequest() { camData.needsRefresh = true; }
    void swap_bitmap();
    void getCurrBitmap(touchgfx::BitmapId *in) { *in = camData.curr_id; }
    bool isCameraRefreshNeeded() const { return camData.needsRefresh; }
    void clearCameraRefresh() { camData.needsRefresh = false; }
    void ProcessCameraBackground();

protected:
#ifndef SIMULATOR
    CameraData camData;
    AI_Info   aiInfo;
    AI_Result aiRes[10];
    
    IMX335CameraDriver cameraDriver;
    const uint32_t W_VAL = 640;
    const uint32_t H_VAL = 480;

    // const uint32_t AI_WIDTH = 224;
    // const uint32_t AI_HEIGHT = 224;
#endif
    ModelListener* modelListener;
};

#endif // MODEL_HPP
