#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <gui_generated/menu_screen/MenuViewBase.hpp>
#include <gui/menu_screen/MenuPresenter.hpp>

class MenuView : public MenuViewBase
{
public:
    MenuView();
    virtual ~MenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void stDaytimeLeftPressed() override;
    virtual void stDaytimeRightPressed() override;
    virtual void endDaytimeRightPressed() override;
    virtual void endDaytimeLeftPressed() override;
protected:
private:
};

#endif // MENUVIEW_HPP
