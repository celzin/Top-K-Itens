#include "heap.hpp"

Heap::Heap(int k) : k(k) {}

void Heap::insert(const std::pair<std::string, int> &element) {
    elements.push_back(element);
    heapify_up();
    if (elements.size() > k) {
        elements[0] = elements.back();
        elements.pop_back();
        heapify_down(0);
    }
}

std::vector<std::pair<std::string, int>> Heap::get_top_k() const {
    return elements;
}

void Heap::heapify_up() {
    int index = elements.size() - 1;
    while (index > 0 && elements[index].second < elements[parent_index(index)].second) {
        std::swap(elements[index], elements[parent_index(index)]);
        index = parent_index(index);
    }
}

void Heap::heapify_down(int index) {
    int smallest = index;
    if (left_child_index(index) < elements.size() && elements[left_child_index(index)].second < elements[smallest].second) {
        smallest = left_child_index(index);
    }
    if (right_child_index(index) < elements.size() && elements[right_child_index(index)].second < elements[smallest].second) {
        smallest = right_child_index(index);
    }
    if (smallest != index) {
        std::swap(elements[index], elements[smallest]);
        heapify_down(smallest);
    }
}

int Heap::left_child_index(int index) const {
    return 2 * index + 1;
}

int Heap::right_child_index(int index) const {
    return 2 * index + 2;
}

int Heap::parent_index(int index) const {
    return (index - 1) / 2;
}

void fill_heap_with_top_elements(Heap &heap, const HashTable &hash_table) {
    auto elements = hash_table.get_all_elements();
    for (const auto &element : elements) {
        heap.insert(element);
    }
}

void print_top_k_words(const Heap &heap) {
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Palavra" << std::setw(5) << "\t" << "Frequência" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    auto top_k = heap.get_top_k();
    for (const auto &element : top_k) {
        std::cout << element.first << std::setw(8) << "\t" << element.second << std::endl;
    }
}