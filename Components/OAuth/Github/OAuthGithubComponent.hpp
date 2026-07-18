#include "../OAuthComponent.hpp"

namespace daberdev::components {

    class OAuthGithubComponent final : public OAuthComponent {
    public:
        explicit OAuthGithubComponent(const userver::components::ComponentConfig& config, const userver::components::ComponentContext& context)
        : OAuthComponent(config, context) {}
        static constexpr std::string_view kName{"daberdev-oauth-github-component"};
    };

}
