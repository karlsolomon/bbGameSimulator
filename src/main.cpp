#include <algorithm>
#include <boost/program_options.hpp>
#include <boost/program_options/detail/parsers.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>
import Bases;
import Player;
import GameState;
namespace po = boost::program_options;

// Do Avg/StDev
template <typename T>
auto variance(const std::vector<T>& vec) -> T {
    const size_t sz = vec.size();
    if (sz <= 1) {
        return 0.0;  // shouldn't happen
    }

    // Calculate the mean
    T mean = std::accumulate(vec.begin(), vec.end(), 0.0) / sz;

    // Now calculate the variance
    auto variance_func = [&mean, &sz](T accumulator, const T& val) {
        return accumulator + ((val - mean) * (val - mean) / (sz - 1.0));
    };

    return std::accumulate(vec.begin(), vec.end(), 0.0, variance_func);
}

#define DEFAULT_NUM_GAMES 10

// Function to read a CSV file and store it in a 2D vector
auto readCSV(const std::string& filename) -> std::vector<std::vector<std::string>> {
    std::vector<std::vector<std::string>> table;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        table.push_back(row);
    }

    file.close();
    return table;
}

auto calculate_mean(const std::vector<int>& numbers) -> double {
    if (numbers.empty()) {
        return 0.0;  // shouldn't happen
    }
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
    return sum / static_cast<double>(numbers.size());
}

auto calculate_median(std::vector<int>& numbers) -> double {
    if (numbers.empty()) {
        return 0.0;  // shouldn't happen
    }
    std::sort(numbers.begin(), numbers.end());
    if (numbers.size() % 2 == 0) {
        return static_cast<double>(numbers[numbers.size() / 2 - 1] + numbers[numbers.size() / 2]) / 2.0;
    } else {
        return static_cast<double>(numbers[numbers.size() / 2]);
    }
}

auto main(int argc, char* argv[]) -> int {
    int numGames;
    std::string csv;
    po::options_description desc("Options");
    desc.add_options()("help,h", "Show help")("numGames,n", po::value<int>(&numGames)->required())(
        "file,f", po::value<std::string>(&csv)->required(), "CSV file");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }
    po::notify(vm);
    if (vm.count("file")) {
        csv = {vm["file"].as<std::string>()};
    }
    if (vm.count("numGames")) {
        numGames = vm["numGames"].as<int>();
    }
    std::println("Testing with {} game simulations", numGames);

    std::vector<std::vector<std::string>> table;
    try {
        table = readCSV(csv);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    std::vector<int> scores(numGames);
    std::vector<int> atBats(numGames);
    std::vector<Player> players;
    for (size_t i = 1; i < table.size(); i++) {
        players.emplace_back(table[i]);
    }

    GameState gs = GameState(players);
    for (int i = 0; i < numGames; i++) {
        std::pair<int, int> stats = gs.playGameGetRunsAtBats();
        scores[i] = stats.first;
        atBats[i] = stats.second;
    }
    std::println("{}", csv);
    std::println("Runs: {} +/- {}: med {}", calculate_mean(scores),
                 sqrt(variance(std::vector<double>(scores.begin(), scores.end()))), calculate_median(scores));
    std::println("AB  : {} +/- {}: med {}", calculate_mean(atBats),
                 sqrt(variance(std::vector<double>(atBats.begin(), atBats.end()))), calculate_median(atBats));
    return 0;
}
