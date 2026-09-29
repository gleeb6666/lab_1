#pragma once
#include <vector>
#include "domino.h"
#include "dominodealer.h"

class Chain {
public:
    explicit Chain(const Domino& first) : left_(first.low), right_(first.high) {}
    bool tryAttach(const Domino& d);

private:
    bool attachBy(int value, int other);

    int left_;
    int right_;
};

int playDeal(DominoDealer& dealer);
std::vector<int> playDeals(DominoDealer& dealer, int count);