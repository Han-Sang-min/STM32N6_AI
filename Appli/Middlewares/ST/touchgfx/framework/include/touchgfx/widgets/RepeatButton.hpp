/******************************************************************************
* Copyright (c) 2018(-2024) STMicroelectronics.
* All rights reserved.
*
* This file is part of the TouchGFX 4.24.2 distribution.
*
* This software is licensed under terms that can be found in the LICENSE file in
* the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
*******************************************************************************/

/**
 * @file touchgfx/widgets/RepeatButton.hpp
 *
 * Declares the touchgfx::RepeatButton class.
 */
#ifndef TOUCHGFX_REPEATBUTTON_HPP
#define TOUCHGFX_REPEATBUTTON_HPP

#include <touchgfx/events/ClickEvent.hpp>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/widgets/Button.hpp>

namespace touchgfx
{
/**
 * A RepeatButton is similar to a regular Button, but it will 'repeat' if pressed for a long
 * period of time. The RepeatButton differs from a regular Button with regards to
 * activation. A Button is activated when the button is released, whereas a RepeatButton
 * is activated immediately when pressed and then at regular intervals. A RepeatButton
 * does not activate when released.
 *
 * As for other well-known repeat buttons, the interval from the first activation until
 * the second activation as well as the subsequent interval between activations can be
 * set for the RepeatButton.
 *
 * The default values for initial delay is 10 ticks, and the default value for the
 * following delays between button activations is 5 ticks.
 */
class RepeatButton : public Button
{
public:
    RepeatButton();

    /**
     * Sets the delay (in number of ticks) from the first button activation until the next
     * time it will be automatically activated.
     *
     * @param  delay The delay, measured in ticks, between first activation and second activation.
     *
     * @see setInterval, getDelay
     */
    virtual void setDelay(int delay);

    /**
     * Gets the delay in ticks from first button activation until next activation.
     *
     * @return The delay, measured in ticks, between first activation and second activation.
     *
     * @see setDelay
     */
    virtual int getDelay();

    /**
     * Sets the interval in number of ticks between each each activation of the pressed
     * button after the second activation.
     *
     * @param  interval The interval between repeated activations, measured in ticks.
     *
     * @see setDelay, getInterval
     */
    virtual void setInterval(int interval);

    /**
     * The interval between repeated activations, measured in ticks. This is the number of
     * ticks between the an activation beyond the first and the following activation.
     *
     * @return The interval between repeated activations, measured in ticks.
     *
     * @see setInterval
     */
    virtual int getInterval();

    virtual void handleClickEvent(const ClickEvent& event);

    virtual void handleTickEvent();

private:
    int16_t ticksDelay;
    int16_t ticksInterval;

    int16_t ticks;
    int16_t ticksBeforeContinuous;
};

} // namespace touchgfx

#endif // TOUCHGFX_REPEATBUTTON_HPP
