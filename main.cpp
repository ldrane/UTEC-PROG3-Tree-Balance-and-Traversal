#include <iostream>
#include <cmath>
#include "BST.h"
#include "RedBlackTree.h"

// Declaraciones de funciones de otros problemas
void problema3();
void problema4();

void problema1() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "PROBLEMA 1: BST ITERATIVO Y ANALISIS DE DEGRADACION" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    BST arbol;

    // Insertar 20 elementos
    int elementos[] = {50, 30, 70, 20, 40, 60, 80, 10, 35, 65,
                       25, 45, 55, 75, 15, 5, 55, 85, 27, 77};

    std::cout << "\nInsertando 20 elementos: ";
    for (int i = 0; i < 20; i++) {
        arbol.insertarIterativo(elementos[i]);
        std::cout << elementos[i] << " ";
    }
    std::cout << std::endl;

    // Eliminar 2 elementos
    std::cout << "\nEliminando 5 y 75:" << std::endl;
    arbol.eliminarIterativo(5);
    arbol.eliminarIterativo(75);

    // Recorrido in-order
    arbol.recorridoInOrdenIterativo();

    // Pre-order
    arbol.imprimirPreOrden();

    // Métricas
    std::cout << "\nMETRICS DEL BST:" << std::endl;
    std::cout << "   Altura: " << arbol.getAltura() << std::endl;
    std::cout << "   Nodos: " << arbol.contarNodos() << std::endl;

    // Análisis de degradación
    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "ANALISIS DE DEGRADACION CON DATOS ORDENADOS" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    BST arbolDegradado;
    std::cout << "\nInsertando numeros 1-20 en orden (peor caso):" << std::endl;
    for (int i = 1; i <= 20; i++) {
        arbolDegradado.insertarIterativo(i);
    }

    std::cout << "\nMETRICS DEL BST DEGRADADO:" << std::endl;
    std::cout << "   Altura: " << arbolDegradado.getAltura() << std::endl;
    std::cout << "   Nodos: " << arbolDegradado.contarNodos() << std::endl;

    std::cout << "\nANALISIS MATEMATICO:" << std::endl;
    std::cout << "   Insercion ordenada crea una cadena lineal" << std::endl;
    std::cout << "   Altura = n - 1 = 19" << std::endl;
    std::cout << "   Complejidad: O(n) en lugar de O(log n)" << std::endl;
    std::cout << "   Razon: Sin balanceo, cada busqueda requiere O(n) comparaciones en peor caso" << std::endl;
}

void problema2() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "PROBLEMA 2: RED-BLACK TREE AUTO-BALANCEADO" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    RedBlackTree rbtree;

    // Insertar 20 elementos (mismos que problema 1)
    int elementos[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    std::cout << "\n Insertando numeros 1-20 en ORDEN:" << std::endl;
    for (int i = 0; i < 20; i++) {
        rbtree.insertar(elementos[i]);
    }

    // Mostrar propiedades
    rbtree.imprimirPreOrden();

    std::cout << "\nValidando propiedades RB-Tree: " << (rbtree.validarPropiedades() ? "VALIDO" : "INVALIDO") << std::endl;

    std::cout << "\nMETRICS DEL RED-BLACK TREE:" << std::endl;
    std::cout << "   Altura: " << rbtree.getAltura() << std::endl;
    std::cout << "   Nodos: " << rbtree.contarNodos() << std::endl;

    // Comparación
    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "COMPARACION: BST vs RED-BLACK TREE (con datos 1-20)" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    BST bstOrdenado;
    for (int i = 1; i <= 20; i++) {
        bstOrdenado.insertarIterativo(i);
    }

    int alturaBST = bstOrdenado.getAltura();
    int alturaRB = rbtree.getAltura();

    std::cout << "\n RESULTADOS:" << std::endl;
    std::cout << "   BST (datos ordenados):     altura = " << alturaBST << std::endl;
    std::cout << "   Red-Black Tree:            altura = " << alturaRB << std::endl;
    std::cout << "   Mejora: " << ((alturaBST - alturaRB) * 100.0 / alturaBST)
              << "% menor" << std::endl;

    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "ANALISIS MATEMATICO: ALTURA O(log n)" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::cout << "\nTEOREMA: h <= 2*log2(n+1)" << std::endl;
    std::cout << "\nPara n = 20 nodos:" << std::endl;
    std::cout << "   log2(21) = " << (log(21) / log(2)) << std::endl;
    std::cout << "   2*log2(21) = " << (2 * log(21) / log(2)) << std::endl;
    std::cout << "   Altura maxima teorica = aprox. "
              << (int)(2 * log(21) / log(2)) + 1 << std::endl;
    std::cout << "   Altura observada = " << alturaRB << std::endl;

    std::cout << "\nCONCLUSION:" << std::endl;
    std::cout << "   Considerando el peor caso, Red-Black Tree mantiene altura O(log n) incluso con insercion ordenada mediante rotaciones (O(1) cada una)y recoloracion (O(log n) en peor caso) " << std::endl;
}

int main() {
    problema1();
    problema2();
    problema3();
    problema4();

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "TODAS LAS PRUEBAS COMPLETADAS" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    return 0;
}