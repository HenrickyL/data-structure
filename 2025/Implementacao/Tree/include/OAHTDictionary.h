#ifndef OAHT_DICTIONARY_H
#define OAHT_DICTIONARY_H

#include "IDictionary.h"
#include "OpenAddressHashTable.h"
#include <string>
using namespace Perikan::Hash;

class OAHTDictionary : public IDictionary{
private:
    OpenAddressHashTable<std::string, int>* _ht;


public:
    OAHTDictionary();
    ~OAHTDictionary();

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
    inline int getLoadFactor() const { return _ht->load_factor(); }       // Total de load_factor
    inline std::string getName() const { return "OpenAddressHashTable Dictionary"; };

    std::vector<std::pair<std::string, int>> getSortedEntries() const override;
};


#endif