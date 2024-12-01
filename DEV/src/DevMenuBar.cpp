#include <dev/DevMenuBar.hpp>
#include <TGUI/Core.hpp>

namespace dev {
    static constexpr float barPercent = 0.05f;

    tgui::MenuBar::Ptr DevMenuBar::Build(sf::RenderWindow* window) {        
        _root = tgui::MenuBar::create();
        _root->setHeight(static_cast<float>(window->getSize().y) * barPercent);
        _root->setAutoLayoutUpdateEnabled(true);

        _root->addMenu("File");
        _root->addMenuItem("Open");
        _root->addMenuItem("Save");
        _root->addMenuItem("Close");
        _root->addMenuItem("Exit");

        _root->connectMenuItem({"File", "Exit"}, [window](){
            window->close();
        });


        return _root;
    }

    void DevMenuBar::SetFileIsOpen(bool open) {
        _root->setMenuItemEnabled({"File", "Save"}, open);
        _root->setMenuItemEnabled({"File", "Close"}, open);
    }
}