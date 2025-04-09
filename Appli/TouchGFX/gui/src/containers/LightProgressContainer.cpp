#include <gui/containers/LightProgressContainer.hpp>

#define INIT_LIGHT(i) lightsOn[i] = &light_on_##i;

LightProgressContainer::LightProgressContainer()
{
    curr = 0;

    INIT_LIGHT(0);
    INIT_LIGHT(1);
    INIT_LIGHT(2);
    INIT_LIGHT(3);
    INIT_LIGHT(4);
    INIT_LIGHT(5);
    INIT_LIGHT(6);
    INIT_LIGHT(7);
}

void LightProgressContainer::showNextLight()
{
    if (curr < NUMBER_OF_LIGHTS) {
        lightsOn[curr]->setVisible(true);
        lightsOn[curr]->invalidate();
        curr++;
    }
}

void LightProgressContainer::hideLastLight()
{
    if (curr > 0) {
        curr--;
        lightsOn[curr]->setVisible(false);
        lightsOn[curr]->invalidate();
    }
}

void LightProgressContainer::initialize()
{
    LightProgressContainerBase::initialize();
}
