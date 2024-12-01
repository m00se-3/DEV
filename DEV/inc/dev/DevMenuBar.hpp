#ifndef DEV_MENUBAR_HPP
#define DEV_MENUBAR_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <TGUI/Widgets/MenuBar.hpp>
#include <TGUI/Layout.hpp>

namespace dev {

    class DevMenuBar {
    public:
        [[nodiscard]] tgui::MenuBar::Ptr Build(sf::RenderWindow* window);

        void SetFileIsOpen(bool open);

    private:
        tgui::MenuBar::Ptr _root;
    };
}

#endif