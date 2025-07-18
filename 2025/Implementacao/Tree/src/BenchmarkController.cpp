#include "../include/BenchmarkController.h"
#include "../include/AVLDictionary.h"
#include "../include/RBDictionary.h"
//#include "../include/ChainedHashDictionary.h"
//#include "../include/OpenHashDictionary.h"
#include <iostream>
#include <fstream>
#include <iomanip>


//namespace fs = std::experimental::filesystem;

BenchmarkController::BenchmarkController()
    : textProcessor(), benchmark() {
    // Inicialização de recursos, se necessário
}

void BenchmarkController::execute(int argc, char* argv[]) {
    try {
        RunConfig config = parseArguments(argc, argv);

        if (config.dictType == DictionaryType::ALL) {
            runAllBenchmarks(config);
        }
        else {
            runSingleBenchmark(config.dictType, config);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

BenchmarkController::RunConfig BenchmarkController::parseArguments(int argc, char* argv[]) const {
    if (argc < 3) {
        throw std::invalid_argument(
            "Usage: freq <dictionary_type> <input_file> [output_file] [--benchmark]\n"
            "Available dictionary types: avl, rb, chained, open, all"
        );
    }

    RunConfig config;
    std::string typeStr(argv[1]);

    // Mapeamento de argumentos
    if (typeStr == "avl") config.dictType = DictionaryType::AVL;
    else if (typeStr == "rb") config.dictType = DictionaryType::RED_BLACK;
    else if (typeStr == "chained") config.dictType = DictionaryType::CHAINED_HASH;
    else if (typeStr == "open") config.dictType = DictionaryType::OPEN_HASH;
    else if (typeStr == "all") config.dictType = DictionaryType::ALL;
    else throw std::invalid_argument("Invalid dictionary type: " + typeStr);

    config.inputFile = argv[2];
    config.benchmarkMode = false;

    // Processa argumentos opcionais
    for (int i = 3; i < argc; ++i) {
        std::string arg(argv[i]);
        if (arg == "--benchmark") {
            config.benchmarkMode = true;
        }
        else if (config.outputFile.empty()) {
            config.outputFile = arg;
        }
    }

    std::ifstream file(config.inputFile);
    // Verifica se o arquivo de entrada existe
    if (!file.good()) {
        throw std::runtime_error("Input file does not exist: " + config.inputFile);
    }

    return config;
}

std::unique_ptr<IDictionary> BenchmarkController::createDictionary(DictionaryType type) const {
    switch (type) {
    case DictionaryType::AVL:
        return std::make_unique<AVLDictionary>();
    case DictionaryType::RED_BLACK:
        return std::make_unique<RBDictionary>();
    case DictionaryType::CHAINED_HASH:
    //    return std::make_unique<ChainedHashDictionary>();
    //case DictionaryType::OPEN_HASH:
    //    return std::make_unique<OpenHashDictionary>();
    default:
        throw std::invalid_argument("Unknown dictionary type");
    }
}

void BenchmarkController::runSingleBenchmark(DictionaryType type, const RunConfig& config) {
    auto dict = createDictionary(type);
    auto words = textProcessor.processFile(config.inputFile);
    Benchmark::Metrics metrics = benchmark.run(*dict, words);
    metrics.bookName = benchmark.getBookNameFromPath(config.inputFile);

    // 1. Salva métricas em CSV
    std::string metricsFile = getDictionaryName(type) + "_metrics.csv";
    saveBenchmarkResults(metrics, metricsFile);

    // 2. Salva frequência de palavras em outro CSV
    std::string dictFile = getDictionaryName(type) + "_words.csv";
    saveDictionaryResults(*dict, dictFile);

    // 3. Exibe no console (opcional)
    if (config.benchmarkMode) {
        printBenchmarkResults(metrics);
    }
}

void BenchmarkController::runAllBenchmarks(const RunConfig& config) {
    const std::vector<DictionaryType> allTypes = {
        DictionaryType::AVL,
        DictionaryType::RED_BLACK,
        // DictionaryType::CHAINED_HASH,
        // DictionaryType::OPEN_HASH
    };

    // Processa o arquivo apenas uma vez para todos os dicionários
    auto words = textProcessor.processFile(config.inputFile);
    std::string bookName = benchmark.getBookNameFromPath(config.inputFile);

    for (const auto& type : allTypes) {
        auto dict = createDictionary(type);
        std::string dictName = getDictionaryName(type);

        // Executa benchmark
        Benchmark::Metrics metrics = benchmark.run(*dict, words);
        metrics.bookName = bookName;

        // 1. Sempre salva métricas em CSV
        std::string metricsFile = dictName + "_metrics.csv";
        saveBenchmarkResults(metrics, metricsFile);

        // 2. Sempre salva frequência de palavras
        std::string wordsFile = dictName + "_words.csv";
        saveDictionaryResults(*dict, wordsFile);

        // 3. Salva arquivos adicionais se especificado
        if (!config.outputFile.empty()) {
            std::string customOutput = config.outputFile + "_" + dictName + ".txt";
            saveDictionaryResults(*dict, customOutput);
        }

        // 4. Exibe no console se solicitado
        if (config.benchmarkMode) {
            printBenchmarkResults(metrics);
        }
    }
}

void BenchmarkController::saveDictionaryResults(const IDictionary& dict, const std::string& filename) const {
    std::ostream* out = &std::cout;
    std::ofstream fileStream;

    if (!filename.empty()) {
        fileStream.open(filename);
        if (!fileStream.is_open()) {
            throw std::runtime_error("Failed to open output file: " + filename);
        }
        out = &fileStream;
    }

    // Cabeçalho
    *out << "Word Frequency Results (" << dict.getName() << ")\n";
    *out << "=================================\n";

    //// Obtém e ordena as entradas
    //auto entries = dict.getSortedEntries();

    //// Formata a saída
    //for (const auto& [word, count] : entries) {
    //    *out << "| " << std::setw(25) << std::left << word
    //        << " | " << std::setw(5) << std::right << count << " |\n";
    //}

    //*out << "=================================\n";
    //*out << "Total unique words: " << entries.size() << "\n";
}

std::string BenchmarkController::getDictionaryName(DictionaryType type) const {
    switch (type) {
    case DictionaryType::AVL: return "AVL";
    case DictionaryType::RED_BLACK: return "RedBlack";
    case DictionaryType::CHAINED_HASH: return "ChainedHash";
    case DictionaryType::OPEN_HASH: return "OpenHash";
    case DictionaryType::ALL: return "All";
    default: return "Unknown";
    }
}



void BenchmarkController::saveBenchmarkResults(const Benchmark::Metrics& metrics, const std::string& filename) const {
    std::string fullPath = "result/" + filename;
    std::ofstream out(fullPath);

    if (!out.is_open()) {
        throw std::runtime_error("Falha ao criar arquivo: " + fullPath);
    }

    // Cabeçalho CSV
    out << "estrutura,arquivo,tempo_ms,comparacoes,insercoes,rotacoes,colisoes,rehashes,fator_carga,palavras_totais,palavras_unicas\n";

    // Dados
    out << metrics.structureName << ","
        << metrics.bookName << ","
        << metrics.time_ms << ","
        << metrics.comparisons << ","
        << metrics.insertions << ","
        << metrics.rotations << ","
        << metrics.collisions << ","
        << metrics.rehashes << ","
        << std::fixed << std::setprecision(2) << metrics.load_factor << ","
        << metrics.totalWords << ","
        << metrics.uniqueWords << "\n";
}

void BenchmarkController::printBenchmarkResults(const Benchmark::Metrics& metrics) const {
    std::cout << "\n=== Resultados " << metrics.structureName << " ===\n"
        << "* Tempo (ms): " << metrics.time_ms << "\n"
        << "* Comparacoes: " << metrics.comparisons << "\n"
        << "* Insercoes: " << metrics.insertions << "\n"
        << "* Rotacoes: " << metrics.rotations << "\n"
        << "* Colisoes: " << metrics.collisions << "\n"
        << "* Rehashes: " << metrics.rehashes << "\n"
        << "* Fator Carga: " << std::fixed << std::setprecision(2) << metrics.load_factor << "\n"
        << "* Palavras Totais: " << metrics.totalWords << "\n"
        << "* Palavras Unicas: " << metrics.uniqueWords << "\n"
        << "================================\n";
}