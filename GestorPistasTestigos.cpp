#include "GestorPistasTestigos.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

GestorPistasTestigos::GestorPistasTestigos() {
    pistasRecogidas = 0;
    srand((unsigned)time(NULL));
}

char GestorPistasTestigos::generarTipoPistaAleatorio() const {
    int numero = rand() % 4;
    if (numero == 0) return 'H';
    if (numero == 1) return 'C';
    if (numero == 2) return 'T';
    return 'P';
}

bool GestorPistasTestigos::posicionOcupada(Posicion posicion) const {
    for (Pista p : pistasOcultas) {
        if (p.getPosicion().esIgual(posicion)) return true;
    }

    for (Testigo t : testigosEnMapa) {
        if (t.getPosicion().esIgual(posicion)) return true;
    }

    return false;
}

void GestorPistasTestigos::agregarPosicionesAleatorias(list<Posicion> posicionesLibres) {
    generarPistas(posicionesLibres);
    generarTestigos(posicionesLibres);
}

void GestorPistasTestigos::generarPistas(list<Posicion>& posicionesLibres) {
    int creadas = 0;

    while (creadas < 10 && !posicionesLibres.empty()) {
        int salto = rand() % posicionesLibres.size();
        list<Posicion>::iterator it = posicionesLibres.begin();
        advance(it, salto);

        Posicion posicion = *it;
        posicionesLibres.erase(it);

        char tipo = generarTipoPistaAleatorio();
        Pista nuevaPista(tipo, posicion);
        pistasOcultas.push_back(nuevaPista);
        creadas++;
    }
}

void GestorPistasTestigos::generarTestigos(list<Posicion>& posicionesLibres) {
    int creados = 0;

    while (creados < 5 && !posicionesLibres.empty()) {
        int salto = rand() % posicionesLibres.size();
        list<Posicion>::iterator it = posicionesLibres.begin();
        advance(it, salto);

        Posicion posicion = *it;
        posicionesLibres.erase(it);

        string nombre = "Testigo " + to_string(creados + 1);
        string declaracion = "El testigo entrega una declaracion para revelar un atributo del culpable.";
        Testigo nuevoTestigo(nombre, declaracion, posicion);
        testigosEnMapa.push_back(nuevoTestigo);
        creados++;
    }
}

bool GestorPistasTestigos::hayPistaEn(Posicion posicion) const {
    for (Pista p : pistasOcultas) {
        if (p.getPosicion().esIgual(posicion)) return true;
    }
    return false;
}

bool GestorPistasTestigos::hayTestigoEn(Posicion posicion) const {
    for (Testigo t : testigosEnMapa) {
        if (t.getPosicion().esIgual(posicion)) return true;
    }
    return false;
}

bool GestorPistasTestigos::recogerPista(Posicion posicion) {
    for (list<Pista>::iterator it = pistasOcultas.begin(); it != pistasOcultas.end(); ++it) {
        if (it->getPosicion().esIgual(posicion)) {
            cout << "Encontraste una pista: " << it->getNombreTipo() << " (" << it->getTipo() << ")" << endl;
            pilaPistas.push(*it);
            pistasOcultas.erase(it);
            pistasRecogidas++;
            return true;
        }
    }

    return false;
}

bool GestorPistasTestigos::recogerTestigo(Posicion posicion) {
    for (list<Testigo>::iterator it = testigosEnMapa.begin(); it != testigosEnMapa.end(); ++it) {
        if (it->getPosicion().esIgual(posicion)) {
            cout << "Encontraste a " << it->getNombre() << ". Su declaracion entra a la cola." << endl;
            colaTestigos.push(*it);
            testigosEnMapa.erase(it);
            return true;
        }
    }

    return false;
}

void GestorPistasTestigos::mostrarPistas() const {
    if (pilaPistas.empty()) {
        cout << "No tienes pistas recogidas." << endl;
        return;
    }

    stack<Pista> copia = pilaPistas;
    int contador = 1;

    cout << "Pistas recogidas, de ultima a primera:" << endl;
    while (!copia.empty()) {
        Pista p = copia.top();
        copia.pop();

        cout << contador << ". " << p.getNombreTipo() << " (" << p.getTipo() << ")";
        if (contador == 1) cout << " <- ultima, esta se usa con X";
        cout << endl;
        contador++;
    }
}

void GestorPistasTestigos::mostrarColaTestigos() const {
    if (colaTestigos.empty()) {
        cout << "No hay declaraciones pendientes por interrogar." << endl;
        return;
    }

    queue<Testigo> copia = colaTestigos;
    int contador = 1;

    cout << "Declaraciones pendientes en cola:" << endl;
    while (!copia.empty()) {
        Testigo t = copia.front();
        copia.pop();

        cout << contador << ". " << t.getNombre() << endl;
        contador++;
    }
}

void GestorPistasTestigos::usarUltimaPista(int& puntaje, IAccionesCiudad& ciudad) {
    if (pilaPistas.empty()) {
        cout << "No puedes usar X porque no tienes pistas." << endl;
        return;
    }

    Pista pista = pilaPistas.top();
    pilaPistas.pop();

    cout << "Usaste la pista: " << pista.getNombreTipo() << " (" << pista.getTipo() << ")" << endl;

    if (pista.getTipo() == 'H') {
        puntaje = puntaje / 2;
        cout << "Beneficio: tu puntaje se redujo a la mitad." << endl;
    }
    else if (pista.getTipo() == 'C') {
        ciudad.eliminarCallejonesAleatorios(2);
        cout << "Beneficio: se eliminaron 2 callejones cerrados." << endl;
    }
    else if (pista.getTipo() == 'T') {
        int resultado = rand() % 2;
        if (resultado == 0) {
            puntaje = 0;
            cout << "Resultado del testimonio: tu puntaje volvio a 0." << endl;
        } else {
            puntaje = puntaje * 2;
            cout << "Resultado del testimonio: tu puntaje se duplico." << endl;
        }
    }
    else if (pista.getTipo() == 'P') {
        ciudad.teletransportarDetective();
        cout << "Beneficio: el detective fue teletransportado." << endl;
    }

    ciudad.reubicarPistaAleatoriamente(pista.getTipo());
    ciudad.taparMapa();
    cout << "La pista usada vuelve a quedar escondida en la ciudad." << endl;
}

void GestorPistasTestigos::interrogarTestigo() {
    if (colaTestigos.empty()) {
        cout << "No hay testigos en la cola para interrogar." << endl;
        return;
    }

    Testigo testigo = colaTestigos.front();
    colaTestigos.pop();

    cout << "Interrogando a " << testigo.getNombre() << "..." << endl;
    cout << testigo.getDeclaracion() << endl;
    cout << "Aqui la Persona 3 debe llamar la funcion para revelar un atributo del culpable." << endl;
}

int GestorPistasTestigos::getPistasRecogidas() const {
    return pistasRecogidas;
}

bool GestorPistasTestigos::completoLas10Pistas() const {
    return pistasRecogidas >= 10;
}
