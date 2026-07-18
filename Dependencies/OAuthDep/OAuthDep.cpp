#include "OAuthDep.hpp"
namespace userver::easy{
    OAuthDep::OAuthDep(const userver::components::ComponentContext& context):
    m_oauth_component{&context.FindComponent<daberdev::components::OAuthComponent>()} {
    }

    void OAuthDep::RegisterOn(userver::easy::HttpBase& app) {
        app.TryAddComponent<daberdev::components::OAuthComponent>(
          daberdev::components::OAuthComponent::kName,
          "auth_url#env: OAUTH_AUTH_URL\n"\
          "token_url#env: OAUTH_TOKEN_URL\n"\
          "redirect_url#env: OAUTH_REDIRECT_URL\n"\
          "api_url#env: OAUTH_API_URL\n"
        );
    }
}
