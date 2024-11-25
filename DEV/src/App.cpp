#include <dev/App.hpp>
#include <TGUI/Loading/Theme.hpp>
#include <SFML/Window/Event.hpp>

#include <filesystem>


template<typename... T>
struct StateCreator : T... { using T::operator()...; };

namespace dev {

    App::App()
    {
        const std::filesystem::path themes = TGUI_THEMES;
        
        tgui::Theme::setDefault( (themes / "Black.txt").string());
    }

    void App::Run()
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
                    break;
                }

            }

            // If a new GUI state is requested, setup the new state.
            if(_currentState.index() != _nextState.index())
            {
                _currentState = _nextState;

                _gui.removeAllWidgets();

                std::visit(
                    StateCreator{
                        [](std::monostate) {},
                        [&](auto&& state){ state(_gui); }
                    },
                    _currentState
                );
            }

            constexpr uint8_t def_bg_color_value = 64u;

            _window.clear(sf::Color{ def_bg_color_value, def_bg_color_value, def_bg_color_value});

            _gui.draw();

            _window.display();
        }
    }

    void App::OpenState(GuiState state)
    {
        _nextState = state;
    }

}