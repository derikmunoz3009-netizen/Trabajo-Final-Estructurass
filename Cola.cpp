#include "Cola.h"
#include <iostream>
using namespace std;

Cola::Cola() : frente(nullptr), final_(nullptr), tamano(0) {}

Cola::~Cola() {
    while (!estaVacia()) {
        NodoCola* tmp = frente;
        frente = frente->siguiente;
        delete tmp;
    }
}

void Cola::encolar(string declaracion) {
    NodoCola* nuevo = new NodoCola(declaracion);
    if (estaVacia()) {
        frente = nuevo;
        final_ = nuevo;
    } else {
        final_->siguiente = nuevo;
        final_ = nuevo;
    }
    tamano++;
}

string Cola::desencolar() {
    if (estaVacia()) return "";
    NodoCola* tmp = frente;
    string dec = frente->declaracion;
    frente = frente->siguiente;
    if (frente == nullptr) final_ = nullptr;
    delete tmp;
    tamano--;
    return dec;
}

bool Cola::estaVacia() const { return frente == nullptr; }
int  Cola::getTamano() const { return tamano; }

void Cola::mostrar() const {
    if (estaVacia()) {
        cout << "  No hay testigos por interrogar." << endl;
        return;
    }
    cout << "  Testigos en cola: " << tamano << endl;
    NodoCola* actual = frente;
    int i = 1;
    while (actual != nullptr) {
        cout << "  " << i << ". " << actual->declaracion << endl;
        actual = actual->siguiente;
        i++;
    }
}
