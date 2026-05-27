#include "Mapa.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
using namespace std;

Mapa::Mapa() {
    construirCeldas();
    conectarCeldas();
    ubicarParedes();
    ubicarCallejones();
    ubicarPistas();
    ubicarTestigos();
}

Mapa::~Mapa() {
    if (inicio == nullptr) return;

    bool visitado[11][11] = {false};
    queue<Ubicacion*> q;

    q.push(inicio);
    visitado[0][0] = true;

    while (!q.empty()) {
        Ubicacion* actual = q.front();
        q.pop();

        int fila = actual->getFila();
        int col = actual->getColumna();

        if (actual->arriba != nullptr && !visitado[fila-1][col]) {
            q.push(actual->arriba);
            visitado[fila-1][col] = true;
        }
        if (actual->abajo != nullptr && !visitado[fila+1][col]) {
            q.push(actual->abajo);
            visitado[fila+1][col] = true;
        }
        if (actual->izquierda != nullptr && !visitado[fila][col-1]) {
            q.push(actual->izquierda);
            visitado[fila][col-1] = true;
        }
        if (actual->derecha != nullptr && !visitado[fila][col+1]) {
            q.push(actual->derecha);
            visitado[fila][col+1] = true;
        }

        delete actual;
    }
}

void Mapa::construirCeldas() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            celdas_temp[i][j] = new Ubicacion(i, j, VACIO);
        }
    }
    inicio = celdas_temp[0][0];
}

void Mapa::conectarCeldas() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            celdas_temp[i][j]->arriba    = (i > 0)          ? celdas_temp[i-1][j] : nullptr;
            celdas_temp[i][j]->abajo     = (i < FILAS-1)    ? celdas_temp[i+1][j] : nullptr;
            celdas_temp[i][j]->izquierda = (j > 0)          ? celdas_temp[i][j-1] : nullptr;
            celdas_temp[i][j]->derecha   = (j < COLUMNAS-1) ? celdas_temp[i][j+1] : nullptr;
        }
    }
}

void Mapa::ubicarParedes() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (i == 0 || i == FILAS-1 || j == 0 || j == COLUMNAS-1) {
                celdas_temp[i][j]->setTipo(PARED);
            }
        }
    }
}

void Mapa::ubicarCallejones() {
    int colocados = 0;
    while (colocados < 16) {
        int f = rand() % 9 + 1;
        int c = rand() % 9 + 1;
        if (celdas_temp[f][c]->getTipo() == VACIO) {
            celdas_temp[f][c]->setTipo(CALLEJON);
            colocados++;
        }
    }
}

void Mapa::ubicarPistas() {
    TipoPista tipos[4] = {HUELLA, COARTADA, TESTIMONIO, PRUEBA_FORENSE};
    int colocadas = 0;
    while (colocadas < 10) {
        int f = rand() % 9 + 1;
        int c = rand() % 9 + 1;
        if (celdas_temp[f][c]->getTipo() == VACIO) {
            TipoPista tipo = tipos[rand() % 4];
            Pista* p = new Pista(tipo);
            celdas_temp[f][c]->setTipo(CON_PISTA);
            celdas_temp[f][c]->setPista(p);
            colocadas++;
        }
    }
}

void Mapa::ubicarTestigos() {
    int colocados = 0;
    while (colocados < 5) {
        int f = rand() % 9 + 1;
        int c = rand() % 9 + 1;
        if (celdas_temp[f][c]->getTipo() == VACIO) {
            celdas_temp[f][c]->setTipo(CON_TESTIGO);
            colocados++;
        }
    }
}

bool Mapa::esPosicionLibre(int f, int c) const {
    Ubicacion* celda = getCelda(f, c);
    if (celda == nullptr) return false;
    return celda->getTipo() == VACIO;
}

Ubicacion* Mapa::getCelda(int fila, int col) const {
    if (inicio == nullptr) return nullptr;
    if (fila < 0 || fila >= FILAS || col < 0 || col >= COLUMNAS) return nullptr;

    Ubicacion* actual = inicio;

    for (int i = 0; i < fila; i++) {
        if (actual->abajo == nullptr) return nullptr;
        actual = actual->abajo;
    }

    for (int j = 0; j < col; j++) {
        if (actual->derecha == nullptr) return nullptr;
        actual = actual->derecha;
    }

    return actual;
}

Ubicacion* Mapa::getPosicionAleatoria() const {
    int f, c;
    do {
        f = rand() % 9 + 1;
        c = rand() % 9 + 1;
    } while (!esPosicionLibre(f, c));
    return getCelda(f, c);
}

void Mapa::imprimirTablero(int detectiveFila, int detectiveColumna) const {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            Ubicacion* celda = getCelda(i, j);
            if (celda != nullptr) {
                cout << celda->getSimbolo(detectiveFila, detectiveColumna);
            }
            if (j < COLUMNAS - 1) cout << " ";
        }
        cout << endl;
    }
}

void Mapa::resetearVisibilidad() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            Ubicacion* celda = getCelda(i, j);
            if (celda != nullptr) {
                celda->resetVisita();
            }
        }
    }
}

bool Mapa::hayPistaEn(int f, int c) const {
    Ubicacion* celda = getCelda(f, c);
    if (celda == nullptr) return false;
    return celda->getTipo() == CON_PISTA;
}

bool Mapa::hayTestigoEn(int f, int c) const {
    Ubicacion* celda = getCelda(f, c);
    if (celda == nullptr) return false;
    return celda->getTipo() == CON_TESTIGO;
}

bool Mapa::esTransitable(int f, int c) const {
    Ubicacion* celda = getCelda(f, c);
    if (celda == nullptr) return false;
    TipoUbicacion t = celda->getTipo();
    return t == VACIO || t == CON_PISTA || t == CON_TESTIGO;
}

void Mapa::eliminarCallejonesAleatorios(int cantidad) {
    vector<pair<int,int>> callejones;

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            Ubicacion* celda = getCelda(i, j);
            if (celda != nullptr && celda->getTipo() == CALLEJON) {
                callejones.push_back({i, j});
            }
        }
    }

    for (int k = 0; k < cantidad && !callejones.empty(); k++) {
        int idx = rand() % callejones.size();
        int f = callejones[idx].first;
        int c = callejones[idx].second;

        Ubicacion* celda = getCelda(f, c);
        if (celda != nullptr) {
            celda->setTipo(VACIO);
            cout << "  Callejon eliminado en [" << f << "," << c << "]" << endl;
        }

        callejones.erase(callejones.begin() + idx);
    }
}