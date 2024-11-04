#include <dev/MainMenu.hpp>

namespace dev
{
    void MainMenu::operator()(tgui::Gui& gui)
    {
        auto button = tgui::Button::create("Click Me!");

        button->onPress([button](){ button->setText("Ouch!"); });
        gui.add(button);
    }
}