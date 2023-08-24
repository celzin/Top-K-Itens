cmake_minimum_required(VERSION 3.12)

project("Top-K-Elementos" VERSION 1.0.0)

add_executable(app "src/main.cpp" "src/hash_table.cpp" "src/heap.cpp")