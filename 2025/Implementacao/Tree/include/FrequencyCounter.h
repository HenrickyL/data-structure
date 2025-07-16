#ifndef FREQUENCY_COUNTER_H
#define FREQUENCY_COUNTER_H

#include"../include/IDictionary.h"
#include"../include/AVLDictionary.h"
#include"../include/RBDictionary.h"

#include <chrono> //timer
#include <fstream> //archive
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

class FrequencyCounter {
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
    };

    static void RunAll(const std::string& bookPath, const std::string& outputDir) {
        std::vector<std::unique_ptr<IDictionary>> dictionaries;
        dictionaries.emplace_back(new AVLDictionary());
        dictionaries.emplace_back(new RBDictionary());
        //dictionaries.emplace_back(new ChainedHashDictionary());
        //dictionaries.emplace_back(new OpenAddressDictionary());

        for (auto& dict : dictionaries) {
            Metrics m = RunSingle(*dict, bookPath);
            SaveMetrics(m, outputDir);
        }
    }

private:
    static Metrics RunSingle(IDictionary& dict, const std::string& bookPath) {
        dict.resetMetrics();

        std::ifstream book(bookPath);
        std::string word;

        auto start = std::chrono::high_resolution_clock::now();

        while (book >> word) {
            std::string sanitized = SanitizeWord(word);
            if (!sanitized.empty()) {
                dict.add(sanitized); // Ou operator[] dependendo da interface
            }
        }

        auto end = std::chrono::high_resolution_clock::now();

        Metrics m;
        m.time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        m.comparisons = dict.getComparisonCount();
        // ... preencher outras métricas

        return m;
    }

    static std::string SanitizeWord(const std::string& word) {
        std::string result;
        std::copy_if(word.begin(), word.end(), std::back_inserter(result),
            [](char c) { return std::isalpha(c); });
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result.empty() ? "" : result;
    }

    static void SaveMetrics(const Metrics& m, const std::string& outputDir) {
        std::string filename = outputDir + "/" + m.structureName + "_" + m.bookName + "_metrics.csv";
        std::ofstream out(filename);

        out << "structure;book;time_ms;comparisons;insertions;rotations;collisions;rehashes;load_factor\n";
        out << m.structureName << ";"
            << m.bookName << ";"
            << m.time_ms << ";"
            << m.comparisons << ";"
            << m.insertions << ";"
            << m.rotations << ";"
            << m.collisions << ";"
            << m.rehashes << ";"
            << m.load_factor << "\n";
    }
};

#endif