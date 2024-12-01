#ifndef DEV_GUIPANEL_HPP
#define DEV_GUIPANEL_HPP

#include <TGUI/Layout.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include <filesystem>
#include <concepts>

namespace dev {

    template<typename T>
    concept PanelType = std::derived_from<T, tgui::Container>;

    template<PanelType Type>
    class GuiPanel {
    public:
        GuiPanel() = default;

        GuiPanel(const GuiPanel&) = default;
        GuiPanel(GuiPanel&&) = default;
        GuiPanel& operator=(const GuiPanel&) = default;
        GuiPanel& operator=(GuiPanel&&) = default;

        virtual ~GuiPanel() = default;

        [[nodiscard]] constexpr Type::Ptr operator->() { return _panel; }

        [[nodiscard]] constexpr Type::Ptr Get() const { return _panel; }
        constexpr void SetVisible(bool visible) { _panel->setVisible(visible); }        

        void Create(const tgui::Layout2d& size) {
            _panel = Type::create(size);
            _panel->setPosition({"0%", "6%"});
        }

        void LoadFromFile(const std::filesystem::path& filePath) {
            if(std::filesystem::exists(filePath)) {
                _panel->loadWidgetsFromFile(filePath.string());
            }
        }

    private:
        Type::Ptr _panel;
    };
}

#endif