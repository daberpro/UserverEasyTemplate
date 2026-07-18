#include "SMTPDep.hpp"

namespace userver::easy {
    SMTPDep::SMTPDep(const userver::components::ComponentContext& context)
        : m_smtp_client(&context.FindComponent<daberdev::components::SMTPClientComponent>())
    {
    }

    void SMTPDep::RegisterOn(userver::easy::HttpBase &app){
        app.TryAddComponent<daberdev::components::SMTPClientComponent>(
            daberdev::components::SMTPClientComponent::kName,
            "host: smtp.gmail.com\n"\
            "port: 587\n"\
            "email#env: SMTP_USER_EMAIL\n"\
            "password#env: SMTP_APP_PASSWORD\n"
        );
    }
}
