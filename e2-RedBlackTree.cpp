#include "RedBlackTree.h"

// =================================================================================
// PROBLEMA 2: RED-BLACK TREE AUTO-BALANCEADO (Análisis solicitado al final del code)
// =================================================================================

RedBlackTree::RedBlackTree() : raiz(nullptr) {}

RedBlackTree::~RedBlackTree() {
    destruirAux(raiz);
}

void RedBlackTree::destruirAux(NodoRB* nodo) {
    if (nodo == nullptr) return;
    destruirAux(nodo->izq);
    destruirAux(nodo->der);
    delete nodo;
}

// ROTACIÓN IZQUIERDA: O(1)
void RedBlackTree::rotacionIzquierda(NodoRB* nodo) {
    NodoRB* hijo_der = nodo->der;
    nodo->der = hijo_der->izq;

    if (hijo_der->izq != nullptr)
        hijo_der->izq->padre = nodo;

    hijo_der->padre = nodo->padre;

    if (nodo->padre == nullptr) {
        raiz = hijo_der;
    } else if (nodo == nodo->padre->izq) {
        nodo->padre->izq = hijo_der;
    } else {
        nodo->padre->der = hijo_der;
    }

    hijo_der->izq = nodo;
    nodo->padre = hijo_der;
}

// ROTACIÓN DERECHA: O(1)
void RedBlackTree::rotacionDerecha(NodoRB* nodo) {
    NodoRB* hijo_izq = nodo->izq;
    nodo->izq = hijo_izq->der;

    if (hijo_izq->der != nullptr)
        hijo_izq->der->padre = nodo;

    hijo_izq->padre = nodo->padre;

    if (nodo->padre == nullptr) {
        raiz = hijo_izq;
    } else if (nodo == nodo->padre->der) {
        nodo->padre->der = hijo_izq;
    } else {
        nodo->padre->izq = hijo_izq;
    }

    hijo_izq->der = nodo;
    nodo->padre = hijo_izq;
}

// CORRECCIÓN DE VIOLACIONES: O(log n)
void RedBlackTree::corregirInserccion(NodoRB* nodo) {
    while (nodo->padre != nullptr && nodo->padre->color == ROJO) {
        if (nodo->padre == nodo->padre->padre->izq) {
            NodoRB* tio = nodo->padre->padre->der;

            // Caso 1: Tío rojo
            if (tio != nullptr && tio->color == ROJO) {
                nodo->padre->color = NEGRO;
                tio->color = NEGRO;
                nodo->padre->padre->color = ROJO;
                nodo = nodo->padre->padre;
            } else {
                // Caso 2: Tío negro
                if (nodo == nodo->padre->der) {
                    nodo = nodo->padre;
                    rotacionIzquierda(nodo);
                }

                // Caso 3
                nodo->padre->color = NEGRO;
                nodo->padre->padre->color = ROJO;
                rotacionDerecha(nodo->padre->padre);
            }
        } else {
            NodoRB* tio = nodo->padre->padre->izq;

            if (tio != nullptr && tio->color == ROJO) {
                nodo->padre->color = NEGRO;
                tio->color = NEGRO;
                nodo->padre->padre->color = ROJO;
                nodo = nodo->padre->padre;
            } else {
                if (nodo == nodo->padre->izq) {
                    nodo = nodo->padre;
                    rotacionDerecha(nodo);
                }

                nodo->padre->color = NEGRO;
                nodo->padre->padre->color = ROJO;
                rotacionIzquierda(nodo->padre->padre);
            }
        }
    }
    raiz->color = NEGRO;
}

