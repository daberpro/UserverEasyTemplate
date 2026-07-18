#include "HttpClientMiddlewarePipelineDep.hpp"
#include <userver/clients/http/middlewares/pipeline_component.hpp>
namespace userver::easy {
    HttpClientMiddlewarePipelineDep::HttpClientMiddlewarePipelineDep(const userver::components::ComponentContext& context):
    m_pipeline{&context.FindComponent<userver::clients::http::MiddlewarePipelineComponent>()} {
    }

    void HttpClientMiddlewarePipelineDep::RegisterOn(userver::easy::HttpBase& app) {
        app.TryAddComponent<userver::clients::http::MiddlewarePipelineComponent>(
            userver::clients::http::MiddlewarePipelineComponent::kName,
            "middlewares: {}\n"
        );
    }
}
