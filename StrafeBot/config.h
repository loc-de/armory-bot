#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class Config {
private:
    Config() = default;
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;

    uintptr_t hex_to_ptr(const std::string& hex_str) {
        return static_cast<uintptr_t>(std::stoull(hex_str, nullptr, 16));
    }
	
public:
    struct Offsets {
        uintptr_t X;
        uintptr_t Y;
        uintptr_t Z;
        uintptr_t ROT;
    };
    Offsets offsets;

	std::string server_url;
	std::string graph_path;

    static Config& get() {
        static Config instance;
        return instance;
    }

    void load(const std::string& filename) {
        std::ifstream file(filename);
        nlohmann::json j;
        file >> j;

        offsets.X = hex_to_ptr(j["offsets"]["X"].get<std::string>());
        offsets.Y = hex_to_ptr(j["offsets"]["Y"].get<std::string>());
        offsets.Z = hex_to_ptr(j["offsets"]["Z"].get<std::string>());
        offsets.ROT = hex_to_ptr(j["offsets"]["ROT"].get<std::string>());

        server_url = j["server_url"];
        graph_path = j["graph_path"];
    }
};