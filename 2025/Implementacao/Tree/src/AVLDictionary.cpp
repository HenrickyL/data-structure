#include "../include/AVLDictionary.h"

AVLDictionary::AVLDictionary(){
    _tree = new AVLTree<int, std::string>();
}

AVLDictionary::~AVLDictionary() {
    _tree->clear();
    delete _tree;
}


void AVLDictionary::add(const std::string& word) {
    try {
        int& value = _tree->find(word);
        value += 1;
    }
    catch (const std::runtime_error& e) {
        // Se operator[] não criar a chave, fazemos add direto
        _tree->add(word, 1);
    }
}

void AVLDictionary::remove(const std::string& word) {
    _tree->remove(word);
}

bool AVLDictionary::constains(const std::string& key) const {
    return _tree->contains(key);
}

int AVLDictionary::size() const {
    return _tree->size();
}

int AVLDictionary::count(const std::string& key) const {
    return this->_tree->find(key);
}


int& AVLDictionary::operator[](const std::string key) {
    if (!_tree->contains(key)) {    // se n contem
        _tree->add(key, 0);         // adiciono com valor 0
    }
    return _tree->find(key);
}
const int& AVLDictionary::operator[](const std::string key) const {
    if (!_tree->contains(key)) {
        _tree->add(key, 0);
    }
    return _tree->find(key);
}


int AVLDictionary::getComparisonCount() const { return _tree->getComparisonCount(); }
int AVLDictionary::getInsertionCount() const { return _tree->getInsertionCount(); }
int AVLDictionary::getSearchCount() const { return _tree->getSearchCount();; }

void AVLDictionary::resetMetrics() {

    _tree->resetMetrics();
}

void AVLDictionary::printMetrics() const {
    std::cout << "AVL Dictionary Metrics:\n";
    std::cout << "  Insertions: " << getInsertionCount() << "\n";
    std::cout << "  Searches: " << getSearchCount() << "\n";
    std::cout << "  Comparisons: " << getComparisonCount() << "\n";
    std::cout << "  Rotations: " << _tree->rotationCount() << "\n";
    std::cout << "  Height: " << getHeight() << "\n";
}