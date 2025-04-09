#include "thread_helper_c.h"

#include "AIThread.hpp"
#include "CameraThread.hpp"

extern "C" {

void ai_thread_init() 
{
    AIThread::getInstance().init();
}

TX_EVENT_FLAGS_GROUP* get_ai_events(void)
{
    return AIThread::getEventGroup();
}

void camera_thread_init(void)
{
    CameraThread::getInstance().init();
}

TX_EVENT_FLAGS_GROUP* get_camera_events(void)
{
    return CameraThread::getEventGroup();
}

}