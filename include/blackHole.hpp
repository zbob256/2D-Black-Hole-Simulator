#pragma once

struct BlackHole {
    float distance;
    float angle;
    float schwarzschildRadius;
    float photonSphere;
    float accretionDisk;

    BlackHole(float distance, float angle, float schwarzschildRadius) {
        this->distance = distance;
        this->angle = angle;
        this->schwarzschildRadius = schwarzschildRadius;
        this->photonSphere = schwarzschildRadius * 1.5;
        this->accretionDisk = schwarzschildRadius * 3;
    }
};