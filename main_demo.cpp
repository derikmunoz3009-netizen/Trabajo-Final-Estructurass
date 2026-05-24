#include <iostream>
#include <list>
#include "GestorPistasTestigos.h"

using namespace std;

// Esta clase es solo para probar el modulo de Persona 2.
// En el proyecto real, estas funciones las implementa la clase Ciudad de la Persona 1.
class CiudadPrueba : public IAccionesCiudad {
public:
    void taparMapa() {
        cout << "[Ciudad] El mapa se vuelve a tapar con o." << endl;
    }

    void eliminarCallejonesAleatorios(int cantidad) {
        cout << "[Ciudad] Se eliminan " << cantidad << " callejones aleatorios." << endl;
    }

    void reubicarPistaAleatoriamente(char tipoPista) {
        cout << "[Ciudad] Se reubica la pista tipo " << tipoPista << "." << endl;
    }

    void teletransportarDetective() {
        cout << "[Ciudad] El detective se mueve a una posicion valida aleatoria." << endl;
    }
};

int main() {
    GestorPistasTestigos gestor;
    CiudadPrueba ciudad;
    int puntaje = 16;

    list<Posicion> posicionesLibres;
    for (int f = 1; f <= 9; f++) {
        for (int c = 1; c <= 9; c++) {
            posicionesLibres.push_back(Posicion(f, c));
        }
    }

    gestor.agregarPosicionesAleatorias(posicionesLibres);

    cout << "Modulo de Persona 2 cargado correctamente." << endl;
    cout << "Se generaron 10 pistas y 5 testigos en posiciones aleatorias." << endl;

    // Prueba basica: revisar todas las posiciones para simular que el detective encontro algo.
    for (int f = 1; f <= 9; f++) {
        for (int c = 1; c <= 9; c++) {
            Posicion actual(f, c);
            gestor.recogerPista(actual);
            gestor.recogerTestigo(actual);
        }
    }

    cout << endl;
    gestor.mostrarPistas();

    cout << endl;
    gestor.mostrarColaTestigos();

    cout << endl;
    gestor.usarUltimaPista(puntaje, ciudad);
    cout << "Puntaje actual: " << puntaje << endl;

    cout << endl;
    gestor.interrogarTestigo();

    return 0;
}
