#ifndef DEV_MAINMENU_HPP
#define DEV_MAINMENU_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace dev {
    struct MainMenu {
        void operator()(tgui::Gui& gui);
    };
}

#endif