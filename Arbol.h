#ifndef ARBOL_H
#define ARBOL_H

#include <iostream>
#include <stack>
#include <queue>
#include <vector>

struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;

    Nodo(int d) : dato(d), izq(nullptr), der(nullptr), padre(nullptr) {}
};

#endif // ARBOL_H