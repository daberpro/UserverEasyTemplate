#include "HttpClientDep.hpp"

namespace userver::easy {

    HttpClientDep::HttpClientDep(const userver::components::ComponentContext& context) :
    m_http_client(&context.FindComponent<userver::components::HttpClient>().GetHttpClient()) {
    }

    void HttpClientDep::RegisterOn(userver::easy::HttpBase& app) {
        app.TryAddComponent<userver::components::HttpClient>(
            userver::components::HttpClient::kName,
            "core-component: http-client-core\n"
            "middlewares:\n"
            "# http-client-middleware-override:\n"
            "# enabled: true\n"
            "# http-client-middleware-additional:\n"
            "# enabled: true"
        );
    }

}
