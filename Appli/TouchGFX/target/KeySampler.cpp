#include "KeySampler.hpp"
#include "main.h"

using namespace touchgfx;

void KeySampler::init()
{
    previousState = 0;
}

bool KeySampler::sample(uint8_t& key)
{
    bool buttonPressed = false;
    if ((HAL_GPIO_ReadPin(USER_BUTTON_1_GPIO_Port, USER_BUTTON_1_Pin) != GPIO_PIN_RESET))
    {
        if (previousState != 1)
        {
            buttonPressed = true;
            key = 1; // This is the "hardware button key" reffered in the TouchGFX Designer Interactions
            previousState = 1;
        }
    }
    else
    {
        previousState = 0;
    }

    return buttonPressed;
}
