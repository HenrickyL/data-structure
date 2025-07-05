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

    void reset_metrics() override;
    void print_summary(std::ostream& out) const override;
};

#endif
