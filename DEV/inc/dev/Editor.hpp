#ifndef DEV_EDITOR_HPP
#define DEV_EDITOR_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <dev/GuiPanel.hpp>

namespace dev {
    class Editor {
    public: 
        void operator()(GuiPanel<tgui::Panel>& panel);
    };
}

#endif