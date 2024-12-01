#include <dev/App.hpp>
#include <TGUI/Layout.hpp>
#include <TGUI/Loading/Theme.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include <filesystem>
#include <variant>

template<typename... T>
struct StateCreator : T... { using T::operator()...; };

namespace dev {
    static constexpr auto devFontSize = 16u;
    static constexpr uint8_t devBGColorValue = 64u;

    void App::Run(const GuiState& initialState) {
        _nextState = initialState;
        Run();
    }

    void App::Run() {        
        tgui::Theme::setDefault( (_themes / "Black.txt").string());
        _gui.setWindow(_window);
        _gui.setTextSize(devFontSize);

        _gui.add(_menuBar.Build(&_window));
        _menuBar.SetFileIsOpen(false);

        _dataFileControls.Create(tgui::Layout2d{ "100%", "80%" });
        _dataFileControls.SetVisible(false);
        _gui.add(_dataFileControls.Get());

        sf::Clock eventClock{};

        if(_recorder && _playbackEvents) {
            while (_window.isOpen()) {
                PollEventsFromRecorder(eventClock);
                UpdateAppState();
            }
        } else {
            while (_window.isOpen()) {
                PollEventsFromWindow(eventClock);
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

    void App::PollEventsFromWindow(sf::Clock& clock) {
        bool noEvents = true;
        while (const auto event = _window.pollEvent()) {     
            noEvents = false;  
            _gui.handleEvent(*event);
            
            if(IsRecording()) { _recorder->AddEvent(*event); }
            
            if (event->is<sf::Event::Closed>()) {
                _window.close();
            }
        }

        if(noEvents && IsRecording()) { _recorder->AccumulateTime(clock.restart()); }
    }

    void App::UpdateAppState() {
        // If a new GUI state is requested, setup the new state.
        if(_currentState.index() != _nextState.index()) {
            _currentState = _nextState;

            std::visit(
                StateCreator{
                    [&](std::monostate) { _dataFileControls.SetVisible(false); },
                    [&](Json& state){
                        _dataFileControls.SetVisible(true);
                        state(_dataFileControls,
                        std::filesystem::path{DEV_FORMS_DIR} / "JsonForm.txt");
                    }
                },
                _currentState
            );
        }

        _window.clear(sf::Color{ devBGColorValue, devBGColorValue, devBGColorValue});
        _gui.draw();
        _window.display();
    }

}