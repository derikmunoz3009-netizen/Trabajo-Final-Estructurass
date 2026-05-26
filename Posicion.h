#ifndef POSICION_H
#define POSICION_H

class Posicion {
private:
    int fila;
    int columna;

public:
    Posicion();
    Posicion(int fila, int columna);

    int getFila() const;
    int getColumna() const;

    void setFila(int fila);
    void setColumna(int columna);

    bool esIgual(const Posicion& otra) const;
};

#endif