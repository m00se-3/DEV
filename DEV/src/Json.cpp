#include <dev/Json.hpp>
#include <fstream>

namespace dev {
    Json::Json(const std::filesystem::path& filePath) {
        std::fstream json{filePath};
        _jsonHandle = nlohmann::json::parse(json);
    }

    void Json::operator()(GuiPanel<tgui::Panel>& panel, const std::filesystem::path& formPath) {
        panel.LoadFromFile(formPath);
    }
}