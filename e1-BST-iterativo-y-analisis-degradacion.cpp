#include "BST.h"

// =========================================================================================
// PROBLEMA 1: BST ITERATIVO Y ANÁLISIS DE DEGRADACIÓN (Análisis solicitado debajo del code)
// =========================================================================================

BST::BST() : raiz(nullptr) {}

BST::~BST() {
    destruir(raiz);
}

void BST::destruir(Nodo* nodo) {
    if (nodo == nullptr) return;
    destruir(nodo->izq);
    destruir(nodo->der);
    delete nodo;
}

// INSERCIÓN ITERATIVA: O(h) donde h es altura
void BST::insertarIterativo(int valor) {
    Nodo* nuevoNodo = new Nodo(valor);

    // Caso especial: árbol vacío
    if (raiz == nullptr) {
        raiz = nuevoNodo;
        return;
    }

    // Iteración: descender hasta encontrar posición correcta
    Nodo* actual = raiz;
    Nodo* padre = nullptr;

    while (actual != nullptr) {
        padre = actual;

        if (valor < actual->dato) {
            actual = actual->izq;
        } else if (valor > actual->dato) {
            actual = actual->der;
        } else {
            // Duplicado: no insertar
            delete nuevoNodo;
            return;
        }
    }

    // Insertar en posición correcta
    nuevoNodo->padre = padre;
    if (valor < padre->dato)
        padre->izq = nuevoNodo;
    else
        padre->der = nuevoNodo;
}

// BÚSQUEDA ITERATIVA: O(h)
Nodo* BST::buscarIterativo(int valor) {
    Nodo* actual = raiz;

    while (actual != nullptr) {
        if (valor == actual->dato)
            return actual;
        else if (valor < actual->dato)
            actual = actual->izq;
        else
            actual = actual->der;
    }
    return nullptr;
}

// ELIMINACIÓN ITERATIVA: O(h)
bool BST::eliminarIterativo(int valor) {
    Nodo* nodo = buscarIterativo(valor);
    if (nodo == nullptr) return false;

    // CASO 1: Nodo hoja
    if (nodo->izq == nullptr && nodo->der == nullptr) {
        if (nodo->padre == nullptr) {
            raiz = nullptr;
        } else {
            if (nodo->padre->izq == nodo)
                nodo->padre->izq = nullptr;
            else
                nodo->padre->der = nullptr;
        }
        delete nodo;
        return true;
    }

    // CASO 2: Un hijo
    if (nodo->izq == nullptr || nodo->der == nullptr) {
        Nodo* hijo = (nodo->izq != nullptr) ? nodo->izq : nodo->der;

        if (nodo->padre == nullptr) {
            raiz = hijo;
            hijo->padre = nullptr;
        } else {
            if (nodo->padre->izq == nodo)
                nodo->padre->izq = hijo;
            else
                nodo->padre->der = hijo;
            hijo->padre = nodo->padre;
        }
        delete nodo;
        return true;
    }

    // CASO 3: Dos hijos (reemplazar con sucesor)
    Nodo* sucesor = nodo->der;
    while (sucesor->izq != nullptr)
        sucesor = sucesor->izq;

    nodo->dato = sucesor->dato;
    Nodo* hijoSucesor = sucesor->der;

    if (nodo->der == sucesor) {
        nodo->der = hijoSucesor;
    } else {
        sucesor->padre->izq = hijoSucesor;
    }

    if (hijoSucesor != nullptr)
        hijoSucesor->padre = sucesor->padre;

    delete sucesor;
    return true;
}

// RECORRIDO IN-ORDER ITERATIVO: O(n)
void BST::recorridoInOrdenIterativo() {
    std::stack<Nodo*> pila;
    Nodo* actual = raiz;

    std::cout << "Recorrido In-Order: ";

    while (actual != nullptr || !pila.empty()) {
        // Descender al hijo izquierdo más lejano
        while (actual != nullptr) {
            pila.push(actual);
            actual = actual->izq;
        }

        // Pop del stack
        actual = pila.top();
        pila.pop();

        // Procesar nodo
        std::cout << actual->dato << " ";

        // Ir al hijo derecho
        actual = actual->der;
    }
    std::cout << std::endl;
}

// ALTURA: O(n)
int BST::calcularAltura(Nodo* nodo) {
    if (nodo == nullptr) return -1;
    return 1 + std::max(calcularAltura(nodo->izq), calcularAltura(nodo->der));
}

int BST::getAltura() {
    return calcularAltura(raiz);
}

int BST::contarNodos() {
    if (raiz == nullptr) return 0;

    int count = 0;
    std::stack<Nodo*> pila;
    pila.push(raiz);

    while (!pila.empty()) {
        Nodo* nodo = pila.top();
        pila.pop();
        count++;

        if (nodo->der != nullptr) pila.push(nodo->der);
        if (nodo->izq != nullptr) pila.push(nodo->izq);
    }
    return count;
}

void BST::imprimirPreOrden() {
    if (raiz == nullptr) {
        std::cout << "Árbol vacío" << std::endl;
        return;
    }

    std::stack<Nodo*> pila;
    pila.push(raiz);

    std::cout << "Recorrido Pre-Order: ";
    while (!pila.empty()) {
        Nodo* nodo = pila.top();
        pila.pop();
        std::cout << nodo->dato << " ";

        if (nodo->der != nullptr) pila.push(nodo->der);
        if (nodo->izq != nullptr) pila.push(nodo->izq);
    }
    std::cout << std::endl;
}

Nodo* BST::getRaiz() {
    return raiz;
}


/*
ANÁLISIS MATEMÁTICO: ¿POR QUÉ O(n)?

Inserción ordenada (1,2,3,4,5,...,n):
- Primer nodo: se inserta en raíz
- Segundo nodo: comparación 1, va a derecha
- Tercer nodo: comparaciones 2, va a derecha del derecho
- n-ésimo nodo: comparaciones n-1

ESTRUCTURA RESULTANTE (Lo veo como una cadena lineal):
    1
     \
      2
       \
        3
         \
          ...
           \
            n

Altura = n-1 = O(n)

Complejidad de inserción promedio:
- Suma = 0 + 1 + 2 + ... + (n-1) = n(n-1)/2 = O(n²)

CONCLUSIÓN: Entonces pued concluir que sin balanceo, el árbol degenera en lista enlazada, perdiendo la ventaja
            logarítmica del BST.
*/