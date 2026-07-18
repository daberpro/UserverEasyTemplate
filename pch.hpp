#pragma once
#include <string>
#include <string_view>
#include <print>

// Framework Utama
#include <userver/easy.hpp>
#include <userver/http/content_type.hpp>
#include <userver/http/status_code.hpp>

// Komponen & Context
#include <userver/components/component.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/loggable_component_base.hpp>
#include <userver/clients/dns/component.hpp>
#include <userver/clients/dns/resolver.hpp>
#include <userver/concurrent/background_task_storage.hpp>
#include <userver/clients/http/client.hpp>
#include <userver/clients/http/component.hpp>


// Database & I/O
#include <userver/storages/mysql.hpp>
#include <userver/storages/mysql/cluster.hpp>
#include <userver/engine/io/socket.hpp>
#include <userver/engine/io/tls_wrapper.hpp>

// Format & Konfigurasi
#include <userver/formats/json/serialize.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/yaml_config/merge_schemas.hpp>
#include <userver/yaml_config/schema.hpp>

// Crypto
#include <userver/crypto/base64.hpp>
