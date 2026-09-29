#include "statistics.h"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>

namespace {

int minPossibleSize(int totalTiles)
{
    return totalTiles == 1 ? 1 : 2;
}

double median(std::vector<int>& sorted)
{
    std::size_t mid = sorted.size() / 2;
    if (sorted.size() % 2 == 1)
        return sorted[mid];
    return (sorted[mid - 1] + sorted[mid]) / 2.0;
}

}

DealStatistics computeStatistics(std::vector<int> sizes, int totalTiles)
{
    if (sizes.empty())
        throw std::invalid_argument("no deals to analyze");

    DealStatistics stats;
    stats.totalDeals = static_cast<int>(sizes.size());
    stats.totalTiles = totalTiles;

    for (int s = minPossibleSize(totalTiles); s <= totalTiles; ++s) {
        int cnt = static_cast<int>(std::ranges::count(sizes, s));
        stats.frequencies.push_back({s, cnt});
    }

    stats.mostFrequentSize = std::ranges::max(stats.frequencies).size;

    long long sum = std::accumulate(sizes.begin(), sizes.end(), 0LL, std::plus<>{});
    stats.averageSize = static_cast<double>(sum) / stats.totalDeals;

    std::ranges::sort(sizes, std::less<>{});
    stats.medianSize = median(sizes);

    return stats;
}

void printStatistics(const DealStatistics& stats)
{
    std::cout << "\nTotal tiles in set: " << stats.totalTiles
              << ", deals made: " << stats.totalDeals << "\n\n";
    std::cout << std::setw(6) << "Size" << std::setw(12) << "Deals" << std::setw(12) << "Percent" << '\n';
    std::cout << std::string(30, '-') << '\n';

    std::cout << std::fixed << std::setprecision(3);
    for (const auto& [size, count] : stats.frequencies) {
        double percent = 100.0 * count / stats.totalDeals;
        std::cout << std::setw(6) << size << std::setw(12) << count << std::setw(11) << percent << "%\n";
    }

    std::cout << std::string(30, '-') << '\n';
    std::cout << "Most frequent size: " << stats.mostFrequentSize << '\n';
    std::cout << "Average size:       " << stats.averageSize << '\n';
    std::cout << "Median size:        " << stats.medianSize << '\n';
}