//
// Created by D.E. Goodman-Wilson on 8/16/16.
//

#pragma once

#include <slack/event/events.h>
#include <slack/types.h>
#include <typeindex>
#include <string>
#include <vector>
#include <regex>
#include <utility>


namespace slack
{

struct http_event_envelope
{
    std::string token;
    slack::team_id team_id;
    std::string api_app_id;
    std::vector<user_id> authed_users;
};

class http_event_handler_callback
{
public:
    virtual ~http_event_handler_callback() = default;

    void exec(std::shared_ptr<slack::base::event> event, const http_event_envelope& envelope)
    {
        call(event, envelope);
    }

private:
    virtual void call(std::shared_ptr<slack::base::event>, const http_event_envelope&) = 0;
};


template<class EventT>
class http_event_handler_callback_template :
        public http_event_handler_callback
{
public:
    http_event_handler_callback_template(std::function<void(std::shared_ptr<EventT>, const http_event_envelope& envelope)> memFn) : function_(memFn)
    {};

    void call(std::shared_ptr<slack::base::event> event, const http_event_envelope& envelope)
    {
        function_(std::static_pointer_cast<EventT>(event), envelope);
    }

private:
    std::function<void(std::shared_ptr<EventT>, const http_event_envelope& envelope)> function_;
};

class http_event_client
{
public:
    using token_lookup_delegate = std::function<std::string(const std::string &)>;

    http_event_client(token_lookup_delegate delegate, std::string &&verification_token);

    http_event_client(token_lookup_delegate delegate, const std::string &verification_token);

    virtual ~http_event_client() = default;

    virtual std::string handle_event(const std::string &event);

    // event handlers
    template<class EventT>
    void on(std::function<void(std::shared_ptr<EventT>, const http_event_envelope &envelope)> handler);
    template<class EventT>
    void remove_on();
    void on_error(std::function<void(std::string message, std::string received)> handler);
    void remove_on_error();

    // message handlers
    struct message
    {
        std::string text;
        user_id from_user_id;
        channel_id channel_id;

        void reply(std::string text) const;

        std::string token;
        struct team_id team_id;
    };
    using hears_cb = std::function<void(const struct message &message)>;
    template<typename T>
    void hears(T &&message, hears_cb callback)
    {
        callbacks_.emplace_back(std::regex{std::forward<T>(message)}, callback);
    }

private:
    std::string verification_token_;
    using handler_map = std::map<std::type_index, std::unique_ptr<http_event_handler_callback>>;
    handler_map handlers_;
    std::function<void(std::string message, std::string received)> error_handler_;
    //let's just brute force this for now
    std::vector<std::pair<std::regex, hears_cb>> callbacks_;
    token_lookup_delegate token_lookup_;

    template <class Event>
    bool route_message_(const Event &message);
};


template<class EventT>
void http_event_client::on(std::function<void(std::shared_ptr<EventT>, const http_event_envelope &envelope)> func)
{
    handlers_[std::type_index{typeid(EventT)}] = std::unique_ptr<http_event_handler_callback>{
            new http_event_handler_callback_template<EventT>(func)};
}

//This feels...hackish? But it should work.
template<class EventT>
void http_event_client::remove_on()
{
    handlers_.erase(std::type_index{typeid(EventT)});
}
} //namespace slack
