//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <json/json.h>


TEST(message, message_json_constructor)
{
    std::string raw_json = "{\"ok\":true,\"channel\":\"C01234567\",\"ts\":\"1448407807.000017\",\"message\":{\"text\":\"this is a api.test\",\"username\":\"bot\",\"type\":\"message\",\"subtype\":\"bot_message\",\"ts\":\"1448407807.000017\"}}";
    Json::Value result_ob;
    Json::Reader reader;
    bool parsed_success = reader.parse(raw_json, result_ob, false);
    ASSERT_TRUE(true);
    ASSERT_TRUE(parsed_success);
    auto ok = result_ob["ok"].asBool();
    ASSERT_TRUE(ok);
    slack::message m{result_ob["message"]};
    ASSERT_EQ(m.text, "this is a api.test");
}

//TODO we need to figure out the right way to manage incoming webhooks.
//TEST(incoming_webhooks, incoming_webhooks_basic)
//{
//    auto res = static_cast<std::string>(slack::incoming_webhook::payload{
//            "bar",
//            slack::incoming_webhook::payload::parameter::text{"bar"}
//    });
//    ASSERT_EQ("{\n\t\"text\" : \"bar\"\n}", res); //TODO the whitespace makes this fragile!
//}

//TEST(incoming_webhooks, incoming_webhooks_advanced)
//{
//    auto res = static_cast<std::string>(slack::incoming_webhook::payload{
//            "bar",
//            slack::incoming_webhook::payload::parameter::username{"baz"}
//    });
//    ASSERT_EQ("{\n\t\"text\" : \"bar\",\n\t\"username\" : \"baz\"\n}",
//              res); //TODO the ordering and whitespace makes this fragile!
//}
//
//TEST(incoming_webhooks, incoming_webhooks_attachments)
//{
//    slack::incoming_webhook::payload payload{
//            slack::incoming_webhook::payload::parameter::attachments{
//                    {slack::attachment::parameter::text{"text"}}
//            }
//    };
//    auto res = static_cast<std::string>(payload);
//    ASSERT_EQ("{\n\t\"attachments\" : \n\t[\n\t\t{\n\t\t\t\"text\" : \"text\"\n\t\t}\n\t]\n}",
//              res); //TODO the whitespace makes this fragile!
//}

