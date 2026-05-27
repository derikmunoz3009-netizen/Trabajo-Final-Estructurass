#include "Ciudad.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

// ============================================================
// Funcion para mostrar el menu de controles
// ============================================================
void mostrarControles() {
    cout << "\n=========================================" << endl;
    cout << "         CONTROLES DEL JUEGO" << endl;
    cout << "=========================================" << endl;
    cout << "  MOVIMIENTO DEL DETECTIVE:" << endl;
    cout << "    W - Moverse ARRIBA" << endl;
    cout << "    A - Moverse a la IZQUIERDA" << endl;
    cout << "    S - Moverse ABAJO" << endl;
    cout << "    D - Moverse a la DERECHA" << endl;
    cout << "" << endl;
    cout << "  ACCIONES:" << endl;
    cout << "    T - Ver PISTAS recogidas (Stack LIFO)" << endl;
    cout << "    X - USAR la ultima pista encontrada" << endl;
    cout << "    SS - Ver SOSPECHOSOS con atributos revelados" << endl;
    cout << "    I - INTERROGAR al siguiente testigo (Cola)" << endl;
    cout << "" << endl;
    cout << "  SALIR:" << endl;
    cout << "    Q - Abandonar el juego" << endl;
    cout << "    ? - Ver controles" << endl;
    cout << "=========================================" << endl;
}

// ============================================================
// Funcion para validar que la entrada sea solo movimiento
// ============================================================
bool esMovimientoValido(char tecla) {
    tecla = toupper(tecla);
    return (tecla == 'W' || tecla == 'A' || tecla == 'S' || tecla == 'D');
}

// ============================================================
// Funcion para validar que sea una accion valida
// ============================================================
bool esAccionValida(char tecla) {
    tecla = toupper(tecla);
    return (tecla == 'T' || tecla == 'X' || tecla == 'I' || tecla == 'Q');
}

// ============================================================
// MAIN - Punto de entrada del programa
// ============================================================
int main() {
    // Inicializar la semilla para numeros aleatorios
    srand(time(0));

    // Crear la ciudad (automaticamente crea el tablero, bordes, callejones y detective)
    Ciudad ciudad;

    cout << "\n=========================================" << endl;
    cout << "       DETECTIVE CASE" << endl;
    cout << "Encuentra las 10 pistas y acusa" << endl;
    cout << "       al culpable correcto" << endl;
    cout << "=========================================" << endl;

    cout << "\nCual es tu nombre, detective? > ";
    string nombre;
    getline(cin, nombre);

    // Validar que el nombre no este vacio
    if (nombre.empty()) {
        nombre = "Detective";
    }

    cout << "\nBienvenido, " << nombre << "!" << endl;
    cout << "\n" << nombre << ", Tu puntaje actual es: " << ciudad.getPuntaje() << endl;

    // Imprimir el tablero inicial
    ciudad.imprimirTablero();

    // Mostrar controles
    mostrarControles();

    // Loop del juego
    bool jugando = true;

    while (jugando) {
        cout << "\n" << nombre << " (Puntaje: " << ciudad.getPuntaje() << ") > Ingresa comando (W/A/S/D para mover, ? para ayuda): ";
        string entrada;
        getline(cin, entrada);

        // Si la entrada esta vacia, ignorar
        if (entrada.empty()) {
            cout << "ADVERTENCIA: Debes ingresar un comando. Intenta de nuevo." << endl;
            continue;
        }

        char comando = toupper(entrada[0]);

        // ============================================================
        // Opciones de movimiento (WASD)
        // ============================================================
        if (comando == 'W' || comando == 'A' || comando == 'S' || comando == 'D') {
            // Intentar mover al detective
            bool seMovio = ciudad.moverDetective(comando);

            if (seMovio) {
                cout << "\nOK: Te moviste exitosamente." << endl;
                cout << nombre << ", Tu puntaje actual es: " << ciudad.getPuntaje() << endl;
                ciudad.imprimirTablero();
            }
            else {
                cout << "\nERROR: No puedes ir por ahi! Hay un borde # o un callejon cerrado |" << endl;
                cout << "   Intenta otro movimiento (W/A/S/D)." << endl;
            }
        }
        // ============================================================
        // Accion: Ver pistas (T)
        // ============================================================
        else if (comando == 'T') {
            cout << "\nViendo las pistas que has recolectado..." << endl;
            // Aqui iria: gestor.mostrarPistas();
            cout << "   (Esta funcionalidad aun esta en desarrollo)" << endl;
        }
        // ============================================================
        // Accion: Usar pista (X)
        // ============================================================
        else if (comando == 'X') {
            cout << "\nUsando la ultima pista encontrada..." << endl;
            // Aqui iria: gestor.usarUltimaPista(puntaje, ciudad);
            cout << "   (Esta funcionalidad aun esta en desarrollo)" << endl;
        }
        // ============================================================
        // Accion: Ver sospechosos (S) - PERO OJO: S es tambien Abajo
        // ============================================================
        else if (comando == 'S' && entrada.length() > 1 && toupper(entrada[1]) == 'S') {
            // Si escriben "SS" es para ver sospechosos
            cout << "\nViendo sospechosos del caso con atributos revelados..." << endl;
            // Aqui iria: hash.mostrarTodos();
            cout << "   (Esta funcionalidad aun esta en desarrollo)" << endl;
        }
        else if (comando == 'S' && entrada.length() == 1) {
            // Si solo escriben "S", preguntar si quieren moverse o ver sospechosos
            cout << "\nADVERTENCIA: 'S' puede significar dos cosas:" << endl;
            cout << "    1. Mover ABAJO" << endl;
            cout << "    2. Ver SOSPECHOSOS (si escribes SS)" << endl;
            cout << "   Cual deseas? Intenta de nuevo." << endl;
        }
        // ============================================================
        // Accion: Interrogar testigo (I)
        // ============================================================
        else if (comando == 'I') {
            cout << "\nInterrogando al siguiente testigo en la cola..." << endl;
            // Aqui iria: gestor.interrogarTestigo();
            cout << "   (Esta funcionalidad aun esta en desarrollo)" << endl;
        }
        // ============================================================
        // Ayuda (?)
        // ============================================================
        else if (comando == '?') {
            mostrarControles();
        }
        // ============================================================
        // Salir del juego (Q)
        // ============================================================
        else if (comando == 'Q') {
            cout << "\nHasta luego, " << nombre << "!" << endl;
            cout << "Tu puntaje final fue: " << ciudad.getPuntaje() << " movimientos." << endl;
            jugando = false;
        }
        // ============================================================
        // Comando no valido
        // ============================================================
        else {
            cout << "\nERROR: Comando no reconocido: '" << comando << "'" << endl;
            cout << "   Comandos disponibles:" << endl;
            cout << "   - W, A, S, D: Movimiento (SOLO para moverse)" << endl;
            cout << "   - T: Ver pistas" << endl;
            cout << "   - X: Usar pista" << endl;
            cout << "   - SS: Ver sospechosos" << endl;
            cout << "   - I: Interrogar testigo" << endl;
            cout << "   - Q: Salir" << endl;
            cout << "   - ?: Ver controles completos" << endl;
        }
    }

    return 0;
}