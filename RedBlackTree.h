#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "Arbol.h"
#include <iostream>

enum Color { ROJO, NEGRO };

struct NodoRB {
    int dato;
    Color color;
    NodoRB* izq;
    NodoRB* der;
    NodoRB* padre;

    NodoRB(int d) : dato(d), color(ROJO), izq(nullptr), der(nullptr), padre(nullptr) {}
};

class RedBlackTree {
private:
    NodoRB* raiz;

    // Rotaciones
    void rotacionIzquierda(NodoRB* nodo);
    void rotacionDerecha(NodoRB* nodo);

    // Recoloración
    void corregirInserccion(NodoRB* nodo);

    // Búsqueda
    NodoRB* buscar(NodoRB* nodo, int valor);

    // Altura
    int calcularAltura(NodoRB* nodo);

    // Validación
    bool validarPropiedades(NodoRB* nodo, int negrosEnCamino, int& negrosEsperados);

    // Recorridos
    void preOrdenAux(NodoRB* nodo);

    // Destrucción
    void destruirAux(NodoRB* nodo);

public:
    RedBlackTree();
    ~RedBlackTree();

    void insertar(int valor);
    void imprimirPreOrden();
    int getAltura();
    bool validarPropiedades();
    int contarNodos();
};

#endif // RED_BLACK_TREE_H