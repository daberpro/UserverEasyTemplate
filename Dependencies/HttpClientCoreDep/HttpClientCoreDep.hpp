#pragma once
#include "../../pch.hpp"
#include <userver/clients/http/component_core.hpp>

namespace userver::easy {

    class HttpClientCoreDep {
    public:
        explicit HttpClientCoreDep(const userver::components::ComponentContext& context);
        static void RegisterOn(userver::easy::HttpBase& app);

    private:
        userver::components::HttpClientCore* m_http_client_core{nullptr};
    };

}