// INSERCIÓN: O(log n)
void RedBlackTree::insertar(int valor) {
    NodoRB* nuevoNodo = new NodoRB(valor);

    if (raiz == nullptr) {
        raiz = nuevoNodo;
        raiz->color = NEGRO;
        return;
    }

    NodoRB* actual = raiz;
    NodoRB* padre = nullptr;

    while (actual != nullptr) {
        padre = actual;
        if (valor < actual->dato) {
            actual = actual->izq;
        } else if (valor > actual->dato) {
            actual = actual->der;
        } else {
            delete nuevoNodo;
            return;
        }
    }

    nuevoNodo->padre = padre;
    if (valor < padre->dato)
        padre->izq = nuevoNodo;
    else
        padre->der = nuevoNodo;

    corregirInserccion(nuevoNodo);
}

// ALTURA
int RedBlackTree::calcularAltura(NodoRB* nodo) {
    if (nodo == nullptr) return 0;
    return 1 + std::max(calcularAltura(nodo->izq), calcularAltura(nodo->der));
}

int RedBlackTree::getAltura() {
    return calcularAltura(raiz);
}

// VALIDACIÓN DE PROPIEDADES
bool RedBlackTree::validarPropiedades(NodoRB* nodo, int negrosEnCamino, int& negrosEsperados) {
    if (nodo == nullptr) {
        if (negrosEsperados == -1) {
            negrosEsperados = negrosEnCamino;
        }
        return negrosEnCamino == negrosEsperados;
    }

    // Verificar: No dos rojos consecutivos
    if (nodo->color == ROJO && nodo->padre != nullptr && nodo->padre->color == ROJO)
        return false;

    // Contar nodos negros
    int nuevoConteo = negrosEnCamino;
    if (nodo->color == NEGRO) nuevoConteo++;

    return validarPropiedades(nodo->izq, nuevoConteo, negrosEsperados) &&
           validarPropiedades(nodo->der, nuevoConteo, negrosEsperados);
}

bool RedBlackTree::validarPropiedades() {
    if (raiz == nullptr) return true;
    if (raiz->color != NEGRO) return false;

    int negrosEsperados = -1;
    return validarPropiedades(raiz, 0, negrosEsperados);
}

// RECORRIDO PRE-ORDER
void RedBlackTree::preOrdenAux(NodoRB* nodo) {
    if (nodo == nullptr) return;
    std::cout << nodo->dato << "(" << (nodo->color == ROJO ? "R" : "N") << ") ";
    preOrdenAux(nodo->izq);
    preOrdenAux(nodo->der);
}

void RedBlackTree::imprimirPreOrden() {
    std::cout << "Pre-Order RB-Tree: ";
    preOrdenAux(raiz);
    std::cout << std::endl;
}

int RedBlackTree::contarNodos() {
    if (raiz == nullptr) return 0;

    int count = 0;
    std::stack<NodoRB*> pila;
    pila.push(raiz);

    while (!pila.empty()) {
        NodoRB* nodo = pila.top();
        pila.pop();
        count++;

        if (nodo->der != nullptr) pila.push(nodo->der);
        if (nodo->izq != nullptr) pila.push(nodo->izq);
    }
    return count;
}


/*
DEMOSTRACIÓN MATEMÁTICA: ALTURA O(log n)

Teorema: En un Red-Black Tree con n nodos, la altura h <= 2*log2(n+1)

Prueba:
Sea B = número mínimo de nodos negros en cualquier camino raíz-hoja

1. Cualquier camino raíz-hoja tiene h nodos
2. Por la regla de "sin dos rojos consecutivos":
   - Máximo h/2 nodos rojos en un camino
3. Por la regla de "igual número de negros":
   - Mínimo h/2 nodos negros

Por lo tanto: B >= h/2

4. Un árbol con B nodos negros tiene al menos 2^B - 1 nodos totales
5. Entonces: n >= 2^(h/2) - 1
6. Resolviendo: h <= 2*log2(n+1)

CONCLUSIÓN: Entonces, concluyo que considerando el peor caso, Red-Black Tree mantiene altura O(log n) incluso con
 inserción ordenada mediante rotaciones (O(1) cada una)y recoloración (O(log n) en peor caso)
*/