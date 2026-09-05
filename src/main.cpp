#include <curlpp/cURLpp.hpp>

#include "ApiCollection.hpp"
#include "Request.hpp"
#include "app.hpp"

void addSampleRequests(ApiCollection& collection) {
    auto request1 = std::make_unique<Request>("Example", RequestVerb::GET);
    request1->setUrl("https://example.com");

    // Gives ownership to the ApiCollection vector
    collection.addRequest(std::move(request1));

    auto request2 =
        std::make_unique<Request>("Example POST", RequestVerb::POST);
    request2->setUrl("https://example.com");

    // Gives ownership to the ApiCollection vector
    collection.addRequest(std::move(request2));
}

void addSampleRequests2(ApiCollection& collection) {
    auto request1 = std::make_unique<Request>("Example 2", RequestVerb::GET);
    request1->setUrl("https://example.com");

    // Gives ownership to the ApiCollection vector
    collection.addRequest(std::move(request1));

    auto request2 =
        std::make_unique<Request>("Example POST 2", RequestVerb::POST);
    request2->setUrl("https://example.com");

    // Gives ownership to the ApiCollection vector
    collection.addRequest(std::move(request2));
}

int main(void) {
    curlpp::initialize();

    auto collection = std::make_unique<ApiCollection>("Example Collection");
    auto collection2 = std::make_unique<ApiCollection>("Example Collection 2");

    addSampleRequests(*collection);
    addSampleRequests2(*collection2);

    std::vector<std::unique_ptr<ApiCollection>> collections;
    collections.push_back(std::move(collection));
    collections.push_back(std::move(collection2));

    RestrApp app(std::move(collections));
    app.run();
}
