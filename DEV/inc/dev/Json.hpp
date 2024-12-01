#ifndef DEV_JSON_HPP
#define DEV_JSON_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <dev/GuiPanel.hpp>

#include <filesystem>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

namespace dev {
    struct Json {
        Json() = default;
        Json(const std::filesystem::path& filePath);
        void operator()(GuiPanel<tgui::Panel>& panel, const std::filesystem::path& formPath);
        [[nodiscard]] constexpr operator bool() const { return !_jsonHandle.empty(); }

        nlohmann::json _jsonHandle;
    };
}

#endif