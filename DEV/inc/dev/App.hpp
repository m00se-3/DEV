#ifndef DEV_APP_H
#define DEV_APP_H

#include <internal/EventRecorder.hpp>
#include <dev/Forms.hpp>
#include <dev/GuiPanel.hpp>
#include <TGUI/Widgets/Group.hpp>
#include <TGUI/Widgets/Panel.hpp>

#include <memory>

namespace dev {
    class App {
    public:
        using GuiState = std::variant<
                            std::monostate,
                            Json>;

        App() = default;
        App(EventRecorder* recorder, bool playback = false) : _recorder(recorder), _playbackEvents(playback) {}

        void Run();
        void Run(const GuiState& initialState);
        constexpr void OpenState(GuiState state) { _nextState = state; }
        [[nodiscard]] constexpr bool IsRecording() const { return _recordEvents; }

        void PollEventsFromWindow(sf::Clock& clock);
        void PollEventsFromRecorder(sf::Clock& clock);
        void UpdateAppState();

    private:
        static constexpr uint32_t def_Width = 800u, def_Height = 600u;
        sf::RenderWindow _window { sf::VideoMode({def_Width, def_Height}), "Data Editor-Viewer" };
        tgui::Gui _gui;
        DevMenuBar _menuBar;
        //GuiPanel<tgui::Panel> _statusBar;
        //GuiPanel<tgui::Panel> _messagePanel;
        GuiPanel<tgui::Panel> _dataFileControls;

        std::filesystem::path _themes = TGUI_THEMES;
        std::unique_ptr<EventRecorder> _recorder;

        GuiState _currentState {std::monostate{}}, _nextState {std::monostate{}};
        bool _recordEvents = false, _playbackEvents = false;
    };
}

#endif