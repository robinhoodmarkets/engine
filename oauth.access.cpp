//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/oauth.access.h"
#include "private.h"
#include <vector>
#include <sstream>
#include <iostream>

namespace slack { namespace oauth
{

const std::string access::error::INVALID_CLIENT_ID = std::string{"invalid_client_id"};
const std::string access::error::BAD_CLIENT_SECRET = std::string{"bad_client_secret"};
const std::string access::error::INVALID_CODE = std::string{"invalid_code"};
const std::string access::error::BAD_REDIRECT_URI = std::string{"bad_redirect_uri"};

void access::initialize_()
{
    http::params params{
            {"client_id",     client_id_},
            {"client_secret", client_secret_},
            {"code",          code_}
    };

    if (redirect_uri_)
    {
        params.emplace("redirect_uri", *redirect_uri_);
    }

    auto result_ob = slack_private::get(this, "oauth.access", params);
    if (!this->error_message)
    {
        if (result_ob["access_token"].isString()) access_token = {result_ob["access_token"].asString()};
        if (result_ob["scope"].isString())
        {
            scopes = std::vector<scope>{};
            std::string s;
            std::istringstream f{result_ob["scope"].asString()};
            while (std::getline(f, s, ',')) {
                scopes->push_back(s);
            }
        }
        if (result_ob["team_name"].isString()) team_name = {result_ob["team_name"].asString()};
        if (result_ob["team_id"].isString()) team_id = {result_ob["team_id"].asString()};
    }
}

}} //namespace oauth slack