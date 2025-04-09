#include "HwButtonCtrl.hpp"
#include "main.h"

using namespace touchgfx;

HwButtonCtrl::HwButtonCtrl() {
    init();
}

void HwButtonCtrl::init() {
    previousState = 0;
}

bool HwButtonCtrl::sample(uint8_t &key) {
    bool buttonPressed = false;
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) {
        key = 1;
        previousState = 1;
        return true;
    } else if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0) == GPIO_PIN_SET) {
        key = 2;
        previousState = 2;
        return true;
    } else {
        key = 0;
        previousState = 0;
    }
    return buttonPressed;
}
