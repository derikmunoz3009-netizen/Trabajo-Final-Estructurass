#ifndef COLA_H
#define COLA_H

#include <string>
using namespace std;

struct NodoCola {
    string declaracion;
    NodoCola* siguiente;
    NodoCola(string d) : declaracion(d), siguiente(nullptr) {}
};

class Cola {
private:
    NodoCola* frente;
    NodoCola* final_;
    int tamano;

public:
    Cola();
    ~Cola();

    void   encolar(string declaracion);
    string desencolar();
    bool   estaVacia() const;
    int    getTamano() const;

    void mostrar() const;
};

#endif
