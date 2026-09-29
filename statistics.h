#pragma once
#include <compare>
#include <vector>

struct SizeFrequency {
    int size = 0;
    int count = 0;

    std::strong_ordering operator<=>(const SizeFrequency& other) const
    {
        if (auto cmp = count <=> other.count; cmp != 0)
            return cmp;
        return other.size <=> size;
    }
    bool operator==(const SizeFrequency&) const = default;
};

struct DealStatistics {
    std::vector<SizeFrequency> frequencies;
    int totalDeals = 0;
    int totalTiles = 0;
    int mostFrequentSize = 0;
    double averageSize = 0.0;
    double medianSize = 0.0;
};

DealStatistics computeStatistics(std::vector<int> sizes, int totalTiles);

void printStatistics(const DealStatistics& stats);