#include <iostream>
#include <algorithm>
#include "hash_table.hpp"
#include "heap.hpp"

int main() {
    HashTable hash_table(100000);
    Heap heap(20);

    std::set<std::string> stopwords = load_stopwords("dataset/stopwords.txt");
    process_files("dataset", stopwords, hash_table);

    // Preenchendo a heap com os primeiros k elementos do hash
    auto elements = hash_table.get_all_elements();
    for (const auto &element : elements) {
        heap.insert(element);
    }

    // Imprimindo as top k palavras
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Palavra" << std::setw(5) << "\t" << "Frequência" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    auto top_k = heap.get_top_k();
    for (const auto &element : top_k) {
        std::cout << element.first << std::setw(8) << "\t" << element.second << std::endl;
    }

    return 0;
}