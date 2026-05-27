//
// Juego.cpp — VERSIÓN CORREGIDA
// Correcciones:
//   1. Z ahora mueve hacia abajo correctamente (no colisiona con S = sospechosos)
//   2. Nueva tecla 'R' permite acusar en CUALQUIER momento del juego
//

#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

static vector<pair<string, vector<string>>> SOSPECHOSOS_POSIBLES = {
    {"Carlos",   {"alto",  "zurdo",    "cabello negro",   "ojos cafes",   "cicatriz en mejilla"}},
    {"Diana",    {"alta",  "diestra",  "cabello rubio",   "ojos verdes",  "lunar en cuello"}},
    {"Eduardo",  {"bajo",  "zurdo",    "calvo",           "ojos negros",  "barba espesa"}},
    {"Fernanda", {"alta",  "diestra",  "cabello rojo",    "ojos claros",  "tatuaje en brazo"}},
    {"Gonzalo",  {"alto",  "diestro",  "cabello gris",    "ojos cafes",   "cojea al caminar"}},
    {"Hilda",    {"baja",  "zurda",    "cabello negro",   "ojos verdes",  "voz muy aguda"}},
    {"Ivan",     {"alto",  "diestro",  "cabello castano", "ojos azules",  "usa lentes"}},
    {"Julia",    {"media", "zurda",    "cabello corto",   "ojos cafes",   "habla muy rapido"}},
    {"Kevin",    {"bajo",  "diestro",  "cabello rizado",  "ojos negros",  "siempre de negro"}},
    {"Laura",    {"alta",  "diestra",  "cabello largo",   "ojos verdes",  "acento extranjero"}}
};

Juego::Juego() {
    srand(time(nullptr));
    mapa             = new Mapa();
    pilaPistas       = new Pila();
    colaTestigos     = new Cola();
    tablaSospechosos = new TablaHash();
    historial        = new ABB();
    detective        = nullptr;
    juegoTerminado   = false;
    casoResuelto     = false;
}

Juego::~Juego() {
    delete mapa;
    delete detective;
    delete pilaPistas;
    delete colaTestigos;
    delete tablaSospechosos;
    delete historial;
}

void Juego::inicializarSospechosos() {
    vector<int> indices;
    for (int i = 0; i < (int)SOSPECHOSOS_POSIBLES.size(); i++)
        indices.push_back(i);

    for (int i = (int)indices.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(indices[i], indices[j]);
    }

    for (int i = 0; i < 8; i++) {
        auto& datos = SOSPECHOSOS_POSIBLES[indices[i]];
        Sospechoso s(datos.first, datos.second);
        tablaSospechosos->insertar(datos.first, s);
    }

    int culpableIdx = rand() % 8;
    auto& datosCulpable = SOSPECHOSOS_POSIBLES[indices[culpableIdx]];
    Sospechoso* culpable = tablaSospechosos->buscar(datosCulpable.first);
    if (culpable != nullptr)
        culpable->marcarCulpable();

    cout << "\n  Caso iniciado. 8 sospechosos registrados.\n";
}

void Juego::inicializarDetective() {
    string nombre;
    cout << "\n  Ingresa tu nombre de detective: ";
    getline(cin, nombre);

    Ubicacion* posInicial = mapa->getPosicionAleatoria();
    detective = new Detective(nombre,
                              posInicial->getFila(),
                              posInicial->getColumna());
    posInicial->visitar();

    if (historial->haJugado(nombre)) {
        cout << "  Bienvenido de nuevo, " << nombre
             << "! Tu mejor puntaje es: "
             << historial->getMejorPuntaje(nombre) << " movimientos.\n";
    } else {
        cout << "  Bienvenido al caso, " << nombre << "!\n";
    }
}

