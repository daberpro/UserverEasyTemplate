#include "HttpClientCoreDep.hpp"
#include <userver/clients/http/component_core.hpp>

namespace userver::easy {

    HttpClientCoreDep::HttpClientCoreDep(const userver::components::ComponentContext& context):
    m_http_client_core{&context.FindComponent<userver::components::HttpClientCore>()} {}

    void HttpClientCoreDep::RegisterOn(userver::easy::HttpBase& app) {
        app.TryAddComponent<userver::components::HttpClientCore>(
            userver::components::HttpClientCore::kName,
            "pool-statistics-disable: false\n"\
            "thread-name-prefix: http-client\n"\
            "threads: 2\n"\
            "fs-task-processor: fs-task-processor\n"\
            "destination-metrics-auto-max-size: 100\n"\
            "user-agent: common_component_list sample\n"\
        );
    }

}
