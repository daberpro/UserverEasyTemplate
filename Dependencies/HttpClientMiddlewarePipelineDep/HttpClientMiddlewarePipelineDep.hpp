#pragma once

#include <userver/components/component_context.hpp>
namespace userver::easy {
    class HttpClientMiddlewarePipelineDep {
    public:
        explicit HttpClientMiddlewarePipelineDep(const userver::components::ComponentContext&);
        static void RegisterOn(userver::easy::HttpBase&);
    private:
        userver::clients::http::MiddlewarePipelineComponent* m_pipeline{nullptr};
    };
}
