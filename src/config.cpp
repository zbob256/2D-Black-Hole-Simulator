#include "config.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

// Defaults
int WIDTH = 800;
int HEIGHT = 800;
long double UNIVERSE_SIZE = 1e8L;

void collectJSON() {
    std::ifstream file(CONFIG_DIR "/config.json");

    if (!file.is_open()) {
        std::cerr << "Failed to open config.json\n";
        return;
    }

    json config;
    file >> config;

    WIDTH = config.at("WIDTH").get<int>();
    HEIGHT = config.at("HEIGHT").get<int>();
    UNIVERSE_SIZE = config.at("UNIVERSE_SIZE").get<long double>();
}