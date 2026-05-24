#ifndef NODO_H
#define NODO_H

// Incluimos string para poder usar textos
#include <string>

using namespace std;

class Nodo {
private:
    // Contenido de la casilla: 'o' (no visitado), ' ' (vacío), '#' (borde), '|' (callejón), 'D' (detective)
    char contenido;
    
    // Booleano para saber si ya fue visitado por el detective
    bool visitado;
    
    // Punteros para conectar con otros nodos en las 4 direcciones
    // Esta es la LISTA MÚLTIPLEMENTE ENLAZADA
    Nodo* arriba;      // Apunta al nodo de arriba
    Nodo* abajo;       // Apunta al nodo de abajo
    Nodo* izquierda;   // Apunta al nodo de la izquierda
    Nodo* derecha;     // Apunta al nodo de la derecha

public:
    // Constructor: crea un nodo con un contenido inicial
    Nodo(char contenido);
    
    // Destructor: libera la memoria (aunque en este proyecto no lo usamos mucho)
    ~Nodo();
    
    // GETTERS - Métodos para obtener información del nodo
    char getContenido();           // Retorna el contenido de la casilla
    bool getVisitado();            // Retorna si fue visitado
    Nodo* getArriba();             // Retorna el puntero del nodo arriba
    Nodo* getAbajo();              // Retorna el puntero del nodo abajo
    Nodo* getIzquierda();          // Retorna el puntero del nodo izquierda
    Nodo* getDerechaC();            // Retorna el puntero del nodo derecha
    
    // SETTERS - Métodos para cambiar la información del nodo
    void setContenido(char contenido);     // Cambia el contenido
    void setVisitado(bool visitado);       // Marca como visitado o no
    void setArriba(Nodo* nodo);            // Conecta con el nodo arriba
    void setAbajo(Nodo* nodo);             // Conecta con el nodo abajo
    void setIzquierda(Nodo* nodo);         // Conecta con el nodo izquierda
    void setDerecha(Nodo* nodo);           // Conecta con el nodo derecha
};

#endif
