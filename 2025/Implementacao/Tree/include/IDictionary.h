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
    virtual void reset_metrics() = 0;
    virtual void print_summary(std::ostream& out) const = 0;
};


#endif