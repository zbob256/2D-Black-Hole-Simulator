#pragma once

struct BlackHole {
    float distance;
    float angle;
    float shawrzschildRadius;
    float photonSphere;
    float accretionDisk;

    BlackHole(float distance, float angle, float shawrzschildRadius) {
        this->distance = distance;
        this->angle = angle;
        this->shawrzschildRadius = shawrzschildRadius;
        this->photonSphere = shawrzschildRadius + 2;
        this->accretionDisk = shawrzschildRadius + 5;
    }
};