void Juego::moverDetective(char direccion) {
    int f = detective->getFila();
    int c = detective->getColumna();

    Ubicacion* actual  = mapa->getCelda(f, c);
    Ubicacion* destino = nullptr;

    if      (direccion == 'W') destino = actual->arriba;
    else if (direccion == 'B') destino = actual->abajo;   // B = abajo (Z convertido a B)
    else if (direccion == 'A') destino = actual->izquierda;
    else if (direccion == 'D') destino = actual->derecha;

    if (destino == nullptr) return;

    TipoUbicacion tipoDest = destino->getTipo();

    if (tipoDest == PARED) {
        cout << "  No puedes salir de la ciudad.\n";
        return;
    }

    if (tipoDest == CALLEJON) {
        destino->hacerVisible();
        cout << "  Callejon cerrado! Busca otra ruta.\n";
        detective->sumarPunto();
        return;
    }

    TipoUbicacion tipoAntes = tipoDest;

    detective->setPosicion(destino->getFila(), destino->getColumna());
    destino->visitar();
    detective->sumarPunto();

    if (tipoAntes == CON_PISTA) {
        Pista* p = destino->getPista();
        if (p != nullptr) {
            cout << "\n  *** Encontraste una pista! Tipo: "
                 << p->getTipoString() << " ***\n";
            pilaPistas->push(p);
            detective->agregarPista();
            destino->quitarPista();
            tablaSospechosos->revelarAtributoACulpable();
        }
    }

    if (tipoAntes == CON_TESTIGO) {
        string declaracion = generarDeclaracion();
        cout << "\n  *** Testigo encontrado! Su declaracion entra a la cola ***\n";
        colaTestigos->encolar(declaracion);
    }
}

string Juego::generarDeclaracion() const {
    vector<string> frases = {
        "Vi al sospechoso cerca del mercado esa noche...",
        "Escuche pasos extranios en el callejon...",
        "Habia alguien merodeando la zona...",
        "El sospechoso actuaba de manera muy nerviosa..."
    };
    return frases[rand() % frases.size()];
}

void Juego::usarPista() {
    if (pilaPistas->estaVacia()) {
        cout << "  No tienes pistas para usar.\n";
        return;
    }

    Pista* p = pilaPistas->pop();
    detective->quitarPista();
    cout << "\n  Usaste una pista: " << p->getTipoString() << endl;
    aplicarEfectoPista(p);

    Ubicacion* nuevaPos = mapa->getPosicionAleatoria();
    nuevaPos->setTipo(CON_PISTA);
    nuevaPos->setPista(p);

    mapa->resetearVisibilidad();
    cout << "  La " << p->getTipoString() << " volvio al mapa y el tablero se reseteo.\n";
}

void Juego::aplicarEfectoPista(Pista* pista) {
    switch (pista->getTipo()) {
        case HUELLA:
            detective->reducirPuntajeMitad();
            cout << "  Efecto Huella: puntaje reducido a la mitad -> "
                 << detective->getPuntaje() << "\n";
            break;

        case COARTADA:
            mapa->eliminarCallejonesAleatorios(2);
            cout << "  Efecto Coartada: 2 callejones eliminados.\n";
            break;

        case TESTIMONIO: {
            int azar = rand() % 2;
            if (azar == 0) {
                detective->resetPuntaje();
                cout << "  Efecto Testimonio: suerte! Puntaje reseteado a 0.\n";
            } else {
                detective->duplicarPuntaje();
                cout << "  Efecto Testimonio: mala suerte! Puntaje duplicado -> "
                     << detective->getPuntaje() << "\n";
            }
            break;
        }

        case PRUEBA_FORENSE: {
            Ubicacion* nuevaPos = mapa->getPosicionAleatoria();
            detective->teleportar(nuevaPos->getFila(), nuevaPos->getColumna());
            nuevaPos->visitar();
            cout << "  Efecto Prueba Forense: teleportado a ["
                 << nuevaPos->getFila() << "," << nuevaPos->getColumna() << "]\n";
            break;
        }
    }
}

void Juego::interrogarTestigo() {
    if (colaTestigos->estaVacia()) {
        cout << "  No hay testigos en la cola.\n";
        return;
    }
    string declaracion = colaTestigos->desencolar();
    cout << "\n  Testigo dice: \"" << declaracion << "\"\n";
    tablaSospechosos->revelarAtributoACulpable();
}

