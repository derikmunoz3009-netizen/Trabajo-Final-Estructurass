#ifndef GESTORPISTASTESTIGOS_H
#define GESTORPISTASTESTIGOS_H

#include <stack>
#include <queue>
#include <list>
#include <string>
#include "Pista.h"
#include "Testigo.h"
#include "IAccionesCiudad.h"

class GestorPistasTestigos {
private:
    std::stack<Pista> pilaPistas;
    std::queue<Testigo> colaTestigos;
    std::list<Pista> pistasOcultas;
    std::list<Testigo> testigosEnMapa;
    int pistasRecogidas;

    char generarTipoPistaAleatorio() const;
    bool posicionOcupada(Posicion posicion) const;

public:
    GestorPistasTestigos();

    void agregarPosicionesAleatorias(std::list<Posicion> posicionesLibres);
    void generarPistas(std::list<Posicion>& posicionesLibres);
    void generarTestigos(std::list<Posicion>& posicionesLibres);

    bool hayPistaEn(Posicion posicion) const;
    bool hayTestigoEn(Posicion posicion) const;

    bool recogerPista(Posicion posicion);
    bool recogerTestigo(Posicion posicion);

    void mostrarPistas() const;
    void mostrarColaTestigos() const;

    void usarUltimaPista(int& puntaje, IAccionesCiudad& ciudad);
    void interrogarTestigo();

    int getPistasRecogidas() const;
    bool completoLas10Pistas() const;
};

#endif
