#include "hash_table.hpp"

namespace fs = std::filesystem;

std::string clean_word(const std::string &word) {
    std::string cleaned_word;
    std::copy_if(word.begin(), word.end(), std::back_inserter(cleaned_word), [](char c) {
        return std::isalpha(c);
    });
    std::transform(cleaned_word.begin(), cleaned_word.end(), cleaned_word.begin(), ::tolower);
    return cleaned_word;
}

HashTable::HashTable(size_t size) : size(size), table(size) {}

void HashTable::insert(const std::string &key) {
    size_t index = hash(key);
    for (auto &entry : table[index]) {
        if (entry.first == key) {
            entry.second++;
            return;
        }
    }
    table[index].push_back(std::make_pair(key, 1));
}

int HashTable::get_frequency(const std::string &key) const {
    size_t index = hash(key);
    for (const auto &entry : table[index]) {
        if (entry.first == key) {
            return entry.second;
        }
    }
    return 0;
}

std::vector<std::pair<std::string, int>> HashTable::get_all_elements() const {
    std::vector<std::pair<std::string, int>> elements;
    for (const auto &bucket : table) {
        for (const auto &entry : bucket) {
            elements.push_back(entry);
        }
    }
    return elements;
}

size_t HashTable::hash(const std::string &key) const {
    size_t hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % size;
    }
    return hash;
}

// ... outras definições ...
std::set<std::string> load_stopwords(const std::string &filename) {
    std::set<std::string> stopwords;
    std::ifstream stopwords_file(filename);
    std::string word;
    while (stopwords_file >> word) {
        stopwords.insert(clean_word(word));
    }
    stopwords_file.close();
    return stopwords;
}

void process_files(const std::string &directory, const std::set<std::string> &stopwords, HashTable &hash_table) {
    for (const auto &entry : fs::directory_iterator(directory)) {
        std::string filename = entry.path().filename().string();
        if (filename != "stopwords.txt") {
            std::ifstream input_file(entry.path());
            std::string line;
            while (std::getline(input_file, line)) {
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) {
                    word = clean_word(word);
                    if (stopwords.find(word) == stopwords.end()) {
                        hash_table.insert(word);
                    }
                }
            }
            input_file.close();
        }
    }
}