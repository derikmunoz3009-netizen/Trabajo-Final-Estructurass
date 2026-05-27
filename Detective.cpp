#include "Detective.h"
#include <iostream>
using namespace std;

Detective::Detective()
    : nombre(""), fila(0), columna(0), puntaje(0), pistasRecogidas(0) {}

Detective::Detective(string nombre, int filaInicial, int columnaInicial)
    : nombre(nombre), fila(filaInicial), columna(columnaInicial),
      puntaje(0), pistasRecogidas(0) {}

string Detective::getNombre()          const { return nombre; }
int    Detective::getFila()            const { return fila; }
int    Detective::getColumna()         const { return columna; }
int    Detective::getPuntaje()         const { return puntaje; }
int    Detective::getPistasRecogidas() const { return pistasRecogidas; }

void Detective::setFila(int f)            { fila = f; }
void Detective::setColumna(int c)         { columna = c; }
void Detective::setPosicion(int f, int c) { fila = f; columna = c; }

void Detective::sumarPunto()          { puntaje++; }
void Detective::reducirPuntajeMitad() { puntaje = puntaje / 2; }
void Detective::duplicarPuntaje()     { puntaje = puntaje * 2; }
void Detective::resetPuntaje()        { puntaje = 0; }

void Detective::teleportar(int f, int c) { fila = f; columna = c; }

void Detective::agregarPista() { pistasRecogidas++; }
void Detective::quitarPista()  { if (pistasRecogidas > 0) pistasRecogidas--; }

bool Detective::haGanado() const { return pistasRecogidas >= 10; }

void Detective::mostrarEstado() const {
    cout << "  " << nombre << ", tu puntaje actual es: " << puntaje
         << " | Pistas: " << pistasRecogidas << "/10" << endl;
}
