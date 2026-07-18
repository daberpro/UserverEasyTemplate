#pragma once
#include "pch.hpp"
#include "Dependencies/MySQLDep/MySQLDep.hpp"
#include "Dependencies/SMTPDep/SMTPDep.hpp"
#include "Dependencies/OAuthDep/OAuthDep.hpp"
#include "Dependencies/HttpClientDep/HttpClientDep.hpp"
#include "Dependencies/HttpClientCoreDep/HttpClientCoreDep.hpp"

namespace userver::easy {

class AppDeps {
public:
    explicit AppDeps(const userver::components::ComponentContext& context)
        :
        db(context),
        smtp(context),
        oauth(context),
        httpClient(context),
        httpClientCore(context) {}

    static void RegisterOn(userver::easy::HttpBase& app) {
        userver::easy::HttpClientCoreDep::RegisterOn(app);
        userver::easy::HttpClientDep::RegisterOn(app);
        userver::easy::MySQLDep::RegisterOn(app);
        userver::easy::SMTPDep::RegisterOn(app);
        userver::easy::OAuthDep::RegisterOn(app);
    }

    userver::easy::MySQLDep db;
    userver::easy::SMTPDep smtp;
    userver::easy::OAuthDep oauth;
    userver::easy::HttpClientDep httpClient;
    userver::easy::HttpClientCoreDep httpClientCore;
};

}
