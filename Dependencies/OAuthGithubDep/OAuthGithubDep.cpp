#include "OAuthGithubDep.hpp"

namespace userver::easy {
    OAuthGithubDep::OAuthGithubDep(const userver::components::ComponentContext& context):
    OAuthDep(context),
    m_oauth_component{&context.FindComponent<daberdev::components::OAuthGithubComponent>()} {
    }

    void OAuthGithubDep::RegisterOn(userver::easy::HttpBase &app){
        app.TryAddComponent<daberdev::components::OAuthGithubComponent>(
            daberdev::components::OAuthGithubComponent::kName,
            "auth_url#env: OAUTH_GITHUB_AUTH_URL\n"
            "token_url#env: OAUTH_GITHUB_TOKEN_URL\n"
            "redirect_url#env: OAUTH_GITHUB_REDIRECT_URL\n"
            "api_url#env: OAUTH_GITHUB_API_URL\n"
            "client_id#env: OAUTH_GITHUB_CLIENT_ID\n"
            "client_secret#env: OAUTH_GITHUB_CLIENT_SECRET\n"
            "scope#env: OAUTH_GITHUB_SCOPE\n"
        );
    }
}
