#include "dominodealer.h"
#include <stdexcept>
#include <string>

DominoDealer::DominoDealer(int n, unsigned seed) : n_(n), gen_(seed)
{
    if (n < 0)
        throw std::invalid_argument("n must be non-negative, got " + std::to_string(n));

    for (int a = 0; a <= n; ++a)
        for (int b = a; b <= n; ++b)
            fullSet_.emplace_back(a, b);

    reset();
}

void DominoDealer::reset()
{
    pool_ = fullSet_;
}

Domino DominoDealer::operator()()
{
    if (pool_.empty())
        throw std::out_of_range("no dominoes left in the pool");

    std::uniform_int_distribution<std::size_t> dist(0, pool_.size() - 1);
    std::size_t index = dist(gen_);

    Domino result = pool_[index];
    pool_[index] = pool_.back();
    pool_.pop_back();
    return result;
}