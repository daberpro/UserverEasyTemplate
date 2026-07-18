#include "MySQLDep.hpp"

#include <userver/clients/dns/component.hpp>
#include <userver/storages/mysql/component.hpp>
#include <userver/storages/secdist/component.hpp>
#include <userver/storages/secdist/provider_component.hpp>

namespace userver::easy {

MySQLDep::MySQLDep(
    const userver::components::ComponentContext& context
)
    : mariadb_cluster_(
          context
              .FindComponent<userver::storages::mysql::Component>("mariadb")
              .GetCluster()
      )
{
    const auto& db_schema = userver::easy::HttpBase::GetDbSchema();

    if (!db_schema.empty()) {
        mariadb_cluster_->Execute(
            userver::storages::mysql::ClusterHostType::kPrimary,
            db_schema
        );
    }
}

void MySQLDep::RegisterOn(userver::easy::HttpBase& app)
{
    app.TryAddComponent<userver::components::DefaultSecdistProvider>(
        userver::components::DefaultSecdistProvider::kName,
        "config: ./secdist.json\n"
        "format: json\n"
    );

    app.TryAddComponent<userver::components::Secdist>(
        userver::components::Secdist::kName,
        "provider: default-secdist-provider\n"
    );

    app.TryAddComponent<userver::storages::mysql::Component>(
        "mariadb",
        "initial_pool_size: 1\n"
        "max_pool_size: 10\n"
        "use_secure_connection: false\n"
    );

    app.TryAddComponent<userver::clients::dns::Component>(
        userver::clients::dns::Component::kName,
        "fs-task-processor: fs-task-processor\n"
    );
}

}  // namespace userver::easy
