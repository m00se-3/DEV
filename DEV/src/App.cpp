#include <dev/App.hpp>
#include <TGUI/Loading/Theme.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include <filesystem>
#include <variant>

template<typename... T>
struct StateCreator : T... { using T::operator()...; };

namespace dev {

    void App::Run(const GuiState& initialState) {
        tgui::Theme::setDefault( (_themes / "Black.txt").string());
        _nextState = initialState;
        _gui.setWindow(_window);
        sf::Clock timer{};

        if(_recorder && _playbackEvents) {
            while (_window.isOpen()) {
                PollEventsFromRecorder(timer);
                UpdateAppState();
            }
        } else {
            while (_window.isOpen()) {
                PollEventsFromWindow(timer);
                UpdateAppState();
            }

            if(_recorder && !_recorder->IsEmpty()) {
                _recorder->DumpToFile();
            }
        }
        
    }

    void App::PollEventsFromRecorder(sf::Clock& clock) {
        while(auto check = _recorder->GetNextEvent()) {
            if(std::holds_alternative<sf::Time>(*check)) {
                auto& timeEvent = std::get<sf::Time>(*check);
                timeEvent -= clock.restart();
                break;
            }

            auto event = std::get<sf::Event>(*check);
            _gui.handleEvent(event);

            if (event.is<sf::Event::Closed>()) {
                _window.close();
            }

            _recorder->PopEvent();
        }
    }

    void App::PollEventsFromWindow([[maybe_unused]] sf::Clock& clock) {
        while (const auto event = _window.pollEvent()) {     
            _gui.handleEvent(*event);
            
            if (event->is<sf::Event::Closed>()) {
                _window.close();
            }

        }
    }

    void App::UpdateAppState() {
        // If a new GUI state is requested, setup the new state.
        if(_currentState.index() != _nextState.index()) {
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