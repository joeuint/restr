#pragma once
#include <vector>

#include <ftxui/component/component_options.hpp>
#include "ApiCollection.hpp"

class RestrApp {
    const std::vector<std::unique_ptr<ApiCollection>> collections;

    void switchCollection(int& index, const ftxui::MenuOption& option, std::vector<std::string>& entries);
    std::vector<std::string> getCollectionNames();
    void getDocumentNames(int idx, std::vector<std::string>& docEntries);

public:

    RestrApp(std::vector<std::unique_ptr<ApiCollection>> collections): collections(std::move(collections)) {};

    void run();
};
