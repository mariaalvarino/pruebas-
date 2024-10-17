#include "estacionservicio.h"
#include <iostream>
#include <sstream>    
#include <iomanip>   
#include <chrono>
#include <ctime>


// Constructor por defecto
EstacionServicio::EstacionServicio()
    : nombre(""), codigo(""), gerente(""), region(""), surtidorCount(0), tanque(0, 0, 0) {
    coordenadas[0] = 0;
    coordenadas[1] = 0;
}

// Constructor con parámetros
EstacionServicio::EstacionServicio(string n, string c, string g, string r, float lat, float lon, float capReg, float capPrem, float capEco)
    : nombre(n), codigo(c), gerente(g), region(r), coordenadas{lat, lon}, surtidorCount(0), tanque(capReg, capPrem, capEco) {
    // Llenar el tanque con valores iniciales, por ejemplo, llenando los tanques al 50%
    tanque.llenarTanque("Regular", capReg / 2);
    tanque.llenarTanque("Premium", capPrem / 2);
    tanque.llenarTanque("EcoExtra", capEco / 2);
}

// Método para obtener el código de la estación
string EstacionServicio::getCodigo() const {
    return codigo;
}
//Método para obtener la region de la estación
string EstacionServicio::getRegion() const {
    return region;
}

// Método para agregar un surtidor
bool EstacionServicio::agregarSurtidor(int codigo, string modelo) {
    if (surtidorCount < 12) {
        surtidores[surtidorCount++] = Surtidor(codigo, modelo);
        return true;
    }
    std::cout << "No se pueden agregar más surtidores." << std::endl;
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
            std::cout << "Surtidor " << codigo << " eliminado." << std::endl;
            return true;
        }
    }
    std::cout << "Surtidor no encontrado." << std::endl;
    return false;
}

// Método para simular la venta de combustible
void EstacionServicio::simularVenta(float cantidadSolicitada, const string& categoria, int documentoCliente) {
    if (surtidorCount == 0) {
        cout << "No hay surtidores disponibles para realizar la venta." << endl;
        return;
    }

    float cantidadVendida = tanque.venderCombustible(cantidadSolicitada, categoria);
    if (cantidadVendida > 0) {
        // Guarda la fecha y hora de la simulación de venta
        auto now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        tm now_tm = *localtime(&now_c);

        std::ostringstream fechaStream, horaStream;
        fechaStream << std::put_time(&now_tm, "%Y-%m-%d");
        horaStream << std::put_time(&now_tm, "%H:%M:%S");

        string fecha = fechaStream.str();
        string hora = horaStream.str();
        float precioPorLitro = obtenerPrecioPorCategoria(categoria);
        float monto = cantidadVendida * precioPorLitro;

        Transaccion nuevaTransaccion(fecha, hora, cantidadVendida, categoria, "Efectivo", documentoCliente, monto);
        surtidores[0].registrarTransaccion(nuevaTransaccion); // Se registra en el primer surtidor

        cout << "Venta realizada: " << cantidadVendida << " litros de " << categoria << " por " << monto << endl;
    } else {
        cout << "No hay suficiente combustible disponible para la venta solicitada." << endl;
    }
}

// Método para mostrar los surtidores
void EstacionServicio::mostrarSurtidores() const {
    for (int i = 0; i < surtidorCount; i++) {
        std::cout << "Surtidor: " << surtidores[i].getCodigo() << ", Modelo: " << surtidores[i].getModelo() << std::endl;
        surtidores[i].mostrarHistorico();
    }
}

// Método para verificar si hay surtidores activos
bool EstacionServicio::tieneSurtidoresActivos() const {
    for (int i = 0; i < surtidorCount; i++) {
        if (surtidores[i].isActivo()) {
            return true;
        }
    }
    return false;
}

// Método para calcular las ventas por categoría
void EstacionServicio::calcularVentasPorCategoria(float& totalRegular, float& totalPremium, float& totalEcoExtra) const {
    for (int i = 0; i < surtidorCount; i++) {
        surtidores[i].calcularVentasPorCategoria(totalRegular, totalPremium, totalEcoExtra);
    }
}
//Metodo para obtener el tanque de la Estacion de Servicio
Tanque& EstacionServicio::getTanque() {
    return tanque;  
}
float EstacionServicio::obtenerPrecioPorCategoria(const std::string& categoria) const {
    if (region == "Norte") {
        if (categoria == "Regular") return precios.precioRegularNorte;
        else if (categoria == "Premium") return precios.precioPremiumNorte;
        else if (categoria == "EcoExtra") return precios.precioEcoNorte;
    } else if (region == "Centro") {
        if (categoria == "Regular") return precios.precioRegularCentro;
        else if (categoria == "Premium") return precios.precioPremiumCentro;
        else if (categoria == "EcoExtra") return precios.precioEcoCentro;
    } else if (region == "Sur") {
        if (categoria == "Regular") return precios.precioRegularSur;
        else if (categoria == "Premium") return precios.precioPremiumSur;
        else if (categoria == "EcoExtra") return precios.precioEcoSur;
    }
    return 0; // En caso de no encontrar categoría
}