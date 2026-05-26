#include "Ciudad.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

// ============================================================
// Función para mostrar el menú de controles
// ============================================================
void mostrarControles() {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                   CONTROLES DEL JUEGO                      ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════╣" << endl;
    cout << "║  MOVIMIENTO DEL DETECTIVE:                                 ║" << endl;
    cout << "║    W - Moverse ARRIBA                                      ║" << endl;
    cout << "║    A - Moverse a la IZQUIERDA                              ║" << endl;
    cout << "║    S - Moverse ABAJO                                       ║" << endl;
    cout << "║    D - Moverse a la DERECHA                                ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  ACCIONES:                                                 ║" << endl;
    cout << "║    T - Ver PISTAS recogidas (Stack LIFO)                   ║" << endl;
    cout << "║    X - USAR la última pista encontrada                     ║" << endl;
    cout << "║    S - Ver SOSPECHOSOS con atributos revelados             ║" << endl;
    cout << "║    I - INTERROGAR al siguiente testigo (Cola)              ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  SALIR:                                                    ║" << endl;
    cout << "║    Q - Abandonar el juego                                  ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
}

// ============================================================
// Función para validar que la entrada sea solo movimiento
// ============================================================
bool esMovimientoValido(char tecla) {
    tecla = toupper(tecla);
    return (tecla == 'W' || tecla == 'A' || tecla == 'S' || tecla == 'D');
}

// ============================================================
// Función para validar que sea una acción válida
// ============================================================
bool esAccionValida(char tecla) {
    tecla = toupper(tecla);
    return (tecla == 'T' || tecla == 'X' || tecla == 'I' || tecla == 'Q');
}

// ============================================================
// MAIN - Punto de entrada del programa
// ============================================================
int main() {
    // Inicializar la semilla para números aleatorios
    srand(time(0));

    // Crear la ciudad (automáticamente crea el tablero, bordes, callejones y detective)
    Ciudad ciudad;

    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                      DETECTIVE CASE                     ║" << endl;
    cout << "║              Encuentra las 10 pistas y acusa               ║" << endl;
    cout << "║                   al culpable correcto                     ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;

    cout << "\n¿Cuál es tu nombre, detective? > ";
    string nombre;
    getline(cin, nombre);

    // Validar que el nombre no esté vacío
    if (nombre.empty()) {
        nombre = "Detective";
    }

    cout << "\n¡Bienvenido, " << nombre << "!" << endl;
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

        // Si la entrada está vacía, ignorar
        if (entrada.empty()) {
            cout << " Debes ingresar un comando. Intenta de nuevo." << endl;
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
                cout << "\n Te moviste exitosamente." << endl;
                cout << nombre << ", Tu puntaje actual es: " << ciudad.getPuntaje() << endl;
                ciudad.imprimirTablero();
            }
            else {
                cout << "\n ¡No puedes ir por ahí! Hay un borde '#' o un callejón cerrado '|'." << endl;
                cout << "   Intenta otro movimiento (W/A/S/D)." << endl;
            }
        }
        // ============================================================
        // Acción: Ver pistas (T)
        // ============================================================
        else if (comando == 'T') {
            cout << "\n Viendo las pistas que has recolectado..." << endl;
            // Aquí iría: gestor.mostrarPistas();
            cout << "   (Esta funcionalidad aún está en desarrollo)" << endl;
        }
        // ============================================================
        // Acción: Usar pista (X)
        // ============================================================
        else if (comando == 'X') {
            cout << "\n Usando la última pista encontrada..." << endl;
            // Aquí iría: gestor.usarUltimaPista(puntaje, ciudad);
            cout << "   (Esta funcionalidad aún está en desarrollo)" << endl;
        }
        // ============================================================
        // Acción: Ver sospechosos (S) - PERO OJO: S es también Abajo
        // ============================================================
        else if (comando == 'S' && entrada.length() > 1 && toupper(entrada[1]) == 'S') {
            // Si escriben "SS" es para ver sospechosos
            cout << "\n👥 Viendo sospechosos del caso con atributos revelados..." << endl;
            // Aquí iría: hash.mostrarTodos();
            cout << "   (Esta funcionalidad aún está en desarrollo)" << endl;
        }
        else if (comando == 'S' && entrada.length() == 1) {
            // Si solo escriben "S", preguntar si quieren moverse o ver sospechosos
            cout << "\n  'S' puede significar dos cosas:" << endl;
            cout << "    1. Mover ABAJO (Si, te moverás abajo)" << endl;
            cout << "    2. Ver SOSPECHOSOS (Si escribes 'SS')" << endl;
            cout << "   ¿Cuál deseas? Intenta de nuevo." << endl;
        }
        // ============================================================
        // Acción: Interrogar testigo (I)
        // ============================================================
        else if (comando == 'I') {
            cout << "\n🎤 Interrogando al siguiente testigo en la cola..." << endl;
            // Aquí iría: gestor.interrogarTestigo();
            cout << "   (Esta funcionalidad aún está en desarrollo)" << endl;
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
            cout << "\n ¡Hasta luego, " << nombre << "!" << endl;
            cout << "Tu puntaje final fue: " << ciudad.getPuntaje() << " movimientos." << endl;
            jugando = false;
        }
        // ============================================================
        // Comando no válido
        // ============================================================
        else {
            cout << "\n Comando no reconocido: '" << comando << "'" << endl;
            cout << "   Comandos disponibles:" << endl;
            cout << "   • W, A, S, D - Movimiento (SOLO para moverse)" << endl;
            cout << "   • T - Ver pistas" << endl;
            cout << "   • X - Usar pista" << endl;
            cout << "   • SS - Ver sospechosos" << endl;
            cout << "   • I - Interrogar testigo" << endl;
            cout << "   • Q - Salir" << endl;
            cout << "   • ? - Ver controles completos" << endl;
        }
    }

    return 0;
}