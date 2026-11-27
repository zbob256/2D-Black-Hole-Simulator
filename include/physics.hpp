#pragma once

constexpr long double G = 6.67430e-11;
constexpr long double C = 299792458.L;
constexpr long double SOLAR_MASS = 1.98847e30;

inline long double calculateSchwarzschildRadius(long double mass) {
    return (2.0L * G * mass) / (C * C);
}