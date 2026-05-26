#include "Ciudad.h"

// CONSTRUCTOR: Inicializa la ciudad y crea el tablero
Ciudad::Ciudad() {
    this->inicioTablero = NULL;    // Todavía no hay tablero
    this->posicionDetective = NULL; // El detective no tiene posición
    this->puntaje = 0;             // Comienza sin puntos

    // Crear el tablero
    this->crearTablero();

    // Colocar los bordes '#'
    this->colocarBordes();

    // Colocar los callejones '|'
    this->colocarCallejones();

    // Colocar al detective 'D'
    this->colocarDetective();
}

// DESTRUCTOR: Aquí deberíamos liberar toda la memoria
Ciudad::~Ciudad() {
}

// ============================================
// MÉTODO: crearTablero()}}
// Crea una lista múltiplemente enlazada de 11x11 nodos
// (11 porque incluye los bordes)
// ============================================
void Ciudad::crearTablero() {
    // Creamos el tablero fila por fila
    // El tablero es 11x11 (9x9 internos + 2 filas/columnas de bordes)

    Nodo* nodoActual = NULL;
    Nodo* nodoAnterior = NULL;
    Nodo* inicioFila = NULL;
    Nodo* nodoArriba = NULL;

    // Recorremos 11 filas (0 a 10)
    for (int fila = 0; fila < 11; fila++) {
        // Para cada fila, recorremos 11 columnas (0 a 10)
        for (int columna = 0; columna < 11; columna++) {
            // Creamos un nuevo nodo con contenido 'o' (no visitado)
            nodoActual = new Nodo('o');

            // Si es el primer nodo del tablero, lo guardamos
            if (this->inicioTablero == NULL) {
                this->inicioTablero = nodoActual;
            }

            // Conectar con el nodo anterior (izquierda)
            if (nodoAnterior != NULL) {
                nodoActual->setIzquierda(nodoAnterior);     // El nuevo apunta a lo anterior
                nodoAnterior->setDerecha(nodoActual);       // Lo anterior apunta al nuevo
            }

            // Guardar como anterior para la siguiente iteración
            nodoAnterior = nodoActual;

            // Si es la primera columna, guardamos el inicio de la fila
            if (columna == 0) {
                inicioFila = nodoActual;
            }
        }

        // Después de procesar una fila, conectamos con la fila anterior (arriba-abajo)
        if (fila > 0) {
            // nodoArriba es el nodo que está una fila arriba de donde estamos
            // Empezamos desde el inicio de la fila anterior
            Nodo* nodoArribaTemp = inicioFila;

            // Pero necesitamos retroceder una fila completa
            // Hacemos esto usando el método que ya existe

            // Guardamos la referencia al inicio de la fila anterior antes de cambiar
            if (fila == 1) {
                nodoArriba = this->inicioTablero;
            }

            // Recorremos los nodos de la fila anterior
            Nodo* nodoActualFila = inicioFila;
            Nodo* nodoArribaFila = nodoArriba;

            // Conectamos cada nodo con el nodo que está arriba
            while (nodoActualFila != NULL && nodoArribaFila != NULL) {
                nodoActualFila->setArriba(nodoArribaFila);
                nodoArribaFila->setAbajo(nodoActualFila);

                // Avanzamos a la siguiente columna
                nodoActualFila = nodoActualFila->getDerecha();
                nodoArribaFila = nodoArribaFila->getDerecha();
            }

            // Guardamos el inicio de la fila actual como "anterior" para la siguiente
            nodoArriba = inicioFila;
        }

        // Para la siguiente fila, reseteamos nodoAnterior
        nodoAnterior = NULL;
    }
}

// ============================================
// MÉTODO: colocarBordes()
// Marca las primeras y últimas filas/columnas como '#' (bordes)
// ============================================
void Ciudad::colocarBordes() {
    // Usamos punteros para recorrer el tablero
    Nodo* nodoActual = this->inicioTablero;

    // Recorremos el tablero completo (11x11)
    for (int fila = 0; fila < 11; fila++) {
        for (int columna = 0; columna < 11; columna++) {
            // Si estamos en la primera o última fila, o primera o última columna
            if (fila == 0 || fila == 10 || columna == 0 || columna == 10) {
                // Es un borde, ponemos '#'
                nodoActual->setContenido('#');
            }

            // Avanzamos al siguiente nodo a la derecha
            if (columna < 10) {  // Si no es la última columna
                nodoActual = nodoActual->getDerecha();
            }
        }

        // Bajamos a la siguiente fila
        if (fila < 10) {  // Si no es la última fila
            nodoActual = nodoActual->getAbajo();
            // Retrocedemos al inicio de la fila
            while (nodoActual->getIzquierda() != NULL) {
                nodoActual = nodoActual->getIzquierda();
            }
        }
    }
}

// ============================================
// MÉTODO: colocarCallejones()
// Coloca 16 callejones '|' de forma aleatoria
// ============================================
void Ciudad::colocarCallejones() {
    int callejonesPuestos = 0;

    // Colocamos 16 callejones
    while (callejonesPuestos < 16) {
        // Obtener una posición aleatoria
        Nodo* posicion = this->obtenerPosicionAleatoria();

        // Solo colocamos si la casilla está vacía ('o')
        // Si ya hay un callejón, intentamos otra posición
        if (posicion != NULL && posicion->getContenido() == 'o') {
            posicion->setContenido('|');
            callejonesPuestos++;
        }
    }
}

