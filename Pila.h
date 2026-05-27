#ifndef PILA_H
#define PILA_H

#include "Pista.h"

struct NodoPila {
    Pista* pista;
    NodoPila* siguiente;
    NodoPila(Pista* p) : pista(p), siguiente(nullptr) {}
};

class Pila {
private:
    NodoPila* tope;
    int tamano;

public:
    Pila();
    ~Pila();

    void   push(Pista* pista);
    Pista* pop();
    Pista* peek() const;
    bool   estaVacia() const;
    int    getTamano() const;

    void mostrar() const;
};

#endif
