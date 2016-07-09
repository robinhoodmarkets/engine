//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/fwd.h>
#include <slack/set_option.h>
#include <string>
#include <vector>
#include <map>
#include <slack/optional.hpp>


#define MAKE_STRING_LIKE(x) class x : public std::string \
{ \
public: \
    x() = default; \
    x(const x &rhs) = default; \
    x(x &&rhs) = default; \
    x &operator=(const x &rhs) = default; \
    x &operator=(x &&rhs) = default; \
    x(const char *raw_string) : std::string(raw_string) {} \
    x(const char *raw_string, size_t length) : std::string(raw_string, length) {} \
    explicit x(size_t to_fill, char character) : std::string(to_fill, character) {} \
    x(const std::string &std_string) : std::string(std_string) {} \
    x(const std::string &std_string, size_t position, size_t length = std::string::npos) \
        : std::string(std_string, position, length) {} \
    explicit x(std::initializer_list<char> il) : std::string(il) {} \
    template<class InputIterator> \
    explicit x(InputIterator first, InputIterator last) \
        : std::string(first, last) {} \
}

#define MAKE_BOOL_LIKE(x) class x \
{ \
public: \
    x() = default; \
    x(const x &rhs) = default; \
    x(x &&rhs) = default; \
    x &operator=(const x &rhs) = default; \
    x &operator=(x &&rhs) = default; \
    x(bool new_val) : value{new_val} {} \
    x & operator=(bool && new_value) {value = new_value;} \
    explicit operator bool() {return value;} \
private: \
    bool value; \
}

#define MAKE_LONG_LONG_LIKE(x) class x\
{ \
public: \
    x() = default; \
    x(const x &rhs) = default; \
    x(x &&rhs) = default; \
    x &operator=(const x &rhs) = default; \
    x &operator=(x &&rhs) = default; \
    x(long long new_val) : value{new_val} {} \
    x & operator=(long long && new_value) {value = new_value;} \
    explicit operator long long() {return value;} \
private: \
    long long value; \
}

namespace slack
{

//TODO NONE of these things should be just strings.

MAKE_STRING_LIKE(team_id);

MAKE_STRING_LIKE(user_id);

MAKE_STRING_LIKE(bot_id);

MAKE_STRING_LIKE(ts);

MAKE_STRING_LIKE(channel_id);

MAKE_STRING_LIKE(token);

MAKE_STRING_LIKE(scope);

struct profile
{
    profile() = default;

    template<class json>
    profile(const json &parsed_json);

    std::string first_name;
    std::string last_name;
    std::string real_name;
    std::string email;
    std::string skype;
    std::string phone;
    std::map<uint16_t, std::string> images;
};

struct user
{
    user() = default;

    template<class json>
    user(const json &parsed_json);

    user_id id;
    std::string name;
    bool deleted;
    std::string color; //TODO would be nice to have a color class!
    slack::profile profile;
    bool is_admin;
    bool is_onwer;
    bool has_2fa;
    bool has_files;
};

//This is the data type that is returned from a slash command
struct command
{
    command() = default;

    command(const std::map<std::string, std::string> &params);

    std::string token; // gIkuvaNzQIHg97ATvDxqgjtO
    slack::team_id team_id; // T0001
    std::string team_domain; // example
    slack::channel_id channel_id; // C2147483705
    std::string channel_name; // test
    slack::user_id user_id; // U2147483697
    std::string user_name; // Steve
    std::string command_name; // /weather
    std::string text; // 94070
    std::string response_url; // https://hooks.slack.com/commands/1234/5678
};

struct reaction
{
    reaction() = default;

    template<class json>
    reaction(const json &parsed_json);

    std::string name;
    int64_t count;
    std::vector<user_id> users;
};

}