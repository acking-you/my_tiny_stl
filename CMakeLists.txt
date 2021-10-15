cmake_minimum_required(VERSION 3.16)
project(my_tiny_stl)

set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32)
add_executable(my_tiny_stl main.cpp BinarySearch.cpp BinarySearch.h HashTable.cpp HashTable.h UnionFind.cpp UnionFind.h Tarjan.cpp Tarjan.h LinkMap.cpp LinkMap.h Trie_dyn.cpp Trie_dyn.h Trie_static.cpp Trie_static.h _public_socket.h TCP_SOCKET_SERVER.cpp TCP_SOCKET_SERVER.h TCP_INTERFACE.h TCP_SOCKET_CLIENT.cpp TCP_SOCKET_CLIENT.h Complex.cpp Complex.h Heap.hpp BigInteger.cpp BigInteger.h AVLTree.cpp AVLTree.h Treap.cpp Treap.h)