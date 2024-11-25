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
        static constexpr uint32_t def_Width = 640u, def_Height = 480u;
        sf::RenderWindow _window { sf::VideoMode({def_Width, def_Width}), "Data Editor-Viewer" };
        tgui::Gui _gui;

        GuiState _currentState {std::monostate{}}, _nextState {MainMenu{}};
    };
}

#endif