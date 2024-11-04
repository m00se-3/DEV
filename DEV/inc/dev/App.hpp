#ifndef DEV_APP_H
#define DEV_APP_H

#include <variant>
#include <dev/Forms.hpp>

namespace dev
{
    class App
    {
    public:
        using GuiState = std::variant<
                            std::monostate,
                            MainMenu,
                            Json>;

        App();

        void Run();

        void OpenState(GuiState state);

    private:
        sf::RenderWindow _window;
        tgui::Gui _gui;

        GuiState _currentState, _nextState;
    };
}

#endif