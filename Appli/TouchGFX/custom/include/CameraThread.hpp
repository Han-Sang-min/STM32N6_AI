#ifndef CAMERA_THREAD_HPP
#define CAMERA_THREAD_HPP

#include "tx_api.h"
#include <gui/model/Model.hpp>
#include "stm32n6xx_hal.h"
#include <gui/common/FrontendApplication.hpp>
#include <cstdio>

using namespace touchgfx;

#define EVENT_START_CAMERA_THREAD     (1 << 0)
#define EVENT_FRAME_INTERUPT          (1 << 1)

class CameraThread {
public:
    static CameraThread& getInstance();
    static void ThreadFunc(ULONG arg);
    void init();
    void Run();

    static TX_EVENT_FLAGS_GROUP* getEventGroup() { return &events; }
private:
    CameraThread() = default;
    
    TX_THREAD thread;
    inline static TX_EVENT_FLAGS_GROUP events;
    static const ULONG STACK_SIZE = 2048;
    UCHAR stack[STACK_SIZE];
};

#endif // CAMERA_THREAD_HPP