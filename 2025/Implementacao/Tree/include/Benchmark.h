#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "../include/IDictionary.h"
#include <chrono>
#include <string>
#include <memory>
#include <vector>

class Benchmark {
public:
    struct Metrics {
        std::string structureName;
        std::string bookName;
        long time_ms;
        int comparisons;
        int insertions;
        int rotations;
        int collisions;
        int rehashes;
        float load_factor;
        size_t totalWords;
        size_t uniqueWords;
    };

    // Run benchmark for a specific dictionary
    Metrics run(IDictionary& dict, const std::vector<std::string>& words);

    // Print results to console
    void printResults(const Metrics& metrics) const;

    // Save results to CSV file
    void saveResults(const Metrics& metrics, const std::string& filename) const;

    std::string getBookNameFromPath(const std::string& path) const;
private:
};

#endif