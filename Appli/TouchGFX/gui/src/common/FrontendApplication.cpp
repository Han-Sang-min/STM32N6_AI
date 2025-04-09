#include <gui/common/FrontendApplication.hpp>
#include "AIThread.hpp"

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap)
{
#ifndef SIMULATOR
    uint32_t cacheSize = 0x600000; // 6MB
    /* If the number of caches changes, code stability issues may arise. (i.e. not aligned to 16-bit boundaries)*/
    uint16_t* cacheStartAddr = (uint16_t*)0x900FFF50;

    Bitmap::setCache(cacheStartAddr, cacheSize, 3);
    model.setupModel();
#else
    const uint32_t cacheSize = 0x600000;
    uint16_t* cacheStartAddr = (uint16_t*)malloc(cacheSize);
    if (cacheStartAddr != nullptr)
    {
        Bitmap::setCache(cacheStartAddr, cacheSize, 4);
    }
#endif
}
