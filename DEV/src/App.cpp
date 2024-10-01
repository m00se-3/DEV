#include <App.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace dev {

    App::App()
    : _window(sf::VideoMode{{640u, 480u}}, "Data  Editor-Viewer"), _gui(_window)
    {
        _gui.mainLoop();
    }

}