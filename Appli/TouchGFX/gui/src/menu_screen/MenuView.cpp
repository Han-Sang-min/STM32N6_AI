#include <gui/menu_screen/MenuView.hpp>

MenuView::MenuView()
{

}

void MenuView::setupScreen()
{
    MenuViewBase::setupScreen();
}

void MenuView::tearDownScreen()
{
    MenuViewBase::tearDownScreen();
}

void MenuView::stDaytimeLeftPressed()
{
    int tmpVal = Unicode::atoi(st_daytime.getWildcard());
    if (tmpVal > 0) {
        tmpVal--;
        Unicode::snprintf(st_daytimeBuffer, ST_DAYTIME_SIZE, "%d", tmpVal);
        st_daytime.invalidate();
    }
}

void MenuView::stDaytimeRightPressed()
{
    int tmpVal = Unicode::atoi(st_daytime.getWildcard());
    if (tmpVal < 24) {
        tmpVal++;
        Unicode::snprintf(st_daytimeBuffer, ST_DAYTIME_SIZE, "%d", tmpVal);
        st_daytime.invalidate();
    }
}

void MenuView::endDaytimeRightPressed()
{
    int tmpVal = Unicode::atoi(end_daytime.getWildcard());
    if (tmpVal < 24) {
        tmpVal++;
        Unicode::snprintf(end_daytimeBuffer, END_DAYTIME_SIZE, "%d", tmpVal);
        end_daytime.invalidate();
    }
}

void MenuView::endDaytimeLeftPressed()
{
    int tmpVal = Unicode::atoi(end_daytime.getWildcard());
    if (tmpVal > 0) {
        tmpVal--;
        Unicode::snprintf(end_daytimeBuffer, END_DAYTIME_SIZE, "%d", tmpVal);
        end_daytime.invalidate();
    }
}
