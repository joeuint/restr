#pragma once
#include <vector>

#include "ApiCollection.hpp"

class RestrApp {
    const std::vector<std::unique_ptr<ApiCollection>> collections;

    std::vector<std::string> getCollectionNames();

public:

    RestrApp(std::vector<std::unique_ptr<ApiCollection>> collections): collections(std::move(collections)) {};

    void run();
};
