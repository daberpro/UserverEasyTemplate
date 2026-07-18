#include "../../Components/OAuth/Github/OAuthGithubComponent.hpp"
#include "../OAuthDep/OAuthDep.hpp"
#include <userver/components/component_config.hpp>

namespace userver::easy {
    class OAuthGithubDep final : public OAuthDep{
    public:
        OAuthGithubDep(const userver::components::ComponentContext&);
        static void RegisterOn(userver::easy::HttpBase& app);
        daberdev::components::OAuthGithubComponent* m_oauth_component{nullptr};
    };
}
