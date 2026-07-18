#pragma once
#include "../../pch.hpp"

namespace userver::easy {
    class MySQLDep {
    public:
        explicit MySQLDep(const userver::components::ComponentContext& context);
        userver::storages::mysql::Cluster& mysql() const noexcept { return *mariadb_cluster_; }
        static void RegisterOn(userver::easy::HttpBase& app);

    private:
        std::shared_ptr<userver::storages::mysql::Cluster> mariadb_cluster_;
    };
}
