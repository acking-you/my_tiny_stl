cmake_minimum_required(VERSION 3.16)
project(my_tiny_stl)

set(CMAKE_CXX_STANDARD 14)

add_executable(my_tiny_stl main.cpp BinarySearch.cpp BinarySearch.h HashTable.cpp HashTable.h UnionFind.cpp UnionFind.h Tarjan.cpp Tarjan.h LinkMap.cpp LinkMap.h Trie_dyn.cpp Trie_dyn.h Trie_static.cpp Trie_static.h)