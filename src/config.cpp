#include "config.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "physics.hpp"

using json = nlohmann::json;

int WIDTH;
int HEIGHT;
long double UNIVERSE_SIZE;

std::vector<BlackHole> blackHoles;

void collectJSON() {
    std::ifstream configFile(CONFIG_DIR "/config.json");
    if (!configFile.is_open()) {
        std::cerr << "Failed to open config.json" << std::endl;
        return;
    }

    try {
        json config;
        configFile >> config;

        WIDTH = config.at("WIDTH").get<int>();
        HEIGHT = config.at("HEIGHT").get<int>();
        UNIVERSE_SIZE = config.at("UNIVERSE_SIZE").get<long double>();
    } catch (const json::exception& error) {
        std::cerr << "Failed to load config: " << error.what() << std::endl;
    }

    std::ifstream blackHoleFile(CONFIG_DIR "/blackHoleData.json");
    if (!blackHoleFile.is_open()) {
        std::cerr << "Failed to open blackHoleData.json" << std::endl;
    } else {
        try {
            json data;
            blackHoleFile >> data;

            for (auto& [name, info] : data.items()) {
                long double mass = info.at("solarMass").get<long double>() * SOLAR_MASS;
                float distance = info.at("distanceFromCenter").get<float>();
                float angle = info.at("degrees").get<float>();
                bool visible = info.at("show").get<bool>();

                BlackHole blackHole{distance, angle, mass, visible};
                blackHoles.push_back(blackHole);
            }
        } catch (const json::exception& error) {
            std::cerr << "Failed to load black hole data: " << error.what() << std::endl;
            blackHoles.clear();
        }
    }
}