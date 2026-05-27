#include "ABB.h"
#include <iostream>
using namespace std;

ABB::ABB() : raiz(nullptr) {}
ABB::~ABB() { destruir(raiz); }

void ABB::destruir(NodoABB* nodo) {
    if (nodo == nullptr) return;
    destruir(nodo->izquierda);
    destruir(nodo->derecha);
    delete nodo;
}

NodoABB* ABB::insertar(NodoABB* nodo, string nombre, int puntaje) {
    if (nodo == nullptr)
        return new NodoABB(nombre, puntaje);
    if (puntaje < nodo->puntaje)
        nodo->izquierda = insertar(nodo->izquierda, nombre, puntaje);
    else if (puntaje > nodo->puntaje)
        nodo->derecha = insertar(nodo->derecha, nombre, puntaje);
    return nodo;
}

NodoABB* ABB::buscar(NodoABB* nodo, string nombre) const {
    if (nodo == nullptr) return nullptr;
    if (nodo->nombre == nombre) return nodo;
    NodoABB* izq = buscar(nodo->izquierda, nombre);
    if (izq != nullptr) return izq;
    return buscar(nodo->derecha, nombre);
}

void ABB::mostrarOrdenado(NodoABB* nodo) const {
    if (nodo == nullptr) return;
    mostrarOrdenado(nodo->izquierda);
    cout << "  " << nodo->nombre
         << " -> " << nodo->puntaje << " movimientos" << endl;
    mostrarOrdenado(nodo->derecha);
}

void ABB::guardarPuntaje(string nombre, int puntaje) {
    NodoABB* existente = buscar(raiz, nombre);
    if (existente != nullptr) {
        if (puntaje < existente->puntaje)
            existente->puntaje = puntaje;
        return;
    }
    raiz = insertar(raiz, nombre, puntaje);
}

int ABB::getMejorPuntaje(string nombre) const {
    NodoABB* nodo = buscar(raiz, nombre);
    if (nodo == nullptr) return -1;
    return nodo->puntaje;
}

bool ABB::haJugado(string nombre) const {
    return buscar(raiz, nombre) != nullptr;
}

void ABB::mostrarRanking() const {
    if (raiz == nullptr) {
        cout << "  No hay puntajes registrados aun." << endl;
        return;
    }
    cout << "  -- Ranking de Detectives --" << endl;
    mostrarOrdenado(raiz);
}
