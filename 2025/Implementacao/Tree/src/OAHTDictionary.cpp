#include "../include/OAHTDictionary.h"
#include <functional> // Para std::hash
#include <iostream>

OAHTDictionary::OAHTDictionary()
    : _ht(new OpenAddressHashTable<std::string, int>()) {
}

OAHTDictionary::~OAHTDictionary() {
    delete _ht;
}

void OAHTDictionary::add(const std::string& word) {
    //int key = std::hash<std::string>{}(word);
    _ht->add(word, 1);
}

void OAHTDictionary::remove(const std::string& word) {
    //int key = std::hash<std::string>{}(word);
    _ht->remove(word);
}

bool OAHTDictionary::constains(const std::string& key) const {
    return _ht->contains(key);
}

int OAHTDictionary::size() const {
    return static_cast<int>(_ht->size());
}

int OAHTDictionary::count(const std::string& key) const {
    return _ht->contains(key) ? 1 : 0;
}

int& OAHTDictionary::operator[](const std::string key) {
    //int hashed_key = std::hash<std::string>{}(key);
    if (!_ht->contains(key)) {
        _ht->add(key, 0);
    }
    return _ht->at(key);
}

const int& OAHTDictionary::operator[](const std::string key) const {
    //int hashed_key = std::hash<std::string>{}(key);
    if (!_ht->contains(key)) {
        _ht->add(key, 0);
    }
    return _ht->at(key);
}

int OAHTDictionary::getComparisonCount() const {
    return static_cast<int>(_ht->getComparisonCount());
}

int OAHTDictionary::getInsertionCount() const {
    return static_cast<int>(_ht->getInsertionCount());
}

int OAHTDictionary::getSearchCount() const {
    return static_cast<int>(_ht->getSearchCount());
}

void OAHTDictionary::resetMetrics() {
    _ht->resetMetrics();
}

void OAHTDictionary::printMetrics() const {
    std::cout << "Metrics for " << getName() << ":\n";
    std::cout << " - Comparisons: " << getComparisonCount() << "\n";
    std::cout << " - Insertions: " << getInsertionCount() << "\n";
    std::cout << " - Searches: " << getSearchCount() << "\n";
    std::cout << " - Collisions: " << getCollisionCount() << "\n";
    std::cout << " - Rehashes: " << getRehashCount() << "\n";
    std::cout << " - Load Factor: " << getLoadFactor() << "\n";
}


std::vector<std::pair<std::string, int>> OAHTDictionary::getSortedEntries() const {
    return _ht->getSortedEntries();
}