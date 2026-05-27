#include "Ubicacion.h"
#include <iostream>
using namespace std;

Ubicacion::Ubicacion()
    : fila(0), columna(0), tipo(VACIO),
      visitada(false), visible(false), pista(nullptr),
      arriba(nullptr), abajo(nullptr),
      izquierda(nullptr), derecha(nullptr) {}

Ubicacion::Ubicacion(int fila, int columna, TipoUbicacion tipo)
    : fila(fila), columna(columna), tipo(tipo),
      visitada(false), visible(false), pista(nullptr),
      arriba(nullptr), abajo(nullptr),
      izquierda(nullptr), derecha(nullptr) {}

Ubicacion::~Ubicacion() {}

int           Ubicacion::getFila()    const { return fila; }
int           Ubicacion::getColumna() const { return columna; }
TipoUbicacion Ubicacion::getTipo()    const { return tipo; }
bool          Ubicacion::isVisitada() const { return visitada; }
bool          Ubicacion::isVisible()  const { return visible; }
Pista*        Ubicacion::getPista()   const { return pista; }

void Ubicacion::setTipo(TipoUbicacion t) { tipo = t; }

void Ubicacion::visitar() {
    visitada = true;
    visible  = true;
}

void Ubicacion::hacerVisible() {
    visible = true;
}

void Ubicacion::resetVisita() {
    visitada = false;
    visible  = false;
}

void Ubicacion::setPista(Pista* p) { pista = p; }

void Ubicacion::quitarPista() {
    pista = nullptr;
    tipo  = VACIO;
}

char Ubicacion::getSimbolo(int detectiveFila, int detectiveColumna) const {
    if (fila == detectiveFila && columna == detectiveColumna)
        return 'I';

    switch (tipo) {
        case PARED:
            return '#';
        case CALLEJON:
            return visible ? '|' : 'o';
        case CON_TESTIGO:
            return visitada ? 'W' : 'o';
        case CON_PISTA:
            return visitada ? ' ' : 'o';
        case VACIO:
            return visitada ? ' ' : 'o';
        default:
            return 'o';
    }
}
