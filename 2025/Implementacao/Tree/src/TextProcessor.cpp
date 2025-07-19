#include "../include/TextProcessor.h"
#include <fstream>
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include <unicode/translit.h>
#include <codecvt>
#include <locale>

// Remove acentos e normaliza caracteres latinos
std::string TextProcessor::removeAccents(const std::string & input) const {
    std::string output;
    for (unsigned char c : input) {
        switch (c) {
        case 'á': case 'à': case 'ã': case 'â': case 'ä': output += 'a'; break;
        case 'é': case 'è': case 'ê': case 'ë': output += 'e'; break;
        case 'í': case 'ì': case 'î': case 'ï': output += 'i'; break;
        case 'ó': case 'ò': case 'õ': case 'ô': case 'ö': output += 'o'; break;
        case 'ú': case 'ù': case 'û': case 'ü': output += 'u'; break;
        case 'ç': output += 'c'; break;
        case 'Á': case 'À': case 'Ã': case 'Â': case 'Ä': output += 'a'; break;
        case 'É': case 'È': case 'Ê': case 'Ë': output += 'e'; break;
        case 'Í': case 'Ì': case 'Î': case 'Ï': output += 'i'; break;
        case 'Ó': case 'Ò': case 'Õ': case 'Ô': case 'Ö': output += 'o'; break;
        case 'Ú': case 'Ù': case 'Û': case 'Ü': output += 'u'; break;
        case 'Ç': output += 'c'; break;
        default: output += c;
        }
    }
    return output;
}

std::string TextProcessor::normalizeWord(const std::string& wordRaw) {
    std::string clean;
    for (char c : wordRaw) {
        if (std::isalpha(c) || c == '-') {
            clean += std::tolower(c);
        }
    }
    return removeAccents(clean);
}

bool TextProcessor::isWordChar(char32_t c) const {
    return u_isalpha(c);
}

bool TextProcessor::isValidChar(char32_t c) const {
    return c == '-'; //|| c == '\'' || c == '’';
}

std::vector<std::string> TextProcessor::processFile(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<char>));

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        icu::UnicodeString uline = icu::UnicodeString::fromUTF8(line);
        icu::UnicodeString currentWord;

        for (int32_t i = 0; i < uline.length();) {
            UChar32 c = uline.char32At(i);
            int32_t len = U16_LENGTH(c);

            if (isWordChar(c)) {
                currentWord.append(c);
            }
            else if (isValidChar(c) && currentWord.length() > 0) {
                currentWord.append(c);
            }
            else if (currentWord.length() > 0) {
                std::string word;
                currentWord.toUTF8String(word);
                word = normalizeWord(word);

                if (!word.empty()) {
                    words.push_back(word);
                }
                currentWord.remove();
            }

            i += len;
        }

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
