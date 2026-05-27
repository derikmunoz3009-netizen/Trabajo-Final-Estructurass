#ifndef MAPA_H
#define MAPA_H

#include "Ubicacion.h"
#include <vector>
using namespace std;

class Mapa {
private:
    static const int FILAS    = 11;
    static const int COLUMNAS = 11;

    Ubicacion* celdas[11][11];

    void construirCeldas();
    void conectarCeldas();
    void ubicarParedes();
    void ubicarCallejones();
    void ubicarPistas();
    void ubicarTestigos();

    bool esPosicionLibre(int fila, int col) const;

public:
    Mapa();
    ~Mapa();

    Ubicacion* getCelda(int fila, int col) const;
    Ubicacion* getPosicionAleatoria() const;

    void imprimirTablero(int detectiveFila, int detectiveColumna) const;
    void resetearVisibilidad();

    bool hayPistaEn(int fila, int col) const;
    bool hayTestigoEn(int fila, int col) const;
    bool esTransitable(int fila, int col) const;

    void eliminarCallejonesAleatorios(int cantidad);
};

#endif
