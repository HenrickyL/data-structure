#include "../include/CHTDictionary.h"
#include <functional> // Para std::hash
#include <iostream>

CHTDictionary::CHTDictionary()
    : _ht(new ChainedHashTable<int, int>()) {
}

CHTDictionary::~CHTDictionary() {
    delete _ht;
}

void CHTDictionary::add(const std::string& word) {
    int key = std::hash<std::string>{}(word);
    _ht->add(key, 1);
}

void CHTDictionary::remove(const std::string& word) {
    int key = std::hash<std::string>{}(word);
    _ht->remove(key);
}

bool CHTDictionary::constains(const std::string& key) const {
    return _ht->contains(std::hash<std::string>{}(key));
}

int CHTDictionary::size() const {
    return static_cast<int>(_ht->size());
}

int CHTDictionary::count(const std::string& key) const {
    return _ht->contains(std::hash<std::string>{}(key)) ? 1 : 0;
}

int& CHTDictionary::operator[](const std::string key) {
    int hashed_key = std::hash<std::string>{}(key);
    if (!_ht->contains(hashed_key)) {
        _ht->add(hashed_key, 0);
    }
    return _ht->at(hashed_key);
}

const int& CHTDictionary::operator[](const std::string key) const {
    int hashed_key = std::hash<std::string>{}(key);
    if (!_ht->contains(hashed_key)) {
        _ht->add(hashed_key, 0);
    }
    return _ht->at(hashed_key);
}

int CHTDictionary::getComparisonCount() const {
    return static_cast<int>(_ht->getComparisonCount());
}

int CHTDictionary::getInsertionCount() const {
    return static_cast<int>(_ht->getInsertionCount());
}

int CHTDictionary::getSearchCount() const {
    return static_cast<int>(_ht->getSearchCount());
}

void CHTDictionary::resetMetrics() {
    _ht->resetMetrics();
}

void CHTDictionary::printMetrics() const {
    std::cout << "Metrics for " << getName() << ":\n";
    std::cout << " - Comparisons: " << getComparisonCount() << "\n";
    std::cout << " - Insertions: " << getInsertionCount() << "\n";
    std::cout << " - Searches: " << getSearchCount() << "\n";
    std::cout << " - Collisions: " << getCollisionCount() << "\n";
    std::cout << " - Rehashes: " << getRehashCount() << "\n";
    std::cout << " - Load Factor: " << getLoadFactor() << "\n";
}

// Métodos inline definidos no header:
// getRotationCount(), getCollisionCount(), getRehashCount(), getLoadFactor(), getName()