#pragma once

constexpr long double G = 6.67430e-11;
constexpr long double C = 299792458.L;
constexpr long double SOLAR_MASS = 1.98847e30;

inline long double calculateSchwarzschildRadius(long double mass) {
    long double meters = (2.L * G * mass) / (C * C);
    return meters / 1000.L;
}