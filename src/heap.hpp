#include <string>
#include <vector>

class Heap {
public:
    Heap(int k);
    void insert(const std::pair<std::string, int> &element);
    std::vector<std::pair<std::string, int>> get_top_k() const;

private:
    void heapify_up();
    void heapify_down(int index);
    int left_child_index(int index) const;
    int right_child_index(int index) const;
    int parent_index(int index) const;
    int k;
    std::vector<std::pair<std::string, int>> elements;
};

