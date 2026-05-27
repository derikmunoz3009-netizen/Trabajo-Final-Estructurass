#include "Sospechoso.h"
#include <iostream>
using namespace std;

Sospechoso::Sospechoso() : nombre(""), esCulpable(false) {}

Sospechoso::Sospechoso(string nombre, vector<string> atributos)
    : nombre(nombre), atributos(atributos), esCulpable(false) {
    atributosRevelados.resize(atributos.size(), false);
}

string Sospechoso::getNombre()     const { return nombre; }
bool   Sospechoso::getEsCulpable() const { return esCulpable; }

void Sospechoso::marcarCulpable() { esCulpable = true; }

void Sospechoso::revelarSiguienteAtributo() {
    for (int i = 0; i < (int)atributosRevelados.size(); i++) {
        if (!atributosRevelados[i]) {
            atributosRevelados[i] = true;
            cout << "  Nuevo dato del culpable revelado: " << atributos[i] << endl;
            return;
        }
    }
    cout << "  No hay mas atributos por revelar." << endl;
}

void Sospechoso::mostrar() const {
    cout << "  " << nombre << " | atributos confirmados: ";
    bool hayAlguno = false;
    for (int i = 0; i < (int)atributos.size(); i++) {
        if (atributosRevelados[i]) {
            if (hayAlguno) cout << ", ";
            cout << atributos[i];
            hayAlguno = true;
        }
    }
    if (!hayAlguno) cout << "-";
    cout << endl;
}

void Sospechoso::mostrarTodo() const {
    cout << "  " << nombre << ": ";
    for (int i = 0; i < (int)atributos.size(); i++) {
        if (i > 0) cout << ", ";
        cout << atributos[i];
    }
    if (esCulpable) cout << " [CULPABLE]";
    cout << endl;
}
