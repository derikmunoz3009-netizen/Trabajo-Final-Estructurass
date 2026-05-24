#include "Ciudad.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Inicializar la semilla para números aleatorios
    srand(time(0));
    
    // Crear la ciudad (automáticamente crea el tablero, bordes, callejones y detective)
    Ciudad ciudad;
    
    cout << "===== DETECTIVE CITY =====" << endl;
    cout << "Tu nombre: " << endl;
    string nombre;
    getline(cin, nombre);
    
    cout << "\n" << nombre << ", Tu puntaje actual es: " << ciudad.getPuntaje() << endl;
    
    // Imprimir el tablero inicial
    ciudad.imprimirTablero();
    
    cout << "\nControles:" << endl;
    cout << "W - Arriba" << endl;
    cout << "A - Izquierda" << endl;
    cout << "S - Abajo" << endl;
    cout << "D - Derecha" << endl;
    cout << "Q - Salir" << endl;
    
    // Loop del juego
    bool jugando = true;
    
    while (jugando) {
        cout << "\n¿Hacia dónde te mueves? > ";
        char movimiento;
        cin >> movimiento;
        
        movimiento = toupper(movimiento);
        
        if (movimiento == 'Q') {
            cout << "\n¡Hasta luego!" << endl;
            jugando = false;
        }
        else if (movimiento == 'W' || movimiento == 'A' || movimiento == 'S' || movimiento == 'D') {
            // Intentar mover al detective
            bool seMovio = ciudad.moverDetective(movimiento);
            
            if (seMovio) {
                cout << "\n" << nombre << ", Tu puntaje actual es: " << ciudad.getPuntaje() << endl;
                ciudad.imprimirTablero();
            }
            else {
                cout << "\n¡No puedes ir por ahí! Hay un callejón o un borde." << endl;
            }
        }
        else {
            cout << "Comando no válido." << endl;
        }
    }
    
    return 0;
}
