#ifndef IDICTIONARY_H
#define IDICTIONARY_H

//Interface
#include<string>

class IDictionary {
public:
    virtual ~IDictionary() = default;

    virtual void add(const std::string& word) = 0;
    virtual void remove(const std::string& word) = 0;
    virtual bool constains(const std::string& key) const = 0;
    virtual int size() const = 0;
    virtual int count(const std::string& key) const = 0;
    //operator
    virtual int& operator[](const std::string key) = 0;
    virtual const int& operator[](const std::string key) const = 0;

    // Métricas básicas
    virtual int getComparisonCount() const = 0;  // Total de comparações realizadas
    virtual int getInsertionCount() const = 0;   // Total de inserções
    virtual int getSearchCount() const = 0;      // Total de buscas
    virtual void resetMetrics() = 0;             // Resetar todas as métricas
    virtual void printMetrics() const = 0;       // Exibir métricas
};


#endif