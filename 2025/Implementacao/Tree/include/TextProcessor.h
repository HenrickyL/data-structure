#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <string>
#include <vector>
#include <unicode/unistr.h>

class TextProcessor {
public:
    // Process file and return list of normalized words
    std::vector<std::string> processFile(const std::string& filename);

    // Normalize a single word
    std::string normalizeWord(const std::string& word);

private:
    bool isValidChar(char32_t c) const;
    bool isWordChar(char32_t c) const;
};

#endif