#include "TablaHash.h"
#include <iostream>
using namespace std;

TablaHash::TablaHash() : tabla(TAMANO, nullptr) {}

TablaHash::~TablaHash() {
    for (int i = 0; i < TAMANO; i++) {
        NodoHash* actual = tabla[i];
        while (actual != nullptr) {
            NodoHash* tmp = actual;
            actual = actual->siguiente;
            delete tmp;
        }
    }
}

int TablaHash::funcionHash(const string& nombre) const {
    const int BASE  = 31;
    const int PRIMO = 11;
    long long hash  = 0;
    for (char c : nombre)
        hash = (hash * BASE + (unsigned char)c) % PRIMO;
    return (int)hash;
}

void TablaHash::insertar(const string& nombre, const Sospechoso& s) {
    int indice = funcionHash(nombre);
    NodoHash* nuevo = new NodoHash(nombre, s);
    nuevo->siguiente = tabla[indice];
    tabla[indice]    = nuevo;
}

Sospechoso* TablaHash::buscar(const string& nombre) {
    int indice = funcionHash(nombre);
    NodoHash* actual = tabla[indice];
    while (actual != nullptr) {
        if (actual->nombre == nombre)
            return &actual->sospechoso;
        actual = actual->siguiente;
    }
    return nullptr;
}

bool TablaHash::existe(const string& nombre) const {
    int indice = funcionHash(nombre);
    NodoHash* actual = tabla[indice];
    while (actual != nullptr) {
        if (actual->nombre == nombre) return true;
        actual = actual->siguiente;
    }
    return false;
}

void TablaHash::revelarAtributoACulpable() {
    for (int i = 0; i < TAMANO; i++) {
        NodoHash* actual = tabla[i];
        while (actual != nullptr) {
            if (actual->sospechoso.getEsCulpable()) {
                actual->sospechoso.revelarSiguienteAtributo();
                return;
            }
            actual = actual->siguiente;
        }
    }
}

void TablaHash::mostrar() const {
    cout << "  Sospechosos del caso:" << endl;
    for (int i = 0; i < TAMANO; i++) {
        NodoHash* actual = tabla[i];
        while (actual != nullptr) {
            actual->sospechoso.mostrar();
            actual = actual->siguiente;
        }
    }
}

string TablaHash::getNombreCulpable() const {
    for (int i = 0; i < TAMANO; i++) {
        NodoHash* actual = tabla[i];
        while (actual != nullptr) {
            if (actual->sospechoso.getEsCulpable())
                return actual->nombre;
            actual = actual->siguiente;
        }
    }
    return "";
}
