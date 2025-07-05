#ifndef FREQUENCY_COUNTER_H
#define FREQUENCY_COUNTER_H

#include"../include/IDictionary.h"
#include <chrono> // time
#include <iostream>

class FrequencyCounter {
private:
    IDictionary* dictionary;
    std::chrono::duration<double> last_execution_time;

public:
    FrequencyCounter(IDictionary* dict) : dictionary(dict) {}

    void process(std::istream& in) {
        dictionary->reset_metrics();
        auto start = std::chrono::high_resolution_clock::now();

        std::string word;
        while (in >> word) { // ainda ver vem uma linha ou palavra, deve ser linha vou ter que fazer o split
            word = sanitize(word);
            if (word.empty()) continue;
            if (dictionary->constains(word)) {
                int c = dictionary->count(word);
                dictionary->remove(word);
                dictionary->add(word);  // com c + 1
            }
            else {
                dictionary->add(word); // com 1
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        last_execution_time = end - start;
    }

    void print_summary(std::ostream& out) const {
        out << "Tempo de execução: " << last_execution_time.count() << " segundos\n";
        dictionary->print_summary(out);
    }

    static std::string sanitize(const std::string& word) {
        //verificar acentos e caracteres especiais
        return word;
    }
};

#endif