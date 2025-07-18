#ifndef AVL_DICTIONARY_H
#define AVL_DICTIONARY_H

#include "IDictionary.h"
#include "AVLTree.h"
#include <string>
#include <iostream>

using namespace Perikan::TREE;

class AVLDictionary : public IDictionary {
private:
    AVLTree<int, std::string>* _tree;

public:
    AVLDictionary();
    ~AVLDictionary();

    void add(const std::string& word) override;
    void remove(const std::string& word) override;
    bool constains(const std::string& key) const override;
    int size() const override;
    int count(const std::string& key) const override;

    int& operator[](const std::string key) override;
    const int& operator[](const std::string key) const override;


    int getComparisonCount() const override;
    int getInsertionCount() const override;
    int getSearchCount() const override;

    void resetMetrics() override;
    void printMetrics() const override;

    inline int getRotationCount() const { return _tree->getRotationCount(); }       // Total de rotacoes
    inline int getHeight() const { return _tree->height(); };
    inline int getCollisionCount() const { return -1; }       // Total de colisoes
    inline int getRehashCount() const { return -1; }       // Total de rehash
    inline float getLoadFactor() const { return -1.0f; }       // Total de load_factor
    inline std::string getName() const { return "AVL Dictionary"; };

    std::vector<std::pair<std::string, int>> getSortedEntries() const override;
};

#endif