void Juego::mostrarPistas() {
    cout << "\n  " << detective->getNombre()
         << ", mira las pistas que llevas:\n";
    pilaPistas->mostrar();
}

void Juego::mostrarSospechosos() {
    cout << "\n  " << detective->getNombre()
         << ", sospechosos del caso:\n";
    tablaSospechosos->mostrar();
}



void Juego::faseFinal(bool acusacionForzada) {
    cout << "\n  ================================================\n";
    if (acusacionForzada && !detective->haGanado()) {
        cout << "  ATENCION: Solo llevas "
             << detective->getPistasRecogidas()
             << " de 10 pistas. Acusar ahora es arriesgado!\n";
    } else {
        cout << "  " << detective->getNombre()
             << ", has recolectado las 10 pistas!\n";
    }
    cout << "  Es momento de acusar.\n";
    mostrarSospechosos();

    cout << "\n  A quien acusas? > ";
    string acusado;
    // Limpiar buffer antes de getline
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, acusado);

    cout << "\n  Buscando a " << acusado << " en la Tabla Hash...\n";
    Sospechoso* s = tablaSospechosos->buscar(acusado);

    if (s == nullptr) {
        cout << "  Ese sospechoso no existe en el caso. Acusacion cancelada.\n";
        // NO termina el juego — el usuario puede seguir jugando
        return;
    }

    if (s->getEsCulpable()) {
        cout << "\n  CASO RESUELTO! " << acusado << " era el culpable!\n";
        casoResuelto = true;
    } else {
        cout << "\n  Acusacion incorrecta. El caso se cierra como fracasado.\n";
        cout << "  El puntaje se penaliza al doble.\n";
        detective->duplicarPuntaje();
        casoResuelto = false;
    }

    juegoTerminado = true;
    cout << "  Puntaje final: " << detective->getPuntaje() << " movimientos.\n";

    historial->guardarPuntaje(detective->getNombre(), detective->getPuntaje());
    cout << "\n";
    historial->mostrarRanking();
}

void Juego::iniciar() {

    cout << "       BIENVENIDO AL CASO DEL DETECTIVE     \n";

    inicializarSospechosos();
    inicializarDetective();

    while (!juegoTerminado) {
        cout << "\n";
        detective->mostrarEstado();
        mapa->imprimirTablero(detective->getFila(), detective->getColumna());


        cout << "\n  [W/A/S/D] Mover   [T] Ver pistas  [Z] Sospechosos";
        cout << "\n  [I] Interrogar    [X] Usar pista  [R] Acusar ahora  [Q] Rendirse\n";
        cout << "  > ";

        char cmd;
        cin >> cmd;
        cmd = toupper(cmd);

        // CORRECCIÓN 1: convertir Z a 'B' antes del switch para que no
        // colisione con la tecla 'S' de mostrarSospechosos.
        if (cmd == 'S') cmd = 'B';

        switch (cmd) {
            case 'W':   // arriba
            case 'A':   // izquierda
            case 'B':   // abajo(S convertido)
            case 'D':   // derecha
                moverDetective(cmd);
                break;

            case 'T':
                mostrarPistas();
                break;

            case 'S':
                mostrarSospechosos();
                break;

            case 'I':
                interrogarTestigo();
                break;

            case 'X':
                usarPista();
                break;

            // acusar en cualquier momento
            case 'R':
                faseFinal(true);
                break;

            case 'Q':
                cout << "  Te rendiste. El caso queda sin resolver.\n";
                detective->duplicarPuntaje();
                juegoTerminado = true;
                historial->guardarPuntaje(detective->getNombre(),
                                          detective->getPuntaje());
                cout << "\n";
                historial->mostrarRanking();
                break;

            default:
                cout << "  Comando invalido.\n";
        }

        // Activar fase final automática al recolectar las 10 pistas
        if (detective->haGanado() && !juegoTerminado)
            faseFinal(false);
    }
}