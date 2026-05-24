#include "Testigo.h"

Testigo::Testigo() {
    this->nombre = "Testigo";
    this->declaracion = "Tiene informacion importante del caso.";
    this->posicion = Posicion();
}

Testigo::Testigo(std::string nombre, std::string declaracion, Posicion posicion) {
    this->nombre = nombre;
    this->declaracion = declaracion;
    this->posicion = posicion;
}

std::string Testigo::getNombre() const {
    return nombre;
}

std::string Testigo::getDeclaracion() const {
    return declaracion;
}

Posicion Testigo::getPosicion() const {
    return posicion;
}

void Testigo::setNombre(std::string nombre) {
    this->nombre = nombre;
}

void Testigo::setDeclaracion(std::string declaracion) {
    this->declaracion = declaracion;
}

void Testigo::setPosicion(Posicion posicion) {
    this->posicion = posicion;
}
