#include <iostream>
#include <algorithm>
#include <iomanip>
#include "hash_table.hpp"
#include "heap.hpp"

const int TABLE_SIZE = 100000;
const int TOP_K = 20;
const std::string STOPWORDS_PATH = "dataset/stopwords.txt";
const std::string DATASET_PATH = "dataset";

int main() {
    HashTable hash_table(TABLE_SIZE);
    Heap heap(TOP_K);

    auto stopwords = initialize_stopwords(STOPWORDS_PATH);
    process_dataset(DATASET_PATH, stopwords, hash_table);
    fill_heap_with_top_elements(heap, hash_table);

    print_top_k_words(heap);

    return 0;
}