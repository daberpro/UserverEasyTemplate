#pragma once
#include "../../Components/OAuth/OAuthComponent.hpp"
#include <userver/components/component_context.hpp>
#include <userver/server/http/http_request.hpp>

namespace userver::easy{
    class OAuthDep {
    public:
        explicit OAuthDep(const userver::components::ComponentContext&);
        static void RegisterOn(userver::easy::HttpBase& app);
        template <typename Self>
        void Auth(this Self&& self,const userver::server::http::HttpRequest& req) {
            if(self.m_oauth_component == nullptr){
                throw std::runtime_error("OAuth component not found");
            }
            self.m_oauth_component->Auth(req);
        }
    private:
        daberdev::components::OAuthComponent* m_oauth_component{nullptr};
    };
}
