#ifndef ABBPUNTAJES_H   // Protección contra inclusión doble
#define ABBPUNTAJES_H

#include <string>   // Para usar string
using namespace std;

// ============================================================
// ESTRUCTURA NodoABB
// Representa un nodo del árbol binario de búsqueda
// Cada nodo guarda el nombre y puntaje de un detective
// ============================================================
struct NodoABB {
    string nombreDetective;   // Nombre del detective
    int puntaje;              // Su mejor puntaje (menor = mejor)
    NodoABB* izquierda;       // Puntero al hijo izquierdo (puntajes menores)
    NodoABB* derecha;         // Puntero al hijo derecho (puntajes mayores)

    // Constructor del nodo
    NodoABB(string nombre, int puntaje) {
        this->nombreDetective = nombre;   // Guarda el nombre
        this->puntaje = puntaje;          // Guarda el puntaje
        this->izquierda = nullptr;        // Sin hijo izquierdo al crearse
        this->derecha = nullptr;          // Sin hijo derecho al crearse
    }
};

// ============================================================
// CLASE ABBPuntajes
// Árbol Binario de Búsqueda para guardar puntajes históricos
// Organizado por PUNTAJE (menor puntaje = mejor = más a la izquierda)
// ============================================================
class ABBPuntajes {

private:
    NodoABB* raiz;   // Nodo raíz del árbol (punto de entrada)

    // Métodos auxiliares privados (se usan internamente con recursión)
    NodoABB* insertarRec(NodoABB* nodo, string nombre, int puntaje);   // Inserción recursiva
    NodoABB* buscarNombreRec(NodoABB* nodo, string nombre);            // Búsqueda por nombre
    void mostrarOrdenadoRec(NodoABB* nodo);                            // Recorrido InOrden
    void liberarMemoria(NodoABB* nodo);                                // Destructor recursivo

public:
    // Constructor: árbol vacío
    ABBPuntajes();

    // Destructor: libera toda la memoria del árbol
    ~ABBPuntajes();

    // Inserta o actualiza el puntaje de un detective
    // Si ya existe, conserva el puntaje menor (mejor)
    void insertarPuntaje(string nombre, int puntaje);

    // Busca si un detective ya jugó antes y muestra su mejor puntaje
    void buscarDetective(string nombre);

    // Muestra todos los detectives ordenados de menor a mayor puntaje
    void mostrarRanking();
};

#endif