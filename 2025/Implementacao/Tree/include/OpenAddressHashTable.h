#ifndef OPEN_ADDRESS_HASH_TABLE_HPP
#define OPEN_ADDRESS_HASH_TABLE_HPP

#include <vector>
#include <functional>
#include <stdexcept>
#include <utility>
#include <cmath>
#include <optional>

namespace Perikan {namespace Hash {

template<typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenAddressHashTable {
private:
    enum SlotState { EMPTY, OCCUPIED, DELETED };

    size_t m_number_of_elements;
    size_t m_table_size;
    float m_max_load_factor;

    std::vector<std::pair<Key, Value>> m_table;
    std::vector<SlotState> m_state;

    Hash m_hashing;

public:
    OpenAddressHashTable(size_t tableSize = 19, float load_factor = 0.7);
    ~OpenAddressHashTable() = default;

    bool add(const Key& key, const Value& value);
    bool contains(const Key& key) const;
    Value& at(const Key& key);
    const Value& at(const Key& key) const;
    bool remove(const Key& key);

    Value& operator[](const Key& key);
    const Value& operator[](const Key& key) const;

    void clear();
    void rehash(size_t new_size);
    void reserve(size_t n);
    void set_max_load_factor(float lf);

    size_t size() const;
    bool empty() const;
    size_t capacity() const;
    float load_factor() const;
    float max_load_factor() const;

private:
    size_t _hash_code(const Key& key, size_t i = 0) const;
    size_t _get_next_prime(size_t x);
    size_t _find_slot(const Key& key) const;
    size_t _probe(const Key& key) const;
};

}} // namespace

#include"../src/OpenAddressHashTable.impl.h"
#endif
