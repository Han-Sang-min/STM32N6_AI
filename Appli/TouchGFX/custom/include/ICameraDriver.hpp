#ifndef ICAMERA_DRIVER_HPP
#define ICAMERA_DRIVER_HPP

#include <cstdint>

class ICameraDriver {
public:
    virtual ~ICameraDriver() {}

    virtual void Init() = 0;
    virtual void Start(uint32_t pipe, uint8_t *pbuff, uint32_t mode) = 0;
    virtual void DoubleBufferStart(uint32_t pipe, uint8_t *pbuff1, uint8_t *pbuff2, uint32_t mode) = 0;
    virtual void BackgroundProcess() = 0;
    virtual void Resume() = 0;
    virtual void Suspend() = 0;
};

#endif // ICAMERA_DRIVER_HPP
