//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/event.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>


namespace slack { namespace event
{


struct hello :
        public base::event
{
    static const std::string type;
};


}} //namespace event slack