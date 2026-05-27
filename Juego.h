#ifndef JUEGO_H
#define JUEGO_H

#include "Mapa.h"
#include "Detective.h"
#include "Pila.h"
#include "Cola.h"
#include "TablaHash.h"
#include "ABB.h"
#include <string>
#include <vector>
using namespace std;

class Juego {
private:
    Mapa*       mapa;
    Detective*  detective;
    Pila*       pilaPistas;
    Cola*       colaTestigos;
    TablaHash*  tablaSospechosos;
    ABB*        historial;

    bool juegoTerminado;
    bool casoResuelto;

    void inicializarSospechosos();
    void inicializarDetective();

    void moverDetective(char direccion);
    void usarPista();
    void interrogarTestigo();
    void mostrarPistas();
    void mostrarSospechosos();

    // CORREGIDO: ahora recibe bool para saber si fue forzada (tecla R)
    void faseFinal(bool acusacionForzada = false);

    string generarDeclaracion() const;
    void   aplicarEfectoPista(Pista* pista);

public:
    Juego();
    ~Juego();

    void iniciar();
};

#endif