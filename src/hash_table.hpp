#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <string>
#include <iostream>    
#include <vector>
#include <list>
#include <set>
#include <string>
#include <fstream> 
#include <sstream>  
#include <regex>
#include <algorithm>
#include <dirent.h>
#include <cctype>

class HashTable {
public:
    HashTable(size_t size);
    void insert(const std::string &key);
    int get_frequency(const std::string &key) const;
    std::vector<std::pair<std::string, int>> get_all_elements() const;
    std::string remove_em_dash(const std::string &input);

private:
    size_t hash(const std::string &key) const;
    size_t size;
    std::vector<std::list<std::pair<std::string, int>>> table;
};

std::set<std::string> load_stopwords(const std::string &filename);
void process_files(const std::string &directory, const std::set<std::string> &stopwords, HashTable &hash_table);

std::set<std::string> initialize_stopwords(const std::string &path);
void process_dataset(const std::string &path, const std::set<std::string> &stopwords, HashTable &hash_table);

#endif  // HASH_TABLE_HPP