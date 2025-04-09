#ifndef HW_BUTTON_CTRL_HPP
#define HW_BUTTON_CTRL_HPP

#include <platform\driver\button\ButtonController.hpp>

namespace touchgfx
{
class HwButtonCtrl : public ButtonController {
public:
    HwButtonCtrl();

    virtual ~HwButtonCtrl() {}
    virtual void init();
    virtual bool sample(uint8_t& key) override;

private:
    bool isButtonPressed(uint8_t buttonId);
    uint8_t previousState;
};
}

#endif  // HW_BUTTON_CTRL_HPP
