#pragma once
#include "../../pch.hpp"

namespace daberdev::components {
    class OAuthComponent : public userver::components::LoggableComponentBase{
    public:
        static constexpr std::string_view kName{"daberdev-oauth-component"};

        OAuthComponent(const userver::components::ComponentConfig&,
                       const userver::components::ComponentContext&);
        void Auth(const userver::server::http::HttpRequest&);
        std::string GetToken(const userver::server::http::HttpRequest&);
        std::string GetData(const userver::server::http::HttpRequest&);
        static userver::yaml_config::Schema GetStaticConfigSchema();

    private:
        std::string m_auth_url;
        std::string m_token_url;
        std::string m_api_url;
        std::string m_redirect_url;

        std::string m_client_id;
        std::string m_client_secret;
        std::string m_scope;

        userver::clients::http::Client* m_client{nullptr};
    };
}
