#pragma once
#include "../../pch.hpp"
#include <userver/clients/http/client.hpp>

namespace userver::easy {

    class HttpClientDep {
    public:
        explicit HttpClientDep(const userver::components::ComponentContext& context);
        static void RegisterOn(userver::easy::HttpBase& app);

        template <typename Self>
        userver::clients::http::Client& GetHttpClient(this Self& self){
            return *self.m_http_client;
        };
    private:
        userver::clients::http::Client* m_http_client{nullptr};
    };

}
