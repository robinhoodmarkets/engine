//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <string>
#include <slack/optional.hpp>
#include <map>
#include <memory>

namespace slack_private
{
struct json_impl;
}

namespace slack
{
namespace base
{

struct error
{
    static const std::string UNKNOWN;
    static const std::string JSON_PARSE_FAILURE;
    static const std::string INVALID_RESPONSE;
};

struct response2
{
    std::string raw_json;
    std::experimental::optional<std::string> error_message;

    operator bool()
    {
        return !static_cast<bool>(error_message); //if error contains a value, return false
    }
};

struct response
{
    response(const std::string &raw_json);
    ~response();

    std::string raw_json;
    std::experimental::optional<std::string> error;

    operator bool()
    {
        return !static_cast<bool>(error); //if error contains a value, return false
    }

protected:
    slack_private::json_impl* json_;
};

} //namespace base
} //namespace slack