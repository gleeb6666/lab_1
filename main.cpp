// Компілятор: GCC 13.3 (g++ -std=c++23)
#include <charconv>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include "dominodealer.h"
#include "game.h"
#include "statistics.h"

namespace {

constexpr int MAX_N = 20;
constexpr int MAX_DEALS = 1'000'000;

int readInt(const std::string& prompt, int minValue, int maxValue)
{
    while (true) {
        std::cout << prompt << " [" << minValue << ".." << maxValue << "]: ";

        std::string line;
        if (!std::getline(std::cin, line))
            throw std::runtime_error("input ended unexpectedly");

        auto first = line.find_first_not_of(" \t\r");
        auto last = line.find_last_not_of(" \t\r");
        if (first == std::string::npos) {
            std::cout << "Error: empty input. Try again.\n";
            continue;
        }

        const char* begin = line.data() + first;
        const char* end = line.data() + last + 1;
        int value = 0;
        auto [ptr, ec] = std::from_chars(begin, end, value);

        if (ec == std::errc::result_out_of_range)
            std::cout << "Error: number is too big. Try again.\n";
        else if (ec != std::errc{} || ptr != end)
            std::cout << "Error: \"" << line << "\" is not an integer. Try again.\n";
        else if (value < minValue || value > maxValue)
            std::cout << "Error: value must be in range [" << minValue << ".." << maxValue << "]. Try again.\n";
        else
            return value;
    }
}

void runExperiment(int maxN, int deals)
{
    std::cout << "\nExperiment: ratio of average/median deal size to the number of tiles\n";
    std::cout << "(" << deals << " deals for every n)\n\n";
    std::cout << std::setw(4) << "n" << std::setw(8) << "tiles" << std::setw(11) << "average"
              << std::setw(10) << "median" << std::setw(13) << "avg/tiles" << std::setw(13) << "med/tiles" << '\n';
    std::cout << std::string(59, '-') << '\n';

    auto statsFor = [deals](int n) {
        DominoDealer dealer(n);
        return computeStatistics(playDeals(dealer, deals), dealer.setSize());
    };

    for (int n = 0; n <= maxN; ++n) {
        DealStatistics s = statsFor(n);
        std::cout << std::setw(4) << n << std::setw(8) << s.totalTiles
                  << std::setw(11) << s.averageSize << std::setw(10) << s.medianSize
                  << std::setw(13) << s.averageSize / s.totalTiles
                  << std::setw(13) << s.medianSize / s.totalTiles << '\n';
    }
}

}

int main()
{
    try {
        int n = readInt("Enter n (max number on a tile)", 0, MAX_N);
        int deals = readInt("Enter number of deals", 1, MAX_DEALS);

        DominoDealer dealer(n);
        DealStatistics stats = computeStatistics(playDeals(dealer, deals), dealer.setSize());
        printStatistics(stats);

        runExperiment(n, deals);
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
        return 0;
    }
    return 0;
}