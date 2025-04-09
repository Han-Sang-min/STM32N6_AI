#ifndef LIGHTPROGRESSCONTAINER_HPP
#define LIGHTPROGRESSCONTAINER_HPP

#include <gui_generated/containers/LightProgressContainerBase.hpp>

class LightProgressContainer : public LightProgressContainerBase
{
public:
    LightProgressContainer();
    virtual ~LightProgressContainer() {}

    virtual void initialize();

    void showNextLight();
    void hideLastLight();
    int getCurrentLightCount() const {return curr;}
protected:
private:
    int curr;
    static const int NUMBER_OF_LIGHTS = 8;
    touchgfx::Image* lightsOn[NUMBER_OF_LIGHTS];
};

#endif // LIGHTPROGRESSCONTAINER_HPP
