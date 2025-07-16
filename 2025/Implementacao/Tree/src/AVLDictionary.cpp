#include "../include/AVLDictionary.h"

AVLDictionary::AVLDictionary(){
    _tree = new AVLTree<int, std::string>();
}

AVLDictionary::~AVLDictionary() {
    _tree->clear();
    delete _tree;
}


void AVLDictionary::add(const std::string& word) {
    if (constains(word)) {
        int value = count(word);
        _tree->remove(word);         // atualiza
        _tree->add(word, value + 1);
    }
    else {
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

void AVLDictionary::reset_metrics() {
    _tree->resetMetric();
}

void AVLDictionary::print_summary(std::ostream& out) const {
    out << "[AVL Summary]\n";
    out << "Comparações de chave: " << 0 << "\n";
    out << "Rotações (aprox.): " << 0 << "\n"; // ou real, se rastrear
    out << "Número total de palavras: " << size() << "\n";
}



int& AVLDictionary::operator[](const std::string key) {
    if (!_tree->contains(key)) {
        _tree->add(key, 0);
    }
    return _tree->find(key);
}
const int& AVLDictionary::operator[](const std::string key) const {
    if (!_tree->contains(key)) {
        _tree->add(key, 0);
    }
    return _tree->find(key);
}
