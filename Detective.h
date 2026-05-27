#ifndef DETECTIVE_H
#define DETECTIVE_H

#include <string>
using namespace std;

class Detective {
private:
    string nombre;
    int fila;
    int columna;
    int puntaje;
    int pistasRecogidas;

public:
    Detective();
    Detective(string nombre, int filaInicial, int columnaInicial);

    string getNombre()          const;
    int    getFila()            const;
    int    getColumna()         const;
    int    getPuntaje()         const;
    int    getPistasRecogidas() const;

    void setFila(int fila);
    void setColumna(int columna);
    void setPosicion(int fila, int columna);

    void sumarPunto();
    void reducirPuntajeMitad();
    void duplicarPuntaje();
    void resetPuntaje();
    void teleportar(int nuevaFila, int nuevaColumna);

    void agregarPista();
    void quitarPista();
    bool haGanado() const;

    void mostrarEstado() const;
};

#endif
