#ifndef BENCHMARK_CONTROLLER_H
#define BENCHMARK_CONTROLLER_H

#include <string>
#include <memory>
#include <vector>
#include "../include/IDictionary.h"
#include "Benchmark.h"
#include "TextProcessor.h"

class BenchmarkController {
public:
    enum class DictionaryType {
        AVL,
        RED_BLACK,
        CHAINED_HASH,
        OPEN_HASH,
        ALL
    };

    struct RunConfig {
        DictionaryType dictType;
        std::string inputFile;
        std::string outputFile;
        bool benchmarkMode;
    };

    BenchmarkController();
    ~BenchmarkController() = default;

    // Main execution method
    void execute(int argc, char* argv[]);

private:
    // Configuration methods
    RunConfig parseArguments(int argc, char* argv[]) const;
    std::unique_ptr<IDictionary> createDictionary(DictionaryType type) const;
    std::string getDictionaryName(DictionaryType type) const;

    // Execution methods
    void runSingleBenchmark(DictionaryType type, const RunConfig& config);
    void runAllBenchmarks(const RunConfig& config);

    // Output methods
    void saveDictionaryResults(const IDictionary& dict, const std::string& filename) const;
    void saveBenchmarkResults(const Benchmark::Metrics& metrics, const std::string& filename) const;
    void printBenchmarkResults(const Benchmark::Metrics& metrics) const;

    // Dependencies
    TextProcessor textProcessor;
    Benchmark benchmark;
};

#endif