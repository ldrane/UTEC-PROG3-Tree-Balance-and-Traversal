#include "Arbol.h"
#include <iostream>
#include <stack>
#include <vector>

// ============================================
// PROBLEMA 3: DFS ITERATIVO SIN RECURSIÓN
// ============================================

/*
PROBLEMA: Encontrar si existe camino raíz-hoja con suma = K Retornar el camino si existe

Entonces, analizando el problema, concluyo que DFS es adecuado porque:
1. Explora completamente una rama antes de pasar a otra
2. Usa menos memoria que BFS (stack vs queue)
3. Mantiene el camino actual en la pila
4. Permite retroceso (backtracking) natural
*/

struct NodoConCamino {
    Nodo* nodo;
    std::vector<int> camino;
    int suma;

    NodoConCamino(Nodo* n, int s) : nodo(n), suma(s) {
        if (n != nullptr) {
            camino.push_back(n->dato);
            suma += n->dato;
        }
    }
};

bool dfsIterativoSuma(Nodo* raiz, int K, std::vector<int>& caminoResultado) {
    if (raiz == nullptr) {
        return false;
    }

    std::stack<NodoConCamino*> pila;
    pila.push(new NodoConCamino(raiz, 0));

    while (!pila.empty()) {
        NodoConCamino* actual = pila.top();
        pila.pop();

        // Si es hoja y suma coincide, se encontró el camino
        if (actual->nodo->izq == nullptr && actual->nodo->der == nullptr && actual->suma == K) {
            caminoResultado = actual->camino;
            delete actual;

            //Liberamos el resto de la pila antes de hacer el return
            while (!pila.empty()){
                delete pila.top();
               pila.pop();
            }
            return true;
        }

        // Agregamos hijos (derecho primero para que el izquierdo se procese antes con LIFO)

        //Agregamos hijo derecho
        if (actual->nodo->der != nullptr) {
            NodoConCamino* derecho = new NodoConCamino(actual->nodo->der, actual->suma);
            derecho->camino = actual->camino;
            derecho->camino.push_back(actual->nodo->der->dato);
            pila.push(derecho);
        }

        // Agregamos hijo izquierdo
        if (actual->nodo->izq != nullptr) {
            NodoConCamino* izquierdo = new NodoConCamino(actual->nodo->izq, actual->suma);
            izquierdo->camino = actual->camino;
            izquierdo->camino.push_back(actual->nodo->izq->dato);
            pila.push(izquierdo);
        }
        delete actual;
    }
    return false;
}

void problema3() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "PROBLEMA 3: DFS Iterativo - Suma Raiz-Hoja" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    // Creamos árbol de prueba
    Nodo* raiz = new Nodo(10);
    raiz->izq = new Nodo(5);
    raiz->der = new Nodo(15);
    raiz->izq->izq = new Nodo(3);
    raiz->izq->der = new Nodo(7);
    raiz->der->der = new Nodo(20);

    int K = 25;  // Buscamos suma = 25
    std::vector<int> camino;

    if (dfsIterativoSuma(raiz, K, camino)) {
        std::cout << "Camino encontrado con suma " << K << ": ";
        for (int val : camino) {
            std::cout << val << " → ";
        }
        std::cout << "\b\b  " << std::endl;
    } else {
        std::cout << "No existe camino con suma " << K << std::endl;
    }

    /*
    ANÁLISIS DE COMPLEJIDAD:
    - Tiempo: O(n) -> visita cada nodo una vez
    - Espacio: O(h) -> altura máxima en la pila
    */

    // Limpiamos
    delete raiz->izq->izq;
    delete raiz->izq->der;
    delete raiz->der->der;
    delete raiz->izq;
    delete raiz->der;
    delete raiz;
}