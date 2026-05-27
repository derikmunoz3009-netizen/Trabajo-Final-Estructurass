#ifndef ABB_H
#define ABB_H

#include <string>
using namespace std;

struct NodoABB {
    string nombre;
    int puntaje;
    NodoABB* izquierda;
    NodoABB* derecha;
    NodoABB(string n, int p)
        : nombre(n), puntaje(p),
          izquierda(nullptr), derecha(nullptr) {}
};

class ABB {
private:
    NodoABB* raiz;

    NodoABB* insertar(NodoABB* nodo, string nombre, int puntaje);
    NodoABB* buscar(NodoABB* nodo, string nombre) const;
    void     mostrarOrdenado(NodoABB* nodo) const;
    void     destruir(NodoABB* nodo);

public:
    ABB();
    ~ABB();

    void guardarPuntaje(string nombre, int puntaje);
    int  getMejorPuntaje(string nombre) const;
    bool haJugado(string nombre) const;
    void mostrarRanking() const;
};

#endif
