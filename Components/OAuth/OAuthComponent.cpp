#include "OAuthComponent.hpp"
#include <userver/clients/http/component.hpp>
#include <userver/http/status_code.hpp>
#include <userver/server/http/http_request.hpp>

namespace daberdev::components {

OAuthComponent::OAuthComponent(const userver::components::ComponentConfig& config,
                               const userver::components::ComponentContext& context)
    : userver::components::LoggableComponentBase(config, context),
      m_redirect_url{config["redirect_url"].As<std::string>()},
      m_auth_url{config["auth_url"].As<std::string>()},
      m_token_url{config["token_url"].As<std::string>()},
      m_api_url{config["api_url"].As<std::string>()},
      m_client{&context.FindComponent<userver::components::HttpClient>().GetHttpClient()} {

          if(m_redirect_url.empty() && m_auth_url.empty() && m_token_url.empty() && m_api_url.empty()){
              throw std::runtime_error("OAuthComponent: redirect_url, auth_url, token_url, and api_url are cannot be empty");
          }

      }


void OAuthComponent::Auth(const userver::server::http::HttpRequest& req) {
    auto& response = req.GetHttpResponse();
    response.SetStatus(userver::http::StatusCode::kFound);
    response.SetHeader(std::string{"Location"},m_auth_url);
}

userver::yaml_config::Schema OAuthComponent::GetStaticConfigSchema() {
    return userver::yaml_config::MergeSchemas<userver::components::LoggableComponentBase>(R"(
    type: object
    description: OAuthComponent config
    additionalProperties: false
    properties:
        auth_url:
            type: string
            description: Authentication URL from provider
        redirect_url:
            type: string
            description: Redirect URL after authentication
        token_url:
            type: string
            description: Token URL from provider
        api_url:
            type: string
            description: API URL from provider
    )");
}

}
