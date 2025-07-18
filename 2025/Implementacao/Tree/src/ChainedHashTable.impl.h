#ifndef CHAINED_HASHTABLE_IMPL_HPP
#define CHAINED_HASHTABLE_IMPL_HPP


#include <cmath>       // sqrt (para primo)
#include <iostream>    // std::cout, std::endl (se usar para debug ou impressão)
#include "../include/ChainedHashTable.h"

namespace Perikan {namespace Hash {

template <typename Key, typename Value, typename Hash>
ChainedHashTable<Key, Value, Hash>::ChainedHashTable(size_t tableSize, float load_factor) {
    m_number_of_elements = 0;
    m_table_size = _get_next_prime(tableSize);
    m_table.resize(m_table_size);
    m_comparison_count = 0;
    m_collision_count = 0;
    m_insertion_count = 0;
    m_search_count = 0;
    m_rehash_count = 0;
    if (load_factor <= 0) {
        m_max_load_factor = 1.0;
    }
    else {
        m_max_load_factor = load_factor;
    }
}


template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::size() const {
    return m_number_of_elements;
}



template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::empty() const {
    return m_number_of_elements == 0;
}


template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::bucket_count() const {
    return m_table_size;
}


template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::bucket_size(size_t n) const {
    if (n >= m_table_size) {
        throw std::out_of_range("invalid index");
    }
    return m_table[n].size();
}


template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::bucket(const Key& k) const {
    return _hash_code(k);
}

template <typename Key, typename Value, typename Hash>
float ChainedHashTable<Key, Value, Hash>::load_factor() const {
    return static_cast<float>(m_number_of_elements) / m_table_size;
}

template <typename Key, typename Value, typename Hash>
float ChainedHashTable<Key, Value, Hash>::max_load_factor() const {
    return m_max_load_factor;
}


template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::clear() {
    for (size_t i = 0; i < m_table_size; ++i) {
        m_table[i].clear();
    }
    m_number_of_elements = 0;
}


template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::add(const Key& k, const Value& v) {
    if (load_factor() >= m_max_load_factor) {
        rehash(2 * m_table_size);
    }
    size_t slot = _hash_code(k);

    // Verifica se ja existe elemento no slot (potencial colisao)
    if (!m_table[slot].empty()) {
        m_collision_count++;
    }
    
    for (auto p : m_table[slot]) {
        m_comparison_count++;
        if (p.first == k) {
            return false;
        }
    }
    m_table[slot].push_back(std::make_pair(k, v));
    m_number_of_elements++;
    m_insertion_count++;
    return true;
}


template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::contains(const Key& k) {
    m_search_count++;
    size_t slot = _hash_code(k);

    for (auto& p : m_table[slot]) {
        m_comparison_count++;
        if (p.first == k) {
            return true;
        }
    }

    return false;
}




template <typename Key, typename Value, typename Hash>
Value& ChainedHashTable<Key, Value, Hash>::at(const Key& k) {
    m_search_count++;
    size_t slot = _hash_code(k);

    for (auto& p : m_table[slot]) {
        m_comparison_count++;
        if (p.first == k) {
            return p.second;
        }
    }
    throw std::out_of_range("key is not in the table");
}

template <typename Key, typename Value, typename Hash>
const Value& ChainedHashTable<Key, Value, Hash>::at(const Key& k) const {
    m_search_count++;
    size_t slot = _hash_code(k);

    for (auto& p : m_table[slot]) {
        m_comparison_count++;
        if (p.first == k) {
            return p.second;
        }
    }
    throw std::out_of_range("key is not in the table");
}


template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::rehash(size_t m) {
    m_rehash_count++;
    size_t new_table_size = _get_next_prime(m);
    if (new_table_size > m_table_size) {
        std::vector<std::vector<std::pair<Key, Value>>> old_vec;
        old_vec = m_table; // copia as chaves para uma nova tabela
        m_table.clear(); // apaga todas as chaves da tabela atual e deixa ela vazia
        m_table.resize(new_table_size); // tabela redimensionada com novo primo
        m_number_of_elements = 0;
        m_table_size = new_table_size;
        for (size_t i = 0; i < old_vec.size(); ++i) {
            for (auto& par : old_vec[i]) {
                add(par.first, par.second);
            }
            old_vec[i].clear(); // opcional
        }
    }
}


template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::remove(const Key& k) {
    size_t slot = _hash_code(k); // calcula o slot em que estaria a chave
    for (auto it = m_table[slot].begin(); it != m_table[slot].end(); ++it) {
        if (it->first == k) {
            m_table[slot].erase(it); // se encontrar, deleta
            m_number_of_elements--;
            return true;
        }
    }
    return false; // se não encontrar, retorna falso
}


template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::reserve(size_t n) {
    if (n > m_table_size * m_max_load_factor) {
        rehash(n / m_max_load_factor);
    }
}


template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::set_max_load_factor(float lf) {
    if (lf <= 0) {
        throw std::out_of_range("invalid load factor");
    }
    // se lf > 0, entao ok, ajusta o max_load_factor e chama reserve()
    m_max_load_factor = lf;
    reserve(m_number_of_elements);
}


template <typename Key, typename Value, typename Hash>
Value& ChainedHashTable<Key, Value, Hash>::operator[](const Key& k) {
    if (load_factor() >= m_max_load_factor) {
        rehash(2 * m_table_size);
    }
    size_t slot = _hash_code(k);
    for (auto& par : m_table[slot]) {
        if (par.first == k) {
            return par.second;
        }
    }
    m_table[slot].push_back({ k, Value() });
    m_number_of_elements++;
    return m_table[slot].back().second;
}


template <typename Key, typename Value, typename Hash>
const Value& ChainedHashTable<Key, Value, Hash>::operator[](const Key& k) const {
    return at(k);
}






template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::_get_next_prime(size_t x) {
    if (x <= 2) return 3;
    x = (x % 2 == 0) ? x + 1 : x;
    bool not_prime = true;
    while (not_prime) {
        not_prime = false;
        for (int i = 3; i <= sqrt(x); i += 2) {
            if (x % i == 0) {
                not_prime = true;
                break;
            }
        }
        x += 2;
    }
    return x - 2;
}


template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::_hash_code(const Key& k) const {
    return m_hashing(k) % m_table_size;
}

// Implemente os novos métodos
template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getComparisonCount() const {
    return m_comparison_count;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getCollisionCount() const {
    return m_collision_count;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getInsertionCount() const {
    return m_insertion_count;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getSearchCount() const {
    return m_search_count;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getRehashCount() const {
    return m_rehash_count;
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::resetMetrics() {
    m_comparison_count = 0;
    m_collision_count = 0;
    m_insertion_count = 0;
    m_search_count = 0;
    m_rehash_count = 0;
}



}}


#endif