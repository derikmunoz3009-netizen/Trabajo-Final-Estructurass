#include "Pista.h"

Pista::Pista() {
    this->tipo = 'H';
    this->posicion = Posicion();
}

Pista::Pista(char tipo, Posicion posicion) {
    this->tipo = tipo;
    this->posicion = posicion;
}

char Pista::getTipo() const {
    return tipo;
}

Posicion Pista::getPosicion() const {
    return posicion;
}

void Pista::setTipo(char tipo) {
    this->tipo = tipo;
}

void Pista::setPosicion(Posicion posicion) {
    this->posicion = posicion;
}

std::string Pista::getNombreTipo() const {
    if (tipo == 'H') return "Huella";
    if (tipo == 'C') return "Coartada";
    if (tipo == 'T') return "Testimonio";
    if (tipo == 'P') return "Prueba forense";
    return "Pista desconocida";
}
