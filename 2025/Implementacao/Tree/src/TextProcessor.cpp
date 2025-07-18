#include "../include/TextProcessor.h"
#include <fstream>
#include <unicode/translit.h>
#include <algorithm>

std::vector<std::string> TextProcessor::processFile(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        icu::UnicodeString uline(line.c_str());
        icu::UnicodeString currentWord;

        for (int32_t i = 0; i < uline.length(); ++i) {
            auto c = uline.char32At(i);

            if (isWordChar(c)) {
                currentWord += c;
            }
            else if (isValidChar(c) && currentWord.length() > 0) {
                // Handle apostrophes or hyphens inside words
                currentWord += c;
            }
            else if (currentWord.length() > 0) {
                // Word ended
                std::string word;
                currentWord.toUTF8String(word);
                word = normalizeWord(word);

                if (!word.empty()) {
                    words.push_back(word);
                }
                currentWord.remove();
            }
        }

        // Add last word if any
        if (currentWord.length() > 0) {
            std::string word;
            currentWord.toUTF8String(word);
            word = normalizeWord(word);

            if (!word.empty()) {
                words.push_back(word);
            }
        }
    }

    return words;
}

std::string TextProcessor::normalizeWord(const std::string& word) {
    icu::UnicodeString uword(word.c_str());
    uword.toLower();

    // Remove non-word characters from start/end (keep hyphens in the middle)
    int32_t start = 0;
    int32_t end = uword.length() - 1;

    while (start <= end && !isWordChar(uword.char32At(start))) {
        start++;
    }

    while (end >= start && !isWordChar(uword.char32At(end))) {
        end--;
    }

    if (start > end) {
        return "";
    }

    icu::UnicodeString normalized = uword.tempSubString(start, end - start + 1);

    // Remove apostrophes from the end (like in "cats'")
    while (normalized.length() > 0 && normalized.char32At(normalized.length() - 1) == '\'') {
        normalized.truncate(normalized.length() - 1);
    }

    std::string result;
    normalized.toUTF8String(result);
    return result;
}

bool TextProcessor::isValidChar(char32_t c) const {
    // Allow apostrophes and hyphens (for words like "don't" or "state-of-the-art")
    return c == '\'' || c == '-';
}

bool TextProcessor::isWordChar(char32_t c) const {
    return u_isalpha(c) || u_isdigit(c);
}