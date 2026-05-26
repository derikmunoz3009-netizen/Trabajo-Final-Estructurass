#ifndef TESTIGO_H
#define TESTIGO_H

#include <string>
#include "Posicion.h"

class Testigo {
private:
    std::string nombre;
    std::string declaracion;
    Posicion posicion;

public:
    Testigo();
    Testigo(std::string nombre, std::string declaracion, Posicion posicion);

    std::string getNombre() const;
    std::string getDeclaracion() const;
    Posicion getPosicion() const;

    void setNombre(std::string nombre);
    void setDeclaracion(std::string declaracion);
    void setPosicion(Posicion posicion);
};

#endif