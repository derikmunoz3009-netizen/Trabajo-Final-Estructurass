#include "Mapa.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
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
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            delete celdas[i][j];
}

void Mapa::construirCeldas() {
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            celdas[i][j] = new Ubicacion(i, j, VACIO);
}

void Mapa::conectarCeldas() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            celdas[i][j]->arriba    = (i > 0)          ? celdas[i-1][j] : nullptr;
            celdas[i][j]->abajo     = (i < FILAS-1)    ? celdas[i+1][j] : nullptr;
            celdas[i][j]->izquierda = (j > 0)          ? celdas[i][j-1] : nullptr;
            celdas[i][j]->derecha   = (j < COLUMNAS-1) ? celdas[i][j+1] : nullptr;
        }
    }
}

void Mapa::ubicarParedes() {
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if (i == 0 || i == FILAS-1 || j == 0 || j == COLUMNAS-1)
                celdas[i][j]->setTipo(PARED);
}

void Mapa::ubicarCallejones() {
    int colocados = 0;
    while (colocados < 16) {
        int f = rand() % 9 + 1;
        int c = rand() % 9 + 1;
        if (celdas[f][c]->getTipo() == VACIO) {
            celdas[f][c]->setTipo(CALLEJON);
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
        if (celdas[f][c]->getTipo() == VACIO) {
            TipoPista tipo = tipos[rand() % 4];
            Pista* p = new Pista(tipo);
            celdas[f][c]->setTipo(CON_PISTA);
            celdas[f][c]->setPista(p);
            colocadas++;
        }
    }
}

void Mapa::ubicarTestigos() {
    int colocados = 0;
    while (colocados < 5) {
        int f = rand() % 9 + 1;
        int c = rand() % 9 + 1;
        if (celdas[f][c]->getTipo() == VACIO) {
            celdas[f][c]->setTipo(CON_TESTIGO);
            colocados++;
        }
    }
}

bool Mapa::esPosicionLibre(int f, int c) const {
    return celdas[f][c]->getTipo() == VACIO;
}

Ubicacion* Mapa::getCelda(int f, int c) const {
    return celdas[f][c];
}

Ubicacion* Mapa::getPosicionAleatoria() const {
    int f, c;
    do {
        f = rand() % 9 + 1;
        c = rand() % 9 + 1;
    } while (!esPosicionLibre(f, c));
    return celdas[f][c];
}

void Mapa::imprimirTablero(int detectiveFila, int detectiveColumna) const {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            cout << celdas[i][j]->getSimbolo(detectiveFila, detectiveColumna);
            if (j < COLUMNAS - 1) cout << " ";
        }
        cout << endl;
    }
}

void Mapa::resetearVisibilidad() {
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            celdas[i][j]->resetVisita();
}

bool Mapa::hayPistaEn(int f, int c) const {
    return celdas[f][c]->getTipo() == CON_PISTA;
}

bool Mapa::hayTestigoEn(int f, int c) const {
    return celdas[f][c]->getTipo() == CON_TESTIGO;
}

bool Mapa::esTransitable(int f, int c) const {
    TipoUbicacion t = celdas[f][c]->getTipo();
    return t == VACIO || t == CON_PISTA || t == CON_TESTIGO;
}

void Mapa::eliminarCallejonesAleatorios(int cantidad) {
    vector<pair<int,int>> callejones;
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            if (celdas[i][j]->getTipo() == CALLEJON)
                callejones.push_back({i, j});

    for (int k = 0; k < cantidad && !callejones.empty(); k++) {
        int idx = rand() % callejones.size();
        int f = callejones[idx].first;
        int c = callejones[idx].second;
        celdas[f][c]->setTipo(VACIO);
        callejones.erase(callejones.begin() + idx);
        cout << "  Callejon eliminado en [" << f << "," << c << "]" << endl;
    }
}
