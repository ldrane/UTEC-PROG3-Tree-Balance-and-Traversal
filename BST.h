#ifndef BST_H
#define BST_H

#include "Arbol.h"
#include <vector>
#include <stack>

class BST {
private:
    Nodo* raiz;
    Nodo* buscarIterativo(int valor);
    int calcularAltura(Nodo* nodo);

public:
    BST();
    ~BST();

    // Operaciones iterativas
    void insertarIterativo(int valor);
    bool eliminarIterativo(int valor);

    // Recorridos
    void recorridoInOrdenIterativo();

    // Análisis
    int getAltura();
    int contarNodos();
    void imprimirPreOrden();

    Nodo* getRaiz();
    void destruir(Nodo* nodo);
};

#endif // BST_H