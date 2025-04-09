#include "CameraThread.hpp"

#include <gui/camera_screen/CameraPresenter.hpp>

CameraThread &CameraThread::getInstance()
{
    static CameraThread instance;
    return instance;
}

void CameraThread::ThreadFunc(ULONG arg)
{
    CameraThread *self = reinterpret_cast<CameraThread*>(arg);
    self->Run();
}

void CameraThread::init()
{
    tx_thread_create(
        &thread,
        (CHAR*)"CameraThread",
        CameraThread::ThreadFunc,
        (ULONG)this,
        stack,
        STACK_SIZE,
        5, 5, TX_NO_TIME_SLICE, TX_AUTO_START
    );

    tx_event_flags_create(&events, (CHAR*)"CAMERA_EVENT_GROUP");
}

void CameraThread::Run()
{
    ULONG actual_flags = 0;
    
    while (true) {
        tx_event_flags_get(&events, EVENT_START_CAMERA_THREAD, TX_OR_CLEAR, &actual_flags, TX_WAIT_FOREVER);
        while (true) {
            tx_event_flags_get(&events, EVENT_FRAME_INTERUPT, TX_OR_CLEAR, &actual_flags, TX_WAIT_FOREVER);
            auto& model = static_cast<FrontendApplication*>(FrontendApplication::getInstance())->getModel();
            model.setCameraRefreshRequest();
            model.swap_bitmap();
        }
    }
}
