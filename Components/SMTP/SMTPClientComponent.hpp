#pragma once
#include "../../pch.hpp"
namespace daberdev::components {
    class SMTPClientComponent final : public userver::components::LoggableComponentBase {
    public:
        static constexpr std::string_view kName{"daberdev-smtp-component-client"};
        SMTPClientComponent(
            const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context
        );

        bool SendEmail(
            const std::string& to,
            const std::string& subject,
            const std::string& body
        );

        void SendEmailAsync(
            std::string to,
            std::string subject,
            std::string body
        );

        static userver::yaml_config::Schema GetStaticConfigSchema();

    private:
        std::string m_host{};
        uint16_t m_port{};
        std::string m_email{};
        std::string m_password{};
        userver::concurrent::BackgroundTaskStorage m_background_tasks;

    };
}
