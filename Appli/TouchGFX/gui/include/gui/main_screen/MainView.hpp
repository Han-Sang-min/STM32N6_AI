#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {};
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

private:
};

#endif // MAINVIEW_HPP
