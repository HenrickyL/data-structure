#ifndef RB_DICTIONARY_H
#define RB_DICTIONARY_H

#include "IDictionary.h"
#include "RBTree.h"
#include <string>
#include <iostream>

using namespace Perikan::TREE;

class RBDictionary : public IDictionary {
private:
    RBTree<int, std::string>* _tree;
    int _comparisonCount;
    int _insertionCount;
    int _searchCount;

public:
    RBDictionary();
    ~RBDictionary();

    void add(const std::string& word) override;
    void remove(const std::string& word) override;
    bool constains(const std::string& key) const override;
    int size() const override;
    int count(const std::string& key) const override;

    int& operator[](const std::string key) override;
    const int& operator[](const std::string key) const override;
    //metrics
    int getComparisonCount() const override;
    int getInsertionCount() const override;
    int getSearchCount() const override;

    void resetMetrics() override;
    void printMetrics() const override;

    inline int getRotationCount() const { return _tree->getRotationCount(); }
    inline int getHeight() const { return _tree->height(); };
    inline int getCollisionCount() const { return -1; }
    inline int getRehashCount() const { return -1; } 
    inline int getLoadFactor() const { return -1; }
    inline std::string getName() const { return "RB Dictionary"; };
};

#endif
