#pragma once

#include <string>
#include <vector>

#include "Request.hpp"

class ApiCollection {
    const std::string name;
    // TODO: Use a unique ptr and pass in via constructor
    std::vector<std::unique_ptr<Request>> reqs;

   public:
    ApiCollection(const std::string& name) : name(name) {};

    void addRequest(std::unique_ptr<Request> req) {
        reqs.push_back(std::move(req));
    }

    const std::vector<std::unique_ptr<Request>>& getRequests() { return reqs; }

    std::string_view getName() const { return name; }
};
