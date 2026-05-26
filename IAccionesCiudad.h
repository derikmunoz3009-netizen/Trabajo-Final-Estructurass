#ifndef IACCIONESCIUDAD_H
#define IACCIONESCIUDAD_H

class IAccionesCiudad {
public:
    virtual ~IAccionesCiudad() {}

    virtual void taparMapa() = 0;
    virtual void eliminarCallejonesAleatorios(int cantidad) = 0;
    virtual void reubicarPistaAleatoriamente(char tipoPista) = 0;
    virtual void teletransportarDetective() = 0;
};

#endif