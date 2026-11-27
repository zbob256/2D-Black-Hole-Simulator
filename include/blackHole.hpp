#pragma once

#include "physics.hpp"
#include <cmath>

const long double UNIVERSE_SIZE_KM = 1e11;

struct BlackHole {
    float distance;
    float angle;
    long double mass;
    long double schwarzschildRadius;
    long double photonSphere;
    long double accretionDisk;

    BlackHole(float distance, float angle, long double mass) {
        this->distance = distance;
        this->angle = angle * (M_PI / 180);
        this->mass = mass;
        this->schwarzschildRadius = calculateSchwarzschildRadius(mass) / UNIVERSE_SIZE_KM;
        this->photonSphere = schwarzschildRadius * 1.5;
        this->accretionDisk = schwarzschildRadius * 3;
    }
};