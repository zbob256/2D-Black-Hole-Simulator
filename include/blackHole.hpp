#pragma once

#include "physics.hpp"
#include <cmath>

struct BlackHole {
    float distance;
    float angle;
    long double mass;
    long double schwarzschildRadius;
    long double photonSphere;
    long double accretionDisk;
    bool visible;

    BlackHole(float distance, float angle, long double mass, bool visible) {
        this->distance = distance;
        this->angle = angle * (M_PI / 180);
        this->mass = mass;
        this->schwarzschildRadius = calculateSchwarzschildRadius(mass);
        this->photonSphere = schwarzschildRadius * 1.5;
        this->accretionDisk = schwarzschildRadius * 3;
        this->visible = visible;
    }
};