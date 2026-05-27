#include "Ciudad.h"
#include "HashSospechosos.h"
#include "GestorPistasTestigos.h"
#include "ABBPuntajes.h"
#include "FaseAcusacion.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <vector>

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

    // Generar 10 posiciones aleatorias para las pistas (dentro del tablero 9x9)
    vector<pair<int, int>> posiciones_pistas;
    cout << "\nGenerando pistas en el mapa..." << endl;

    while (posiciones_pistas.size() < 10) {
        int fila = 1 + (rand() % 9);      // Filas 1-9 (dentro del tablero)
        int columna = 1 + (rand() % 9);   // Columnas 1-9 (dentro del tablero)

        pair<int, int> pos = make_pair(fila, columna);

        // Verificar que no sea duplicada y que no sea la posicion inicial del detective
        bool existe = false;
        for (auto& p : posiciones_pistas) {
            if (p.first == fila && p.second == columna) {
                existe = true;
                break;
            }
        }

        if (!existe && !(fila == 5 && columna == 5)) {  // No en posicion inicial
            posiciones_pistas.push_back(pos);
        }
    }

    cout << "Se generaron 10 pistas en posiciones aleatorias del mapa." << endl;

    // Posicion inicial del detective (aproximadamente centro)
    int fila_detective = 5;
    int columna_detective = 5;

    cout << "\nPuntaje: " << ciudad.getPuntaje() << endl;
    cout << "Pistas recolectadas: 0/10" << endl;

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

    int pistas_recolectadas = 0;
    bool jugando = true;

    while (jugando) {
        cout << "\nComando > ";
        string entrada;
        getline(cin, entrada);

        if (entrada.empty()) {
            continue;
        }

        // Convertir entrada a mayuscula
        transform(entrada.begin(), entrada.end(), entrada.begin(), ::toupper);

        // ============================================================
        // VER SOSPECHOSOS (SS) - TABLA HASH O(1)
        // ============================================================
        if (entrada == "SS") {
            cout << "\nSospechosos del caso (TABLA HASH - Busqueda O(1)):" << endl;
            cout << "==========================================" << endl;
            hash.mostrarTodos();
            cout << "==========================================" << endl;
            continue;
        }

        char comando = entrada[0];

        // ============================================================
        // MOVIMIENTO (WASD) - Lista Multiplemente Enlazada
        // ============================================================
        if (comando == 'W' || comando == 'A' || comando == 'S' || comando == 'D') {
            bool seMovio = ciudad.moverDetective(comando);

            if (seMovio) {
                // Actualizar posicion del detective basado en movimiento
                if (comando == 'W') {
                    fila_detective--;
                }
                else if (comando == 'S') {
                    fila_detective++;
                }
                else if (comando == 'A') {
                    columna_detective--;
                }
                else if (comando == 'D') {
                    columna_detective++;
                }

                cout << "\nOK: Te moviste exitosamente." << endl;
                cout << "Puntaje: " << ciudad.getPuntaje() << endl;

                // VERIFICAR SI HAY PISTA EN ESTA POSICION
                bool hay_pista = false;
                int indice_pista = -1;

                for (int i = 0; i < posiciones_pistas.size(); i++) {
                    if (posiciones_pistas[i].first == fila_detective &&
                        posiciones_pistas[i].second == columna_detective) {
                        hay_pista = true;
                        indice_pista = i;
                        break;
                    }
                }

                // SI HAY PISTA, RECOGERLA
                if (hay_pista) {
                    pistas_recolectadas++;

                    cout << "\n*** ENCONTRASTE UNA PISTA! ***" << endl;

                    // Tipo de pista aleatorio
                    char tipos[] = {'H', 'C', 'T', 'P'};
                    char tipo = tipos[rand() % 4];
                    string nombre_tipo;

                    if (tipo == 'H') nombre_tipo = "Huella";
                    else if (tipo == 'C') nombre_tipo = "Coartada";
                    else if (tipo == 'T') nombre_tipo = "Testimonio";
                    else nombre_tipo = "Prueba";

                    cout << "Tipo de pista: " << nombre_tipo << " (" << tipo << ")" << endl;

                    // Revelar atributo del culpable
                    hash.revelarAtributoCulpable();

                    // Eliminar esta pista de la lista
                    posiciones_pistas.erase(posiciones_pistas.begin() + indice_pista);

                    cout << "\nPistas recolectadas: " << pistas_recolectadas << "/10" << endl;

                    // SI COMPLETO 10 PISTAS, IR A FASE ACUSACION
                    if (pistas_recolectadas >= 10) {
                        cout << "\n*** HAS RECOLECTADO TODAS LAS 10 PISTAS! ***" << endl;
                        cout << "Es hora de hacer tu acusacion...\n" << endl;

                        int puntaje_final = FaseAcusacion::ejecutar(hash, ranking, nombre, ciudad.getPuntaje());

                        cout << "\nPartida finalizada. Puntaje final: " << puntaje_final << endl;
                        jugando = false;
                        continue;
                    }
                }
                else {
                    cout << "Pistas recolectadas: " << pistas_recolectadas << "/10" << endl;
                }

                ciudad.imprimirTablero();
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
            cout << "Pistas recolectadas: " << pistas_recolectadas << "/10" << endl;
            cout << "Guardando en ranking..." << endl;
            ranking.insertarPuntaje(nombre, ciudad.getPuntaje());
            ranking.mostrarRanking();
            jugando = false;
        }
        else {
            cout << "Comando no valido. Intenta W/A/S/D, T, SS, I, R o Q." << endl;
        }
    }

    return 0;
}