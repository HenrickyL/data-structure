#include "../include/RBDictionary.h"

RBDictionary::RBDictionary() {
    _tree = new RBTree<int, std::string>();
}

RBDictionary::~RBDictionary() {
    _tree->clear();
    delete _tree;
}


void RBDictionary::add(const std::string& word) {
    try {
        int& value = _tree->find(word);
        value += 1;
    }
    catch (const std::runtime_error& e) {
        // Se operator[] não criar a chave, fazemos add direto
        _tree->add(word, 1);
    }
}

void RBDictionary::remove(const std::string& word) {
    _tree->remove(word);
}

bool RBDictionary::constains(const std::string& key) const {
    return _tree->contains(key);
}

int RBDictionary::size() const {
    return _tree->size();
}

int RBDictionary::count(const std::string& key) const {
    return this->_tree->find(key);
}


int& RBDictionary::operator[](const std::string key) {
    if (!_tree->contains(key)) {
        _tree->add(key, 0);
    }
    return _tree->find(key);
}
const int& RBDictionary::operator[](const std::string key) const {
    if (!_tree->contains(key)) {
        _tree->add(key, 0);
    }
    return _tree->find(key);
}
int RBDictionary::getComparisonCount() const { return _tree->getComparisonCount(); }
int RBDictionary::getInsertionCount() const { return _tree->getInsertionCount(); }
int RBDictionary::getSearchCount() const { return _tree->getSearchCount();; }

void RBDictionary::resetMetrics() {

    _tree->resetMetrics();
}

void RBDictionary::printMetrics() const {
    std::cout << "AVL Dictionary Metrics:\n";
    std::cout << "  Insertions: " << getInsertionCount() << "\n";
    std::cout << "  Searches: " << getSearchCount() << "\n";
    std::cout << "  Comparisons: " << getComparisonCount() << "\n";
    std::cout << "  Rotations: " << _tree->getRotationCount() << "\n";
    std::cout << "  Height: " << getHeight() << "\n";
}