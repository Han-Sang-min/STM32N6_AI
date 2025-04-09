#ifndef AI_THREAD_HPP
#define AI_THREAD_HPP

#include "tx_api.h"
#include <gui/model/Model.hpp>
#include "stm32n6xx_hal.h"
#include <gui/common/FrontendApplication.hpp>
#include <cstdio>

using namespace touchgfx;

#define EVENT_AI_TRIGGER     (1 << 0)
#define EVENT_AI_CAPTURE     (1 << 1)

class AIThread {
public:
    static AIThread& getInstance();
    static void ThreadFunc(ULONG arg);
    void init();
    void Run();

    static TX_EVENT_FLAGS_GROUP* getEventGroup() { return &events; }
private:
    AIThread() = default;
    
    TX_THREAD thread;
    inline static TX_EVENT_FLAGS_GROUP events;
    static const ULONG STACK_SIZE = 2048;
    UCHAR stack[STACK_SIZE];
};

#endif // AI_THREAD_HPP