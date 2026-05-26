#include "Nodo.h"

// CONSTRUCTOR: Inicializa un nodo con su contenido
// Se ejecuta cuando hacemos: Nodo* n = new Nodo('o');
Nodo::Nodo(char contenido) {
    this->contenido = contenido;  // Asigna el contenido que recibe
    this->visitado = false;       // Inicialmente no está visitado

    // Los punteros comienzan en NULL (no apuntan a nada)
    this->arriba = NULL;
    this->abajo = NULL;
    this->izquierda = NULL;
    this->derecha = NULL;
}

// DESTRUCTOR: Se llama cuando el nodo se elimina (con delete)
Nodo::~Nodo() {
    // En este proyecto no eliminamos nodos, así que está vacío
}

// ===== GETTERS (métodos para LEER información) =====

// Retorna el carácter que hay en esta casilla
char Nodo::getContenido() {
    return this->contenido;
}

// Retorna TRUE si la casilla ya fue visitada, FALSE si no
bool Nodo::getVisitado() {
    return this->visitado;
}

// Retorna el puntero del nodo que está ARRIBA de este
Nodo* Nodo::getArriba() {
    return this->arriba;
}

// Retorna el puntero del nodo que está ABAJO de este
Nodo* Nodo::getAbajo() {
    return this->abajo;
}

// Retorna el puntero del nodo que está a la IZQUIERDA de este
Nodo* Nodo::getIzquierda() {
    return this->izquierda;
}

// Retorna el puntero del nodo que está a la DERECHA de este
Nodo* Nodo::getDerecha() {
    return this->derecha;
}

// ===== SETTERS (métodos para CAMBIAR información) =====

// Cambia el contenido de esta casilla
// Por ejemplo: de 'o' a ' ' cuando se descubre
void Nodo::setContenido(char contenido) {
    this->contenido = contenido;
}

// Marca esta casilla como visitada (true) o no visitada (false)
void Nodo::setVisitado(bool visitado) {
    this->visitado = visitado;
}

// Conecta este nodo con el nodo que está ARRIBA
// Esto es lo que hace la "lista múltiplemente enlazada"
void Nodo::setArriba(Nodo* nodo) {
    this->arriba = nodo;  // Guardamos la dirección de memoria del nodo de arriba
}

// Conecta este nodo con el nodo que está ABAJO
void Nodo::setAbajo(Nodo* nodo) {
    this->abajo = nodo;  // Guardamos la dirección de memoria del nodo de abajo
}

// Conecta este nodo con el nodo que está a la IZQUIERDA
void Nodo::setIzquierda(Nodo* nodo) {
    this->izquierda = nodo;  // Guardamos la dirección de memoria del nodo de izquierda
}

// Conecta este nodo con el nodo que está a la DERECHA
void Nodo::setDerecha(Nodo* nodo) {
    this->derecha = nodo;  // Guardamos la dirección de memoria del nodo de derecha
}