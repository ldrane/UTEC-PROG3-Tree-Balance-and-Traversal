#include "Arbol.h"
#include <iostream>
#include <queue>
#include <algorithm> //para std::max

// ============================================
// PROBLEMA 4: BFS ITERATIVO SIN RECURSIÓN
// ============================================

/*
Considerando las métricas del problema, BFS es mejor porque:
1. Procesa nivel por nivel (acceso ordenado por profundidad).
2. Detecta fácilmente completitud (todos niveles llenos).
3. Calcula ancho comparando nodos por nivel.
4. Profundidad mínima encontrada al primer hallazgo.
*/

struct NodoConNivel {
    Nodo* nodo;
    int nivel;

    NodoConNivel(Nodo* n, int lvl) : nodo(n), nivel(lvl) {}
};

bool esArbolCompleto(Nodo* raiz) {
    if (raiz == nullptr) return true;

    std::queue<Nodo*> cola;
    cola.push(raiz);

    bool encontroHueco = false;  // indica si ya hemos visto un nodo que no tenga ambos hijos

    while (!cola.empty()) {
        Nodo* actual = cola.front();
        cola.pop();

        // Procesamos hijo izquierdo
        if (actual->izq != nullptr) {
            if (encontroHueco) return false; // hay un hueco antes, no puede haber más hijos
            cola.push(actual->izq);
        }
        else{
            encontroHueco = true; // falta hijo izquierdo
        }

        // Procesar hijo derecho
        if (actual->der != nullptr) {
            if (encontroHueco) return false;   // si faltó el izquierdo o ya hubo hueco antes, es inválido
            cola.push(actual->der);
        } else {
            encontroHueco = true;               // falta hijo derecho
        }
    }
    return true;
}

int anchoMaximo(Nodo* raiz) {
    if (raiz == nullptr) return 0;

    std::queue<Nodo*> cola;
    cola.push(raiz);
    int maxAncho = 1;

    while (!cola.empty()) {
        int tamanoActual = cola.size();
        maxAncho = std::max(maxAncho, tamanoActual);

        for (int i = 0; i < tamanoActual; i++) {
            Nodo* nodo = cola.front();
            cola.pop();

            if (nodo->izq != nullptr) cola.push(nodo->izq);
            if (nodo->der != nullptr) cola.push(nodo->der);
        }
    }

    return maxAncho;
}

int profundidadMinima(Nodo* raiz) {
    if (raiz == nullptr) return 0;

    std::queue<NodoConNivel> cola;
    cola.push(NodoConNivel(raiz, 1));

    while (!cola.empty()) {
        NodoConNivel actual = cola.front();
        cola.pop();

        // Primera hoja encontrada es profundidad mínima
        if (actual.nodo->izq == nullptr && actual.nodo->der == nullptr) {
            return actual.nivel;
        }

        if (actual.nodo->izq != nullptr)
            cola.push(NodoConNivel(actual.nodo->izq, actual.nivel + 1));
        if (actual.nodo->der != nullptr)
            cola.push(NodoConNivel(actual.nodo->der, actual.nivel + 1));
    }

    return 1;
}

void problema4() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "PROBLEMA 4: BFS Iterativo - Metrics del Tree" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    // Creamos árbol de prueba
    Nodo* raiz = new Nodo(1);
    raiz->izq = new Nodo(2);
    raiz->der = new Nodo(3);
    raiz->izq->izq = new Nodo(4);
    raiz->izq->der = new Nodo(5);
    raiz->der->izq = new Nodo(6);
    raiz->der->der = new Nodo(7);

    std::cout << "Es un tree completo? "
              << (esArbolCompleto(raiz) ? "SI" : "NO") << std::endl;
    std::cout << "Ancho maximo: " << anchoMaximo(raiz) << std::endl;
    std::cout << "Profundidad minima: " << profundidadMinima(raiz) << std::endl;

    /*
    JUSTIFICACIÓN FORMAL DE BFS:

    1. ÁRBOL COMPLETO:
       - Definición: Todos los niveles llenos excepto el último
       - BFS procesa nivel a nivel (exactamente lo que necesitamos)
       - Detecta huecos al encontrar hoja antes de tiempo

    2. ANCHO MÁXIMO:
       - Necesitamos procesar nodos nivel a nivel
       - BFS garantiza orden de niveles
       - Usar queue.size() = número de nodos en nivel actual

    3. PROFUNDIDAD MÍNIMA:
       - Primera hoja encontrada en BFS es la mínima
       - BFS explora en orden de distancia desde raíz
       - O(profundidad mínima) operaciones
    */

    // Limpiamos
    delete raiz->izq->izq;
    delete raiz->izq->der;
    delete raiz->der->izq;
    delete raiz->der->der;
    delete raiz->izq;
    delete raiz->der;
    delete raiz;
}