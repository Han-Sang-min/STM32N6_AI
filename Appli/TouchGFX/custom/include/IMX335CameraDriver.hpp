#ifndef IMX335_CAMERA_DRIVER_HPP
#define IMX335_CAMERA_DRIVER_HPP

#include "ICameraDriver.hpp"

class IMX335CameraDriver : public ICameraDriver {
public:
    virtual ~IMX335CameraDriver() {}

    virtual void Init() override;
    virtual void Start(uint32_t pipe, uint8_t *pbuff, uint32_t mode) override;
    virtual void DoubleBufferStart(uint32_t pipe, uint8_t *pbuff1, uint8_t *pbuff2, uint32_t mode) override;
    virtual void BackgroundProcess() override;
    virtual void Resume() override;    
    virtual void Suspend() override;
};

#endif // IMX335_CAMERA_DRIVER_HPP
