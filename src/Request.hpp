#pragma once
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <memory>
#include <string>

enum class RequestVerb {
    GET,
    POST,
    PUT,
    PATCH,
    DELETE,
};

class Response {
   public:
    std::string body;
    int statusCode;
    double time;

    Response(std::string body, int statusCode, double time)
        : body(body), statusCode(statusCode), time(time) {};

    std::string_view getBody() { return body; }

    int getStatusCode() { return statusCode; }

    double getTime() { return time; }
};

class Request {
    std::string name;
    RequestVerb verb;
    curlpp::Easy handle;

   public:
    Request(const std::string& name, RequestVerb verb)
        : name(name), verb(verb) {};

    void setUrl(const std::string& url) {
        handle.setOpt(curlpp::Options::Url(url));
    }

    std::string getUrl() {
        curlpp::options::Url url;
        handle.getOpt(&url);

        return url.getValue();
    }

    std::string_view getName() { return name; }

    RequestVerb getVerb() { return verb; }

    std::unique_ptr<Response> execute();
};
