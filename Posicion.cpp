#include "Posicion.h"

Posicion::Posicion() {
    this->fila = 0;
    this->columna = 0;
}

Posicion::Posicion(int fila, int columna) {
    this->fila = fila;
    this->columna = columna;
}

int Posicion::getFila() const {
    return fila;
}

int Posicion::getColumna() const {
    return columna;
}

void Posicion::setFila(int fila) {
    this->fila = fila;
}

void Posicion::setColumna(int columna) {
    this->columna = columna;
}

bool Posicion::esIgual(const Posicion& otra) const {
    return fila == otra.fila && columna == otra.columna;
}