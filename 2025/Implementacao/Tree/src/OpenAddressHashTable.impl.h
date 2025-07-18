#ifndef OPEN_ADDRESS_HASH_TABLE_IMPL_HPP
#define OPEN_ADDRESS_HASH_TABLE_IMPL_HPP

#include "../include/OpenAddressHashTable.h"
#include <cmath>

namespace Perikan {namespace Hash {

template<typename Key, typename Value, typename Hash>
OpenAddressHashTable<Key, Value, Hash>::OpenAddressHashTable(size_t tableSize, float load_factor)
    : m_number_of_elements(0),
    m_max_load_factor(load_factor),
    m_table_size(_get_next_prime(tableSize)),
    m_table(m_table_size),
    m_state(m_table_size, EMPTY),
    m_hashing(Hash()),
    m_comparison_count(0),
    m_insertion_count(0),
    m_search_count(0),
    m_collision_count(0),
    m_rehash_count(0)
{
}


// Auxiliar: verifica se um numero é primo
static bool _is_prime(size_t x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (size_t i = 3; i <= std::sqrt(x); i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

// Retorna o proximo primo >= x
template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashTable<Key, Value, Hash>::_get_next_prime(size_t x) {
    while (!_is_prime(x)) ++x;
    return x;
}

// Função de hash com sondagem linear
template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashTable<Key, Value, Hash>::_hash_code(const Key& key, size_t i) const {
    return (m_hashing(key) + i) % m_table_size;
}

// Inserção
template<typename Key, typename Value, typename Hash>
bool OpenAddressHashTable<Key, Value, Hash>::add(const Key& key, const Value& value) {
    if (load_factor() >= m_max_load_factor) {
        rehash(2 * m_table_size);
    }
    bool has_collided = false;
    for (size_t i = 0; i < m_table_size; ++i) {
        size_t idx = _hash_code(key, i);
        m_comparison_count++;
        if (m_state[idx] == EMPTY || m_state[idx] == DELETED) {
            if (has_collided) {
                m_collision_count++; // Conta como colisao se houve tentativa anterior
            }
            m_table[idx] = std::make_pair(key, value);
            m_state[idx] = OCCUPIED;
            ++m_number_of_elements;
            m_insertion_count++;
            return true;
        }
        else if (m_state[idx] == OCCUPIED && m_table[idx].first == key) {
            return false; // chave ja existe
        }
        // Marca que houve colisão para proximas iteracoes
        has_collided = true;
    }
    return false; // tabela cheia
}

// Busca
template<typename Key, typename Value, typename Hash>
bool OpenAddressHashTable<Key, Value, Hash>::contains(const Key& key) const {
    m_search_count++;
    for (size_t i = 0; i < m_table_size; ++i) {
        size_t idx = _hash_code(key, i);
        m_comparison_count++;
        if (m_state[idx] == EMPTY) return false;
        if (m_state[idx] == OCCUPIED && m_table[idx].first == key) return true;
    }
    return false;
}

// Remoção
template<typename Key, typename Value, typename Hash>
bool OpenAddressHashTable<Key, Value, Hash>::remove(const Key& key) {
    for (size_t i = 0; i < m_table_size; ++i) {
        size_t idx = _hash_code(key, i);
        if (m_state[idx] == EMPTY) return false;
        if (m_state[idx] == OCCUPIED && m_table[idx].first == key) {
            m_state[idx] = DELETED;
            --m_number_of_elements;
            return true;
        }
    }
    return false;
}

// Acesso com exceção
template<typename Key, typename Value, typename Hash>
Value& OpenAddressHashTable<Key, Value, Hash>::at(const Key& key) {
    m_search_count++;
    for (size_t i = 0; i < m_table_size; ++i) {
        size_t idx = _hash_code(key, i);
        m_comparison_count++;
        if (m_state[idx] == EMPTY) break;
        if (m_state[idx] == OCCUPIED && m_table[idx].first == key) {
            return m_table[idx].second;
        }
    }
    throw std::out_of_range("Key not found");
}

// Versão const de at
template<typename Key, typename Value, typename Hash>
const Value& OpenAddressHashTable<Key, Value, Hash>::at(const Key& key) const {
    m_search_count++;
    for (size_t i = 0; i < m_table_size; ++i) {
        size_t idx = _hash_code(key, i);
        m_comparison_count++;
        if (m_state[idx] == EMPTY) break;
        if (m_state[idx] == OCCUPIED && m_table[idx].first == key) {
            return m_table[idx].second;
        }
    }
    throw std::out_of_range("Key not found");
}

// operator[]
template<typename Key, typename Value, typename Hash>
Value& OpenAddressHashTable<Key, Value, Hash>::operator[](const Key& key) {
    if (load_factor() >= m_max_load_factor) {
        rehash(2 * m_table_size);
    }
    for (size_t i = 0; i < m_table_size; ++i) {
        size_t idx = _hash_code(key, i);

        if (m_state[idx] == EMPTY || m_state[idx] == DELETED) {
            m_table[idx] = std::make_pair(key, Value());
            m_state[idx] = OCCUPIED;
            ++m_number_of_elements;
            return m_table[idx].second;
        }
        if (m_state[idx] == OCCUPIED && m_table[idx].first == key) {
            return m_table[idx].second;
        }
    }
    throw std::runtime_error("Hash table overflow");
}

// const operator[]
template<typename Key, typename Value, typename Hash>
const Value& OpenAddressHashTable<Key, Value, Hash>::operator[](const Key& key) const {
    return at(key);
}

// clear
template<typename Key, typename Value, typename Hash>
void OpenAddressHashTable<Key, Value, Hash>::clear() {
    for (size_t i = 0; i < m_table_size; ++i) {
        m_state[i] = EMPTY;
        m_table[i] = std::pair<Key, Value>(); // reset do par (default)
    }
    m_number_of_elements = 0;
}

// reserve
template<typename Key, typename Value, typename Hash>
void OpenAddressHashTable<Key, Value, Hash>::reserve(size_t n) {
    if (n > m_table_size * m_max_load_factor) {
        rehash(static_cast<size_t>(n / m_max_load_factor));
    }
}

// set_max_load_factor
template<typename Key, typename Value, typename Hash>
void OpenAddressHashTable<Key, Value, Hash>::set_max_load_factor(float lf) {
    if (lf <= 0) throw std::out_of_range("Invalid load factor");
    m_max_load_factor = lf;
    reserve(m_number_of_elements);
}

// rehash
template<typename Key, typename Value, typename Hash>
void OpenAddressHashTable<Key, Value, Hash>::rehash(size_t new_size) {
    m_rehash_count++;
    size_t new_table_size = _get_next_prime(new_size);
    std::vector<std::pair<Key, Value>> old_table = std::move(m_table);
    std::vector<SlotState> old_state = std::move(m_state);

    m_table_size = new_table_size;
    m_table = std::vector<std::pair<Key, Value>>(m_table_size);
    m_state = std::vector<SlotState>(m_table_size, EMPTY);
    m_number_of_elements = 0;

    for (size_t i = 0; i < old_table.size(); ++i) {
        if (old_state[i] == OCCUPIED) {
            add(old_table[i].first, old_table[i].second);
        }
    }
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashTable<Key, Value, Hash>::_find_slot(const Key& key) const {
    for (size_t i = 0; i < m_table_size; ++i) {
        size_t idx = _hash_code(key, i);
        if (m_state[idx] == EMPTY) {
            // slot livre para inserção ou chave não encontrada
            return idx;
        }
        if (m_state[idx] == OCCUPIED && m_table[idx].first == key) {
            // chave encontrada
            return idx;
        }
    }
    // Retorna um valor inválido indicando que não encontrou slot adequado (tabela cheia)
    return m_table_size;
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashTable<Key, Value, Hash>::_probe(const Key& key) const {
    return m_hashing(key) % m_table_size;
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashTable<Key, Value, Hash>::size() const {
    return m_number_of_elements;
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashTable<Key, Value, Hash>::capacity() const {
    return m_table_size;
}

template<typename Key, typename Value, typename Hash>
float OpenAddressHashTable<Key, Value, Hash>::load_factor() const {
    if (m_table_size == 0) return 0.0f;
    return static_cast<float>(m_number_of_elements) / m_table_size;
}

// Métodos para obter métricas
template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashTable<Key, Value, Hash>::getComparisonCount() const {
    return m_comparison_count;
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashTable<Key, Value, Hash>::getInsertionCount() const {
    return m_insertion_count;
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashTable<Key, Value, Hash>::getSearchCount() const {
    return m_search_count;
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashTable<Key, Value, Hash>::getCollisionCount() const {
    return m_collision_count;
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashTable<Key, Value, Hash>::getRehashCount() const {
    return m_rehash_count;
}

template<typename Key, typename Value, typename Hash>
void OpenAddressHashTable<Key, Value, Hash>::resetMetrics() {
    m_comparison_count = 0;
    m_insertion_count = 0;
    m_search_count = 0;
    m_collision_count = 0;
    m_rehash_count = 0;
}

}} // namespace

#endif
