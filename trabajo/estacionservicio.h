#ifndef ESTACIONSERVICIO_H
#define ESTACIONSERVICIO_H

#include "surtidor.h"
#include "tanque.h"
#include <string>
using namespace std;

class EstacionServicio {
private:
    string nombre;
    string codigo;
    string gerente;
    string region;
    float coordenadas[2];
    Surtidor surtidores[10];// Arreglo de surtidores
    int surtidorCount;// Contador de surtidores
    Tanque tanque;

public:
    // Constructor por defecto
    EstacionServicio();

    // Constructor con parametros
    EstacionServicio(string n, string c, string g, string r, float lat, float lon, float capReg, float capPrem, float capEco);

    // Métodos
    string getCodigo() const;
    bool agregarSurtidor(int codigo, string modelo);
    bool eliminarSurtidor(int codigo);
    void reportarLitrosVendidos(string categoria) const;
    void simularVenta(float cantidadSolicitada, float precioPorLitro, const string& categoria, int documentoCliente);
    void mostrarSurtidores() const;
    bool tieneSurtidoresActivos() const;
    void calcularVentasPorCategoria(float& totalRegular, float& totalPremium, float& totalEcoExtra) const;
    bool verificarFugas() const;
};

#endif // ESTACIONSERVICIO_H

