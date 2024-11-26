#ifndef DEV_APP_H
#define DEV_APP_H

#include "dev/MainMenu.hpp"
#include <dev/Forms.hpp>
#include <internal/EventRecorder.hpp>

#include <memory>
#include <variant>

namespace dev {
    class App {
    public:
        using GuiState = std::variant<
                            std::monostate,
                            MainMenu,
                            Json>;

        App() = default;
        App(EventRecorder* recorder, bool playback = false) : _recorder(recorder), _playbackEvents(playback) {}

        void Run(const GuiState& initialState = MainMenu{});
        constexpr void OpenState(GuiState state) { _nextState = state; }

        void PollEventsFromWindow(sf::Clock& clock);
        void PollEventsFromRecorder(sf::Clock& clock);
        void UpdateAppState();

    private:
        static constexpr uint32_t def_Width = 640u, def_Height = 480u;
        sf::RenderWindow _window { sf::VideoMode({def_Width, def_Width}), "Data Editor-Viewer" };
        tgui::Gui _gui;
        std::filesystem::path _themes = TGUI_THEMES;
        std::unique_ptr<EventRecorder> _recorder;

        GuiState _currentState {std::monostate{}}, _nextState {std::monostate{}};
        bool _recordEvents = false, _playbackEvents = false;
    };
}

#endif