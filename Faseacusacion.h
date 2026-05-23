// ============================================================
// FaseAcusacion.h
// Maneja la fase final del juego: el jugador acusa a un sospechoso
// ============================================================

#ifndef FASEACUSACION_H   // Protección contra inclusión doble
#define FASEACUSACION_H

#include "HashSospechosos.h"   // Necesitamos la tabla de sospechosos
#include "ABBPuntajes.h"       // Necesitamos el árbol de puntajes
#include <string>
using namespace std;

// ============================================================
// CLASE FaseAcusacion
// Controla todo lo que pasa cuando el jugador recoge las 10 pistas
// ============================================================
class FaseAcusacion {

public:
    // ============================================================
    // ejecutar
    // Llama a esta función cuando el detective recogió las 10 pistas
    // Recibe:
    //   - hash: la tabla con los sospechosos
    //   - abb: el árbol con los puntajes históricos
    //   - nombreDetective: nombre del jugador actual
    //   - puntajeActual: cuántos movimientos lleva
    // Devuelve: el puntaje final (puede cambiar si la acusación es incorrecta)
    // ============================================================
    static int ejecutar(HashSospechosos& hash, ABBPuntajes& abb,
                        string nombreDetective, int puntajeActual);
};

#endif