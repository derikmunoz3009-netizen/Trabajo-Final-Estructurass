#ifndef CIUDAD_H
#define CIUDAD_H

#include "Nodo.h"
#include <iostream>
#include <cstdlib>  // Para usar rand() y srand()
#include <ctime>    // Para usar time()

using namespace std;

class Ciudad {
private:
    // El primer nodo del tablero (esquina arriba-izquierda)
    // De aquí podemos llegar a todos los demás nodos
    Nodo* inicioTablero;
    
    // Guardamos la posición actual del detective
    Nodo* posicionDetective;
    
    // Guardamos cuántos movimientos ha hecho (para el puntaje)
    int puntaje;

public:
    // Constructor: crea el tablero de 9x9
    Ciudad();
    
    // Destructor: libera memoria (aunque no lo usamos aquí)
    ~Ciudad();
    
    // Métodos principales
    
    // Crea el tablero 9x9 con la lista múltiplemente enlazada
    void crearTablero();
    
    // Coloca los bordes '#' alrededor del tablero
    void colocarBordes();
    
    // Coloca los callejones '|' de forma aleatoria (16 callejones)
    void colocarCallejones();
    
    // Coloca al detective 'D' en una posición aleatoria válida
    void colocarDetective();
    
    // Imprime el tablero en la pantalla
    void imprimirTablero();
    
    // Mueve el detective en la dirección indicada (W, A, S, D)
    bool moverDetective(char direccion);
    
    // Obtiene un nodo aleatorio válido (para colocar el detective, pistas, etc.)
    Nodo* obtenerPosicionAleatoria();
    
    // Valida si una posición es válida (no es borde, no es callejón, etc.)
    bool esValidaParaDetective(Nodo* nodo);
    
    // Retorna el nodo inicial del tablero
    Nodo* getInicioTablero();
    
    // Retorna la posición actual del detective
    Nodo* getPosicionDetective();
    
    // Retorna el puntaje actual
    int getPuntaje();
    
    // Aumenta el puntaje en 1 (cada movimiento suma 1 punto)
    void aumentarPuntaje();
};

#endif
