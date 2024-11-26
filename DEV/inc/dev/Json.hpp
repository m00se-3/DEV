#ifndef DEV_JSON_HPP
#define DEV_JSON_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace dev {
    struct Json {
        void operator()(tgui::Gui& gui);
    };
}

#endif