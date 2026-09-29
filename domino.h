#pragma once
#include <compare>

struct Domino {
    int low = 0;
    int high = 0;

    Domino() = default;
    Domino(int a, int b) : low(a < b ? a : b), high(a < b ? b : a) {}

    bool isDouble() const { return low == high; }

    auto operator<=>(const Domino&) const = default;
};