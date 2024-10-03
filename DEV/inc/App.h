#ifndef DEV_APP_H
#define DEV_APP_H

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace dev
{
    class App
    {
    public:
        App();

    private:
        sf::RenderWindow _window;
        tgui::Gui _gui;
    };
}

#endif