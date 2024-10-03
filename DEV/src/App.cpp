#include <App.h>

namespace dev {

    App::App()
    : _window(sf::VideoMode({640u, 480u}), "Data Editor-Viewer")
    {
        _gui.setWindow(_window);
        
        while (_window.isOpen())
        {            
            while (const auto event = _window.pollEvent())
            {
                _gui.handleEvent(*event);
                
                if (event->is<sf::Event::Closed>())
                {
                    _window.close();
                }
            }

            _window.clear();

            _gui.draw();

            _window.display();
        }

    }

}