
# Curso Intensivo de C++: Tópicos Intermediários

## Templates (Genéricos)

### 1. Template Básico para Árvore Binária
```cpp
template <typename T>
class BinaryTree {
    struct Node {
        T data;  // Tipo genérico
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };
    // ... restante da implementação ...
};

// Uso:
BinaryTree<int> treeInt;
BinaryTree<std::string> treeString;
```

### 2. Template com Múltiplos Parâmetros
```cpp
template <typename Key, typename Value>
class Dictionary {
    std::vector<std::pair<Key, Value>> entries;
public:
    void add(const Key& k, const Value& v) {
        entries.emplace_back(k, v);
    }
};
```

## Ponteiros Seguros (Modern C++)

### 1. `unique_ptr` (Posse Exclusiva)
```cpp
auto ptr = std::make_unique<int>(42);  // Alocação segura
// ptr é automaticamente liberado ao sair do escopo
```

### 2. `shared_ptr` (Contagem de Referências)
```cpp
auto shared = std::make_shared<int>(42);
auto another = shared;  // Ambos compartilham a posse
```

### 3. `weak_ptr` (Evitar Ciclos)
```cpp
std::weak_ptr<Node> observer;
if (auto locked = observer.lock()) {  // Converte para shared_ptr
    // Acesso seguro
}
```

## Strings e Métodos Úteis

### 1. Operações Básicas
```cpp
std::string s = "Árvore Binária";
s.append(" em C++");  // Concatenação
s.replace(0, 6, "Árvore");  // Substituição
```

### 2. Busca e Substrings
```cpp
size_t pos = s.find("Bin");  // Retorna posição ou std::string::npos
std::string sub = s.substr(8, 5);  // "Binár"
```

### 3. Conversão Numérica
```cpp
std::string numStr = "1234";
int num = std::stoi(numStr);  // String para int
double d = std::stod("3.1415");  // String para double
std::string piStr = std::to_string(3.1415);  // Double para string
```

## Conversão de Tipos Segura

### 1. `static_cast` (Conversão Explícita)
```cpp
double d = 3.14;
int i = static_cast<int>(d);  // Conversão numérica segura
```

### 2. `dynamic_cast` (Polimorfismo)
```cpp
Base* b = new Derived();
if (Derived* d = dynamic_cast<Derived*>(b)) {
    // Uso seguro do ponteiro convertido
}
```

### 3. `const_cast` (Remover Const)
```cpp
const std::string s = "const";
std::string& mutableStr = const_cast<std::string&>(s);  // Uso cuidadoso!
```

## Boas Práticas Elaboradas

### 1. Regra dos 5 (Gerenciamento de Recursos)
```cpp
class ResourceHolder {
    int* resource;
public:
    // 1. Construtor
    ResourceHolder(int size) : resource(new int[size]) {}
    
    // 2. Destrutor
    ~ResourceHolder() { delete[] resource; }
    
    // 3. Construtor de Cópia
    ResourceHolder(const ResourceHolder& other) {
        resource = new int[/*tamanho*/];
        std::copy(/*...*/);
    }
    
    // 4. Operador de Atribuição
    ResourceHolder& operator=(ResourceHolder other) {
        swap(*this, other);
        return *this;
    }
    
    // 5. Construtor de Movimento
    ResourceHolder(ResourceHolder&& other) noexcept 
        : resource(std::exchange(other.resource, nullptr)) {}
};
```

### 2. Segurança de Exceções
```cpp
void safeOperation() {
    auto res = std::make_unique<Resource>();  // RAII
    // Operações que podem lançar exceções
    if (error) throw std::runtime_error("Erro");
    // Recurso é liberado automaticamente se exceção ocorrer
}
```

### 3. Otimizações Modernas
```cpp
// Move semantics
std::vector<std::string> createStrings() {
    std::vector<std::string> v;
    v.reserve(100);  // Alocação antecipada
    // ... preenche o vetor
    return v;  // NRVO/move implícito
}

// Structured bindings (C++17)
auto [it, inserted] = mySet.insert(value);
```

### 4. Dicas de Performance
```cpp
// Passagem por referência para objetos grandes
void process(const BigObject& obj); 

// Use reserve() em vetores quando possível
std::vector<int> v;
v.reserve(1000);  // Evita realocações

// Prefira emplace_back() no lugar de push_back()
v.emplace_back(42);  // Constrói no local
```

### 5. Estilo e Legibilidade
```cpp
// Use aliases para tipos complexos
template <typename T>
using Matrix = std::vector<std::vector<T>>;

// Atribuição condicional moderna
if (auto it = map.find(key); it != map.end()) {
    // 'it' visível apenas neste escopo
}

// Const correctness
class Immutable {
    int value;
public:
    [[nodiscard]] int getValue() const { return value; }
};
```

## Recomendações Finais

1. **Ferramentas**:
   - Use `clang-tidy` para análise estática
   - Configure CI/CD com testes automatizados
   - Use sanitizers (`-fsanitize=address,undefined`)

2. **Padrões**:
   - Siga as diretrizes do C++ Core Guidelines
   - Documente suas decisões de design
   - Mantenha consistência no estilo de código

3. **Aprendizado**:
   - Estude os novos recursos do C++20/23
   - Pratique com exercícios no LeetCode/HackerRank
   - Participe de code reviews

4. **Performance**:
   - Perfilie antes de otimizar
   - Entenda o modelo de memória do C++
   - Considere cache locality em estruturas de dados
``` 

Este documento combina os melhores recursos do C++ moderno com ênfase em práticas seguras e eficientes, mantendo a clareza e organização do código.