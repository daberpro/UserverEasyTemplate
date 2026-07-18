#include "AppDeps.hpp"

struct User {
    std::string username{};
    std::string email{};
    int32_t id{};
};

[[maybe_unused]] User Parse(const userver::formats::json::Value& row) {
    return User{
        .username = row["username"].As<std::string>(),
        .email = row["email"].As<std::string>(),
        .id = row["id"].As<int32_t>(),
    };
}

[[maybe_unused]] userver::formats::json::Value Serialize(const User& user, userver::formats::serialize::To<userver::formats::json::Value>) {
    userver::formats::json::ValueBuilder result{};
    result["username"] = user.username;
    result["email"] = user.email;
    result["id"] = user.id;
    return result.ExtractValue();
}

int main(int argc, char** argv){

    userver::easy::HttpWith<userver::easy::AppDeps>(argc, argv)
        .DefaultContentType(userver::http::content_type::kApplicationJson)
        .Get("/test-auth",[](const userver::server::http::HttpRequest& req, const userver::easy::AppDeps& dep) -> std::string {
            dep.oauth.Auth(req);
            return {};
        })
        .Post(
            "/test-email",
            [](
                const userver::server::http::HttpRequest& req,
                const userver::easy::AppDeps& dep
            ) -> std::string {
                auto& response = req.GetHttpResponse();
                response.SetContentType(userver::http::content_type::kApplicationJson);

                if(req.GetHeader("Content-Type") != "application/json"){
                    response.SetStatus(userver::http::StatusCode::BadRequest);
                    userver::formats::json::ValueBuilder result{
                        userver::formats::json::Type::kObject
                    };
                    result["message"] = "Content-Type must be application/json";
                    return userver::formats::json::ToString(result.ExtractValue());
                }

                auto body = req.RequestBody();
                auto data = userver::formats::json::FromString(body);

                if(data.HasMember("subject") && data.HasMember("body") && data.HasMember("email")){
                    std::string subject = data["subject"].As<std::string>();
                    std::string body = data["body"].As<std::string>();
                    std::string email = data["email"].As<std::string>();

                    if(subject.empty() || body.empty() || email.empty()) {
                        userver::formats::json::ValueBuilder result{
                            userver::formats::json::Type::kObject
                        };
                        result["message"] = "Subject, body, and email are required";
                        return userver::formats::json::ToString(result.ExtractValue());
                    }

                    dep.smtp.SendEmailAsync(
                        email,
                        subject,
                        body
                    );

                    userver::formats::json::ValueBuilder result{
                        userver::formats::json::Type::kObject
                    };
                    result["message"] = "Email sent successfully";
                    return userver::formats::json::ToString(result.ExtractValue());
                }else{
                    userver::formats::json::ValueBuilder result{
                        userver::formats::json::Type::kObject
                    };
                    result["message"] = "Subject and body are required";
                    return userver::formats::json::ToString(result.ExtractValue());
                }

                userver::formats::json::ValueBuilder result{
                    userver::formats::json::Type::kObject
                };
                result["message"] = "Email sent successfully";
                return userver::formats::json::ToString(result.ExtractValue());
            }
        )
        .Get("/users", [](const userver::server::http::HttpRequest&, const userver::easy::AppDeps& dep) -> std::string {
            auto result_db = dep.db.mysql().Execute(
                userver::storages::mysql::ClusterHostType::kSecondary,
                "SELECT username, email, id FROM users"
            ).AsVector<User>();
            userver::formats::json::ValueBuilder result{
                userver::formats::json::Type::kArray
            };
            for(const auto& row: result_db) {
                result.PushBack(row);
            }
            return userver::formats::json::ToString(result.ExtractValue());
        })
        .Post("/users", [](const userver::server::http::HttpRequest& req, const userver::easy::AppDeps& dep) -> std::string {
            const auto& body = req.RequestBody();
            userver::formats::json::Value json = userver::formats::json::FromString(body);
            const auto& username = json["username"].As<std::string>();
            const auto& email = json["email"].As<std::string>();
            dep.db.mysql().Execute(
                userver::storages::mysql::ClusterHostType::kPrimary,
                "INSERT INTO users (username, email) VALUES (?, ?)",
                username, email
            );
            return userver::formats::json::ToString(json);
        })
        .Post("/users/delete/{id}", [](const userver::server::http::HttpRequest& req, const userver::easy::AppDeps& dep) -> std::string {
            const auto& id = req.GetPathArg("id");
            dep.db.mysql().Execute(
                userver::storages::mysql::ClusterHostType::kPrimary,
                "DELETE FROM users WHERE id = ?",
                id
            );
            std::print("User deleted {}", id);
            return std::format("User deleted {}", id);
        })
        .Put("/users/update/{id}", [](const userver::server::http::HttpRequest& req, const userver::easy::AppDeps& dep) -> std::string {
            const auto& id = req.GetPathArg("id");
            const auto& body = req.RequestBody();
            userver::formats::json::Value json = userver::formats::json::FromString(body);
            const auto& username = json["username"].As<std::string>();
            const auto& email = json["email"].As<std::string>();
            dep.db.mysql().Execute(
                userver::storages::mysql::ClusterHostType::kPrimary,
                "UPDATE users SET username = ?, email = ? WHERE id = ?",
                username, email, id
            );
            return userver::formats::json::ToString(json);
        })
        .LogLevel(userver::logging::Level::kError)
        .Port(3000);

    return 0;
}
