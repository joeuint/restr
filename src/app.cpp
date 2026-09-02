#include <ftxui/component/component.hpp>
#include <ftxui/ftxui.hpp>
#include <string>

#include "app.hpp"

std::vector<std::string> RestrApp::getCollectionNames() {
    std::vector<std::string> collectionNames;

    for (auto&& item: collections) {
        const std::string name { item->getName() };
        collectionNames.push_back(name);
    }

    return collectionNames;
}

void RestrApp::run() {
    auto screen { ftxui::App::Fullscreen() };

    std::vector<std::string> entries { getCollectionNames() };

    std::vector<std::string> documentEntries {
        "POST /auth/login",
        "POST /auth/signup",
        "POST /auth/resetPassword",
        "POST /auth/confirmPassword",
    };

    int selected { 0 };
    int documentSelected { 0 };

    ftxui::MenuOption menuOption;
    menuOption.on_enter = screen.ExitLoopClosure();
    auto menu = ftxui::Menu(&entries, &selected, menuOption);

    ftxui::MenuOption documentOption;
    documentOption.on_enter = screen.ExitLoopClosure();

    auto documentMenu = ftxui::Menu(&documentEntries, &documentSelected, documentOption);

    auto mainComponent = ftxui::Container::Horizontal({menu, documentMenu});

    auto uiRenderer = ftxui::Renderer(mainComponent, [&] {
        auto menuWin = menu->Render();
        auto docMenuWin = documentMenu->Render();

        return ftxui::hbox({
                menuWin | ftxui::flex | ftxui::border,
                docMenuWin | ftxui::flex | ftxui::border
        });
    });

    
    screen.Loop(uiRenderer);
}

