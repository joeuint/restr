#include <memory>
#include <sstream>

#include "curlpp/Easy.hpp"
#include "curlpp/Infos.hpp"
#include "curlpp/Options.hpp"

#include "Request.hpp"

std::unique_ptr<Response> Request::execute() {
    std::stringstream ss;

    handle.setOpt(curlpp::Options::FollowLocation(true));
    handle.setOpt(curlpp::Options::WriteStream(&ss));

    handle.perform();

    std::string body = ss.str();

    auto statusCode = curlpp::infos::ResponseCode::get(handle);

    auto time = curlpp::infos::TotalTime::get(handle);

    auto ptr = std::make_unique<Response>(body, statusCode, time);

    return ptr;
}
