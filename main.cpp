#include "Ciudad.h"
#include "HashSospechosos.h"
#include "GestorPistasTestigos.h"
#include "ABBPuntajes.h"
#include "FaseAcusacion.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Inicializar la semilla para numeros aleatorios
    srand(time(0));

    // Crear todas las estructuras de datos
    Ciudad ciudad;
    HashSospechosos hash;
    ABBPuntajes ranking;
    GestorPistasTestigos gestor;

    // Inicializar los 8 sospechosos en la tabla hash
    cout << "\nCargando sospechosos..." << endl;
    hash.inicializarSospechosos();

    cout << "==========================================" << endl;
    cout << "       DETECTIVE CASE" << endl;
    cout << "==========================================" << endl;

    cout << "\nCual es tu nombre, detective? > ";
    string nombre;
    getline(cin, nombre);

    if (nombre.empty()) {
        nombre = "Detective";
    }

    cout << "\nBienvenido, " << nombre << "!" << endl;

    // Buscar si ya ha jugado antes
    ranking.buscarDetective(nombre);

    cout << "\nPuntaje: " << ciudad.getPuntaje() << endl;
    cout << "Pistas recolectadas: " << gestor.getPistasRecogidas() << "/10" << endl;

    // Imprimir el tablero inicial
    ciudad.imprimirTablero();

    cout << "\nControles:" << endl;
    cout << "W - Arriba" << endl;
    cout << "A - Izquierda" << endl;
    cout << "S - Abajo" << endl;
    cout << "D - Derecha" << endl;
    cout << "T - Ver pistas recolectadas" << endl;
    cout << "SS - Ver sospechosos" << endl;
    cout << "I - Interrogar testigo" << endl;
    cout << "R - Ver ranking" << endl;
    cout << "Q - Salir" << endl;

    // Loop del juego
    bool jugando = true;

    while (jugando) {
        cout << "\nComando > ";
        string entrada;
        getline(cin, entrada);

        if (entrada.empty()) {
            continue;
        }

        char comando = toupper(entrada[0]);

        // ============================================================
        // MOVIMIENTO (WASD) - Lista Multiplemente Enlazada
        // ============================================================
        if (comando == 'W' || comando == 'A' || comando == 'S' || comando == 'D') {
            bool seMovio = ciudad.moverDetective(comando);

            if (seMovio) {
                cout << "\nOK: Te moviste exitosamente." << endl;
                cout << "Puntaje: " << ciudad.getPuntaje() << endl;
                cout << "Pistas recolectadas: " << gestor.getPistasRecogidas() << "/10" << endl;
                ciudad.imprimirTablero();

                // Verificar si estamos en la posicion correcta para una pista
                // NOTA: En una implementacion completa, generarias pistas
                // y verificarias si hay pista en la nueva posicion
            }
            else {
                cout << "\nERROR: No puedes ir por ahi! Hay un borde o un callejon." << endl;
            }
        }
        // ============================================================
        // VER PISTAS (T) - STACK LIFO
        // ============================================================
        else if (comando == 'T') {
            cout << "\nPistas recolectadas (STACK - LIFO):" << endl;
            gestor.mostrarPistas();
        }
        // ============================================================
        // VER SOSPECHOSOS (SS) - TABLA HASH O(1)
        // ============================================================
        else if (comando == 'S' && entrada.length() > 1 && toupper(entrada[1]) == 'S') {
            cout << "\nSospechosos del caso (TABLA HASH - Busqueda O(1)):" << endl;
            cout << "==========================================" << endl;
            hash.mostrarTodos();
            cout << "==========================================" << endl;
        }
        else if (comando == 'S' && entrada.length() == 1) {
            // Mover abajo
            bool seMovio = ciudad.moverDetective('S');
            if (seMovio) {
                cout << "\nOK: Te moviste exitosamente." << endl;
                cout << "Puntaje: " << ciudad.getPuntaje() << endl;
                ciudad.imprimirTablero();
            }
            else {
                cout << "\nERROR: No puedes ir por ahi!" << endl;
            }
        }
        // ============================================================
        // INTERROGAR TESTIGO (I) - QUEUE FIFO
        // ============================================================
        else if (comando == 'I') {
            cout << "\nInterrogando testigo (QUEUE - FIFO):" << endl;
            gestor.interrogarTestigo();
        }
        // ============================================================
        // VER RANKING (R) - ARBOL BINARIO
        // ============================================================
        else if (comando == 'R') {
            cout << "\nRanking historico de detectives (ARBOL BINARIO - Recorrido InOrden):" << endl;
            ranking.mostrarRanking();
        }
        // ============================================================
        // SALIR (Q)
        // ============================================================
        else if (comando == 'Q') {
            cout << "\nHasta luego, " << nombre << "!" << endl;
            cout << "Tu puntaje fue: " << ciudad.getPuntaje() << " movimientos." << endl;
            cout << "Guardando en ranking..." << endl;
            ranking.insertarPuntaje(nombre, ciudad.getPuntaje());
            ranking.mostrarRanking();
            jugando = false;
        }
        else {
            cout << "Comando no valido." << endl;
        }
    }

    return 0;
}