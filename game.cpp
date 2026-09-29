#include "Game.h"
#include <algorithm>
#include <iterator>

bool Chain::attachBy(int value, int other)
{
    if (left_ == value) {
        left_ = other;
        return true;
    }
    if (right_ == value) {
        right_ = other;
        return true;
    }
    return false;
}

bool Chain::tryAttach(const Domino& d)
{
    return attachBy(d.low, d.high) || attachBy(d.high, d.low);
}

int playDeal(DominoDealer& dealer)
{
    dealer.reset();

    Chain chain(dealer());
    int dealt = 1;

    while (!dealer.empty()) {
        Domino next = dealer();
        ++dealt;
        if (!chain.tryAttach(next))
            break;
    }
    return dealt;
}

std::vector<int> playDeals(DominoDealer& dealer, int count)
{
    std::vector<int> sizes;
    sizes.reserve(count);
    std::generate_n(std::back_inserter(sizes), count, [&dealer] { return playDeal(dealer); });
    return sizes;
}