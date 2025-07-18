#include "../include/Benchmark.h"
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <vector>
#include<iostream>
#include <fstream>

Benchmark::Metrics Benchmark::run(IDictionary& dict, const std::vector<std::string>& words) {
    // Reset metrics before starting
    dict.resetMetrics();

    auto start = std::chrono::high_resolution_clock::now();

    // Process all words
    for (const auto& word : words) {
        dict[word] = dict[word] + 1;
    }

    auto end = std::chrono::high_resolution_clock::now();

    // Prepare metrics
    Metrics metrics;
    metrics.structureName = dict.getName();
    metrics.bookName = "book"; // Will be set by controller
    metrics.time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    metrics.comparisons = dict.getComparisonCount();
    metrics.insertions = dict.getInsertionCount();
    metrics.rotations = dict.getRotationCount();
    metrics.collisions = dict.getCollisionCount();
    metrics.rehashes = dict.getRehashCount();
    metrics.load_factor = dict.getLoadFactor();
    metrics.totalWords = words.size();
    metrics.uniqueWords = dict.size();

    return metrics;
}

void Benchmark::printResults(const Metrics& metrics) const {
    std::cout << "\n=== " << metrics.structureName << " Results ===\n";
    std::cout << "Time (ms): " << metrics.time_ms << "\n";
    std::cout << "Comparisons: " << metrics.comparisons << "\n";
    std::cout << "Insertions: " << metrics.insertions << "\n";

    if (metrics.rotations >= 0) {
        std::cout << "Rotations: " << metrics.rotations << "\n";
    }

    if (metrics.collisions >= 0) {
        std::cout << "Collisions: " << metrics.collisions << "\n";
    }

    if (metrics.rehashes >= 0) {
        std::cout << "Rehashes: " << metrics.rehashes << "\n";
    }

    std::cout << "Load Factor: " << std::fixed << std::setprecision(2) << metrics.load_factor << "\n";
    std::cout << "Total Words: " << metrics.totalWords << "\n";
    std::cout << "Unique Words: " << metrics.uniqueWords << "\n";
    std::cout << "=========================\n";
}

void Benchmark::saveResults(const Metrics& metrics, const std::string& filename) const {
    std::ofstream out(filename.c_str());

    if (!out.is_open()) {
        throw std::runtime_error("Cannot open metrics file: " + filename);
    }

    // CSV header
    out << "structure,book,time_ms,comparisons,insertions,rotations,collisions,rehashes,load_factor,total_words,unique_words\n";

    // Data
    out << metrics.structureName << ","
        << metrics.bookName << ","
        << metrics.time_ms << ","
        << metrics.comparisons << ","
        << metrics.insertions << ","
        << metrics.rotations << ","
        << metrics.collisions << ","
        << metrics.rehashes << ","
        << std::fixed << std::setprecision(2) << metrics.load_factor << ","
        << metrics.totalWords << ","
        << metrics.uniqueWords << "\n";
}

std::string Benchmark::getBookNameFromPath(const std::string& path) const {
    size_t lastSlash = path.find_last_of("/\\");
    size_t lastDot = path.find_last_of('.');

    if (lastSlash == std::string::npos) lastSlash = 0;
    else lastSlash++;

    if (lastDot == std::string::npos || lastDot < lastSlash) {
        return path.substr(lastSlash);
    }

    return path.substr(lastSlash, lastDot - lastSlash);
}