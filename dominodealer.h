#pragma once
#include <random>
#include <vector>
#include "domino.h"

class DominoDealer {
public:
    explicit DominoDealer(int n, unsigned seed = std::random_device{}());
    Domino operator()();

    void reset();

    bool empty() const { return pool_.empty(); }
    int maxValue() const { return n_; }
    int setSize() const { return static_cast<int>(fullSet_.size()); }

    static int setSizeFor(int n) { return (n + 1) * (n + 2) / 2; }

private:
    int n_;
    std::vector<Domino> fullSet_;
    std::vector<Domino> pool_;
    std::mt19937 gen_;
};