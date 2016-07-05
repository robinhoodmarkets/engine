//
// Created by Donald Goodman-Wilson on 7/3/16.
//

#include "slack.h"

namespace slack
{

slack::slack(const std::string &token) : token_{token}, chat{this}
{ }

slack::slack(std::string &&token) : token_{std::move(token)}, chat{this}
{ }

std::string slack::token()
{
    return token_;
}

} //namespace