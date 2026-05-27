#include "Pila.h"
#include <iostream>
using namespace std;

Pila::Pila() : tope(nullptr), tamano(0) {}

Pila::~Pila() {
    while (!estaVacia()) {
        NodoPila* tmp = tope;
        tope = tope->siguiente;
        delete tmp;
    }
}

void Pila::push(Pista* pista) {
    NodoPila* nuevo = new NodoPila(pista);
    nuevo->siguiente = tope;
    tope = nuevo;
    tamano++;
}

Pista* Pila::pop() {
    if (estaVacia()) return nullptr;
    NodoPila* tmp = tope;
    Pista* p = tope->pista;
    tope = tope->siguiente;
    delete tmp;
    tamano--;
    return p;
}

Pista* Pila::peek() const {
    if (estaVacia()) return nullptr;
    return tope->pista;
}

bool Pila::estaVacia() const { return tope == nullptr; }
int  Pila::getTamano() const { return tamano; }

void Pila::mostrar() const {
    if (estaVacia()) {
        cout << "  No has recogido pistas aun." << endl;
        return;
    }
    cout << "  ['# #']" << endl;
    cout << "  ['# #']" << endl;
    NodoPila* actual = tope;
    int pos = tamano;
    while (actual != nullptr) {
        cout << "  ['# " << actual->pista->getSimbolo() << " #']";
        if (pos == tamano)     cout << " <- ultima (se usa con X)";
        if (pos == tamano - 1) cout << " <- penultima";
        if (pos == tamano - 2) cout << " <- antepenultima";
        cout << endl;
        actual = actual->siguiente;
        pos--;
    }
    cout << "  ['# #']" << endl;
}
