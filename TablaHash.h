#ifndef TABLAHASH_H
#define TABLAHASH_H

#include "Sospechoso.h"
#include <vector>
using namespace std;

struct NodoHash {
    string nombre;
    Sospechoso sospechoso;
    NodoHash* siguiente;
    NodoHash(string n, Sospechoso s)
        : nombre(n), sospechoso(s), siguiente(nullptr) {}
};

class TablaHash {
private:
    static const int TAMANO = 11;
    vector<NodoHash*> tabla;

    int funcionHash(const string& nombre) const;

public:
    TablaHash();
    ~TablaHash();

    void        insertar(const string& nombre, const Sospechoso& s);
    Sospechoso* buscar(const string& nombre);
    bool        existe(const string& nombre) const;

    void   revelarAtributoACulpable();
    void   mostrar() const;
    string getNombreCulpable() const;
};

#endif
