#include "app.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/ftxui.hpp>
#include <string>

std::vector<std::string> RestrApp::getCollectionNames() {
    std::vector<std::string> collectionNames;

    for (auto&& item : collections) {
        const std::string name{item->getName()};
        collectionNames.push_back(name);
    }

    return collectionNames;
}

void RestrApp::getDocumentNames(int idx, std::vector<std::string>& docEntries) {
    auto& collection = collections.at(idx);

    auto& requests = collection->getRequests();

    for (auto& item : requests) {
        const std::string requestName{item->getName()};
        docEntries.push_back(requestName);
    }
}

void RestrApp::fireRequest(const int collectionIndex, const int docIndex) {
    const auto& collection{collections.at(collectionIndex)};

    const auto& request{collection->getRequests().at(docIndex)};

    const auto result = request->execute();
}

// TODO: Remove the option param
void RestrApp::switchCollection(int& index, const ftxui::MenuOption& option,
                                std::vector<std::string>& entries) {
    entries.clear();
    getDocumentNames(index, entries);
}
void RestrApp::run() {
    auto screen{ftxui::App::Fullscreen()};

    std::vector<std::string> entries{getCollectionNames()};

    int selected{0};

    std::vector<std::string> documentEntries;

    getDocumentNames(selected, documentEntries);

    int documentSelected{0};

    ftxui::MenuOption menuOption;
    menuOption.on_change = [&]() {
        switchCollection(selected, menuOption, documentEntries);
    };
    auto menu = ftxui::Menu(&entries, &selected, menuOption);

    ftxui::MenuOption documentOption;
    documentOption.on_enter = [&]() {
        fireRequest(selected, documentSelected);
    };

    auto documentMenu =
        ftxui::Menu(&documentEntries, &documentSelected, documentOption);

    auto mainComponent = ftxui::Container::Horizontal({menu, documentMenu});

    auto uiRenderer = ftxui::Renderer(mainComponent, [&] {
        auto menuWin = menu->Render();
        auto docMenuWin = documentMenu->Render();

        return ftxui::vbox({
            ftxui::hbox(
                {ftxui::vbox({ftxui::text("API Collections"),
                              menuWin | ftxui::border | ftxui::flex}),
                 ftxui::vbox({ftxui::text("Requests"),
                              docMenuWin | ftxui::border | ftxui::flex}) |
                     ftxui::flex}) |
                ftxui::flex,
        });
    });

    screen.Loop(uiRenderer);
}
