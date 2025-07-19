#ifndef CHT_DICTIONARY_H
#define CHT_DICTIONARY_H

#include "IDictionary.h"
#include "ChainedHashTable.h"
#include <string>
using namespace Perikan::Hash;

class CHTDictionary : public IDictionary {
private:
    ChainedHashTable<std::string, int>* _ht;


public:
    CHTDictionary();
    ~CHTDictionary();

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

    inline int getHeight() const { return -1; };
    inline int getRotationCount() const { return -1; }       // Total de rotacoes
    inline int getCollisionCount() const { return _ht->getCollisionCount(); }       // Total de colisoes
    inline int getRehashCount() const { return _ht->getRehashCount(); }       // Total de rehash
    inline float getLoadFactor() const { return _ht->load_factor(); }       // Total de load_factor
    inline std::string getName() const { return "ChainedHashTable Dictionary"; };

    std::vector<std::pair<std::string, int>> getSortedEntries() const override;

};


#endif