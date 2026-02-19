cmake_minimum_required(VERSION 3.28)
project(tsk6)

set(CMAKE_CXX_STANDARD 20)

add_executable(tsk6
            main.cpp
            e1-BST-iterativo-y-analisis-degradacion.cpp
            e2-RedBlackTree.cpp
            e3-DFS-iterativo-avanzado.cpp
            e4-BFS-iterativo-avanzado.cpp
)
