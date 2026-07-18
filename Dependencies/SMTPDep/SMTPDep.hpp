#pragma once
#include "../../pch.hpp"
#include "../../Components/SMTP/SMTPClientComponent.hpp"

namespace userver::easy{
    class SMTPDep {
    public:
        explicit SMTPDep(const userver::components::ComponentContext& context);
        template<typename Self>
        bool SendEmail(this Self&& self, const std::string& to, const std::string& subject, const std::string& body) {
            return self.m_smtp_client->SendEmail(to, subject, body);
        }
        template<typename Self>
        void SendEmailAsync(this Self&& self,std::string to,std::string subject,std::string body) {
            return self.m_smtp_client->SendEmailAsync(to, subject, body);
        }
        static void RegisterOn(userver::easy::HttpBase& app);

    private:
        daberdev::components::SMTPClientComponent* m_smtp_client{nullptr};
    };
}
