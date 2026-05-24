#ifndef PISTA_H
#define PISTA_H

#include <string>
#include "Posicion.h"

class Pista {
private:
    char tipo;
    Posicion posicion;

public:
    Pista();
    Pista(char tipo, Posicion posicion);

    char getTipo() const;
    Posicion getPosicion() const;

    void setTipo(char tipo);
    void setPosicion(Posicion posicion);

    std::string getNombreTipo() const;
};

#endif
