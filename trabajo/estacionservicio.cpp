#include "estacionservicio.h"
#include <iostream>

// Constructor por defecto
EstacionServicio::EstacionServicio()
    : nombre(""), codigo(""), gerente(""), region(""), surtidorCount(0), tanque(0, 0, 0) {
    coordenadas[0] = 0;
    coordenadas[1] = 0;
}

// Constructor con parametros
EstacionServicio::EstacionServicio(string n, string c, string g, string r, float lat, float lon, float capReg, float capPrem, float capEco)
    : nombre(n), codigo(c), gerente(g), region(r), coordenadas{lat, lon}, surtidorCount(0), tanque(capReg, capPrem, capEco) {
    // Llenar el tanque con valores iniciales, por ejemplo, llenando los tanques al 50%
    tanque.llenarTanque("Regular", capReg / 2);
    tanque.llenarTanque("Premium", capPrem / 2);
    tanque.llenarTanque("EcoExtra", capEco / 2);
}
// Metodo para obtener el codigo de la estacion
string EstacionServicio::getCodigo() const {
    return codigo;
}
// Metodo para agregar un surtidor
bool EstacionServicio::agregarSurtidor(int codigo, string modelo) {
    if (surtidorCount < 10) {
        surtidores[surtidorCount++] = Surtidor(codigo, modelo);
        return true;
    }
    cout << "No se pueden agregar mas surtidores" <<endl;
    return false;
}

// Método para eliminar un surtidor
bool EstacionServicio::eliminarSurtidor(int codigo) {
    for (int i = 0; i < surtidorCount; i++) {
        if (surtidores[i].getCodigo() == codigo) {
            for (int j = i; j < surtidorCount - 1; j++) {
                surtidores[j] = surtidores[j + 1];
            }
            surtidorCount--;
            cout << "Surtidor " << codigo << " eliminado" << endl;
            return true;
        }
    }
    cout << "No se encontro el surtidor "<< codigo << std::endl;
    return false;
}

void EstacionServicio::simularVenta(float cantidadSolicitada, float precioPorLitro, const string& categoria, int documentoCliente) {
    if (surtidorCount == 0) {
        std::cout << "No hay surtidores disponibles para realizar la venta." << std::endl;
        return;
    }

    float cantidadVendida = tanque.venderCombustible(cantidadSolicitada, categoria);
    if (cantidadVendida > 0) {
        string fecha = "2024-10-12";  // Ejemplo de fecha estática
        string hora = "12:00";        // Ejemplo de hora estática
        float monto = cantidadVendida * precioPorLitro;
        Transaccion nuevaTransaccion(fecha, hora, cantidadVendida, categoria, "Efectivo", documentoCliente, monto);
        surtidores[0].registrarTransaccion(nuevaTransaccion);
        std::cout << "Venta realizada: " << cantidadVendida << " litros de " << categoria << " por $" << monto << std::endl;
    } else {
        std::cout << "No hay suficiente combustible disponible para la venta solicitada." << std::endl;
    }
}

void EstacionServicio::mostrarSurtidores() const {
    for (int i = 0; i < surtidorCount; i++) {
        cout << "Surtidor: " << surtidores[i].getCodigo() << ", Modelo: " << surtidores[i].getModelo() << endl;
        surtidores[i].mostrarHistorico();
    }
}

//verificar si hay surtidores activos
bool EstacionServicio::tieneSurtidoresActivos() const {
    for (int i = 0; i < surtidorCount; i++) {
        if (surtidores[i].isActivo()) {
            return true;
        }
    }
    return false;
}

//calcular ventas por categoria
void EstacionServicio::calcularVentasPorCategoria(float& totalRegular, float& totalPremium, float& totalEcoExtra) const {
    for (int i = 0; i < surtidorCount; i++) {
        surtidores[i].calcularVentasPorCategoria(totalRegular, totalPremium, totalEcoExtra);
    }
}

bool EstacionServicio::verificarFugas() const {
    float totalVendido = 0;
    for (int i = 0; i < surtidorCount; i++) {
        totalVendido += surtidores[i].getTotalVendido();
    }

    float capacidadTotal = tanque.getCapacidadRegular() + tanque.getCapacidadPremium() + tanque.getCapacidadEcoExtra();
    float almacenadoActual = tanque.getCantidadRegular() + tanque.getCantidadPremium() + tanque.getCantidadEcoExtra();
    float porcentaje = (totalVendido + almacenadoActual) / capacidadTotal;

    return porcentaje < 0.95; // Retorna true si hay fuga
}

