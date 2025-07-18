#ifndef IDICTIONARY_H
#define IDICTIONARY_H

//Interface
#include<string>

class IDictionary {
public:
    virtual ~IDictionary() = default;


    virtual std::string getName() const = 0;
    virtual void add(const std::string& word) = 0;
    virtual void remove(const std::string& word) = 0;
    virtual bool constains(const std::string& key) const = 0;
    virtual int size() const = 0;
    virtual int count(const std::string& key) const = 0;
    //operator
    virtual int& operator[](const std::string key) = 0;
    virtual const int& operator[](const std::string key) const = 0;

    // Métricas
    virtual int getComparisonCount() const = 0;  // Total de comparacoes realizadas
    virtual int getInsertionCount() const = 0;   // Total de insercoes
    virtual int getSearchCount() const = 0;      // Total de buscas
    virtual void resetMetrics() = 0;             // Resetar todas as metricas
    virtual void printMetrics() const = 0;       // Exibir metricas

    virtual int getRotationCount() const = 0;       // Total de rotacoes
    virtual int getCollisionCount() const = 0;       // Total de colisoes
    virtual int getRehashCount() const = 0;       // Total de rehash
    virtual int getLoadFactor() const = 0;       // Total de load_factor

    //virtual std::vector<std::pair<std::string, int>> getSortedEntries() const = 0;
};

#endif