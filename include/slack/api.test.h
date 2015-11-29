//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/base/response.h>
#include <slack/base/impl.h>

namespace slack
{
namespace api
{

//parameters
namespace parameter { namespace test {
MAKE_STRING_LIKE(error);
MAKE_STRING_LIKE(foo);
} }

//response
namespace response
{
namespace error
{
namespace test
{
const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
}
}

struct test :
        public slack::base::response
{
    test(const std::string &raw_json);

    std::experimental::optional<std::map<std::string, std::string>> args;
};
} //namespace response

//impl
namespace impl
{



class api :
        public slack::base::impl<slack::api::response::test>
{
public:
    //TODO can these be moved into the base class?
    response::test get_response();

    //TODO can we make a generic template?
    void set_option(const parameter::test::error &error)
    { error_ = error; }

    void set_option(parameter::test::error &&error)
    { error_ = std::move(error); }

    void set_option(const parameter::test::foo &foo)
    { foo_ = foo; }

    void set_option(parameter::test::foo &&foo)
    { foo_ = std::move(foo); }

private:
    std::experimental::optional<parameter::test::error> error_;
    std::experimental::optional<parameter::test::foo> foo_;
};

} //namespace impl

template<typename T>
void set_option(impl::api &impl, T &&t)
{
    impl.set_option(SLACK_FWD(t));
}

template<typename T, typename... Ts>
void set_option(impl::api &impl, T &&t, Ts &&... ts)
{
    set_option(impl, SLACK_FWD(t));
    set_option(impl, SLACK_FWD(ts)...);
}

template<typename ...Ts>
::slack::api::response::test test()
{
    class impl::api impl;
    return impl.get_response();
}

template<typename ...Ts>
::slack::api::response::test test(Ts &&...ts)
{
    class impl::api impl;
    set_option(impl, std::forward<Ts>(ts)...);
    return impl.get_response();
}

}
} //namespace slack