// ============================================
// MÉTODO: colocarDetective()
// Coloca al detective 'D' en una posición aleatoria válida
// ============================================
void Ciudad::colocarDetective() {
    // Intentamos encontrar una posición válida
    Nodo* posicion = NULL;

    // Repetimos hasta encontrar un lugar válido
    while (posicion == NULL) {
        // Obtenemos una posición aleatoria
        Nodo* candidato = this->obtenerPosicionAleatoria();

        // Verificamos si es válida (no borde, no callejón)
        if (this->esValidaParaDetective(candidato)) {
            posicion = candidato;
        }
    }

    // Colocamos al detective en esa posición
    this->posicionDetective = posicion;
    posicion->setContenido('D');
    posicion->setVisitado(true);  // El detective comienza en una casilla visitada
}

// ============================================
// MÉTODO: obtenerPosicionAleatoria()
// Retorna un nodo aleatorio del tablero
// ============================================
Nodo* Ciudad::obtenerPosicionAleatoria() {
    // Número aleatorio entre 0 y 10 (filas)
    int filaAleatorio = rand() % 11;

    // Número aleatorio entre 0 y 10 (columnas)
    int columnaAleatorio = rand() % 11;

    // Empezamos desde el inicio del tablero
    Nodo* nodoActual = this->inicioTablero;

    // Bajamos hasta la fila aleatoria
    for (int fila = 0; fila < filaAleatorio; fila++) {
        if (nodoActual->getAbajo() != NULL) {
            nodoActual = nodoActual->getAbajo();
        }
    }

    // Nos movemos a la derecha hasta la columna aleatoria
    for (int columna = 0; columna < columnaAleatorio; columna++) {
        if (nodoActual->getDerecha() != NULL) {
            nodoActual = nodoActual->getDerecha();
        }
    }

    return nodoActual;
}

// ============================================
// MÉTODO: esValidaParaDetective()
// Verifica si un nodo es válido para colocar al detective
// Retorna TRUE si es válido, FALSE si no
// ============================================
bool Ciudad::esValidaParaDetective(Nodo* nodo) {
    if (nodo == NULL) {
        return false;  // No existe el nodo
    }

    char contenido = nodo->getContenido();

    // Es válido si es 'o' (casilla vacía)
    // No es válido si es '#' (borde), '|' (callejón), o tiene otra cosa
    if (contenido == 'o') {
        return true;
    }

    return false;
}

// ============================================
// MÉTODO: moverDetective()
// Mueve el detective en la dirección indicada
// Recibe: W (arriba), S (abajo), A (izquierda), D (derecha)
// Retorna: TRUE si se movió, FALSE si no pudo
// ============================================
bool Ciudad::moverDetective(char direccion) {
    Nodo* nuevaPosicion = NULL;

    // Convertimos a mayúscula por si acaso
    direccion = toupper(direccion);

    // Según la dirección, obtenemos el nodo hacia donde se mueve
    if (direccion == 'W') {
        // Arriba
        nuevaPosicion = this->posicionDetective->getArriba();
    }
    else if (direccion == 'S') {
        // Abajo
        nuevaPosicion = this->posicionDetective->getAbajo();
    }
    else if (direccion == 'A') {
        // Izquierda
        nuevaPosicion = this->posicionDetective->getIzquierda();
    }
    else if (direccion == 'D') {
        // Derecha
        nuevaPosicion = this->posicionDetective->getDerecha();
    }

    // Verificamos si la nueva posición es NULL (no existe)
    if (nuevaPosicion == NULL) {
        return false;
    }

    char contenido = nuevaPosicion->getContenido();

    // NO podemos movernos si hay borde '#' o callejón '|'
    if (contenido == '#' || contenido == '|') {
        return false;
    }

    // Si llegamos aquí, el movimiento es válido
    // Quitamos la 'D' de la posición actual
    this->posicionDetective->setContenido(' ');

    // Marcamos la nueva posición
    this->posicionDetective = nuevaPosicion;
    nuevaPosicion->setContenido('D');
    nuevaPosicion->setVisitado(true);

    // Aumentamos el puntaje (cada movimiento = 1 punto)
    this->aumentarPuntaje();

    return true;  // El movimiento fue exitoso
}

// ============================================
// MÉTODO: imprimirTablero()
// Imprime el tablero actual en la pantalla
// ============================================
void Ciudad::imprimirTablero() {
    Nodo* nodoActual = this->inicioTablero;

    // Recorremos el tablero fila por fila
    for (int fila = 0; fila < 11; fila++) {
        // En cada fila, imprimimos columna por columna
        for (int columna = 0; columna < 11; columna++) {
            // Imprimimos el contenido del nodo actual
            cout << nodoActual->getContenido();

            // Avanzamos al siguiente nodo a la derecha
            if (columna < 10) {
                nodoActual = nodoActual->getDerecha();
            }
        }

        // Salto de línea para pasar a la siguiente fila
        cout << endl;

        // Si no es la última fila, bajamos
        if (fila < 10) {
            nodoActual = nodoActual->getAbajo();

            // Retrocedemos al inicio de la fila
            while (nodoActual->getIzquierda() != NULL) {
                nodoActual = nodoActual->getIzquierda();
            }
        }
    }
}

// ============================================
// GETTERS - Métodos para obtener información
// ============================================

// Retorna el nodo inicial del tablero
Nodo* Ciudad::getInicioTablero() {
    return this->inicioTablero;
}

// Retorna la posición actual del detective
Nodo* Ciudad::getPosicionDetective() {
    return this->posicionDetective;
}

// Retorna el puntaje actual
int Ciudad::getPuntaje() {
    return this->puntaje;
}

// ============================================
// MÉTODO: aumentarPuntaje()
// Aumenta el puntaje en 1 (cada movimiento suma 1)
// ============================================
void Ciudad::aumentarPuntaje() {
    this->puntaje++;
}