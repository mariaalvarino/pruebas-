#include "redestaciones.h"
#include <iostream>
#include <cstdlib>  // Para el rand()
#include <ctime>    // Para la semilla de rand()

using namespace std;
void menu(){
    cout <<endl<< "         MENU PRINCIPAL    " << endl;
    cout << "1 Agregar estacion de servicio" << endl;
    cout << "2 Eliminar estacion de Servicio" << endl;
    cout << "3 Agregar surtidor a una estacion" << endl;
    cout << "4 Eliminar surtidor de una estacion" << endl;
    cout << "5 Simular venta de combustible" << endl;
    cout << "6 Mostrar historial de transacciones de una estacion" << endl;
    cout << "7 Calcular ventas totales por categoria" << endl;
    cout << "8 Fijar precios de combustible por region" << endl;
    cout << "9 verificar fugas de combustible" << endl;
    cout << "10 Salir" << endl;
    cout << "Seleccione una opcion: ";
}
int main() {
    srand(time(0));  // Inicializa la semilla para números aleatorios

    RedEstaciones redEstaciones(100);  // Se inicializa la red con capacidad para 100 estaciones

    int opcion;

    do {

        menu();
        cin >> opcion;

        switch (opcion) {
        case 1: {
            // agregar estacion
            std::string nombre, codigo, gerente, region;
            float lat, lon;
            cout<<endl << "Ingrese el nombre de la estacion: "; cin >> nombre;
            cout << "Ingrese el codigo de la estacion: "; cin >> codigo;
            cout << "Ingrese el nombre del gerente: "; cin >> gerente;
            cout << "Ingrese la region (Norte/Centro/Sur): "; cin >> region;
            cout << "Ingrese la latitud de la estacion: "; cin >> lat;
            cout << "Ingrese la longitud de la estacion: "; cin >> lon;

            EstacionServicio estacion(nombre, codigo, gerente, region, lat, lon, 150, 180, 170);
            redEstaciones.agregarEstacion(estacion);
            cout << "Estacion de servicio agregada exitosamente." << endl;
            break;
        }
        case 2: {
            // Eliminar estacion
            string codigo;
            cout << endl<<"Ingrese el codigo de la estacion a eliminar: "; cin >> codigo;
            redEstaciones.eliminarEstacion(codigo);
            break;
        }
        case 3: {
            // Agregar surtidor
            string codigoEstacion;
            int codigoSurtidor;
            string modeloSurtidor;
            cout <<endl<< "Ingrese el codigo de la estacion: "; cin >> codigoEstacion;
            cout<<endl << "Ingrese el codigo del surtidor: "; cin >> codigoSurtidor;
            cout << "Ingrese el modelo del surtidor: "; cin >> modeloSurtidor;

            bool estacionEncontrada = false;
            for (int i = 0; i < redEstaciones.getContadorEstaciones(); i++) {
                EstacionServicio* estacion = redEstaciones.getEstacion(i);
                if (estacion && estacion->getCodigo() == codigoEstacion) {
                    estacion->agregarSurtidor(codigoSurtidor, modeloSurtidor);
                    cout << "Surtidor agregado a la estacion" << endl;
                    estacionEncontrada = true;
                    break;
                }
            }
            if (!estacionEncontrada) {
                cout << "Estacion no encontrada." <<endl;
            }
            break;
        }
        case 4: {
            // Eliminar Surtidor
            std::string codigoEstacion;
            int codigoSurtidor;
            cout << endl<<"Ingrese el codigo de la estacion: "; cin >> codigoEstacion;
            cout << "Ingrese el codigo del surtidor: "; cin >> codigoSurtidor;

            bool estacionEncontrada = false;
            for (int i = 0; i < redEstaciones.getContadorEstaciones(); i++) {
                EstacionServicio* estacion = redEstaciones.getEstacion(i);
                if (estacion && estacion->getCodigo() == codigoEstacion) {
                    estacion->eliminarSurtidor(codigoSurtidor);
                    std::cout << "Surtidor eliminado de la estacion" << endl;
                    estacionEncontrada = true;
                    break;
                }
            }
            if (!estacionEncontrada) {
                cout << "Estacion no encontrada" << endl;
            }
            break;
        }
        case 5:{
            // Simular Venta de Combustible
            string codigoEstacion, categoria;
            float cantidadSolicitada, precioPorLitro;
            int documentoCliente;
            cout << endl<<"Ingrese el codigo de la estacion: "; cin >> codigoEstacion;
            cout << "Ingrese la categoria de combustible (Regular, Premium, EcoExtra): "; cin >> categoria;
            cout << "Ingrese la cantidad de combustible solicitada: "; cin >> cantidadSolicitada;
            cout << "Ingrese el precio por litro: "; cin >> precioPorLitro;
            cout << "Ingrese el documento del cliente: "; cin >> documentoCliente;

            bool estacionEncontrada = false;

            for (int i = 0; i < redEstaciones.getContadorEstaciones(); i++) {
                EstacionServicio* estacion = redEstaciones.getEstacion(i);
                if (estacion && estacion->getCodigo() == codigoEstacion) {
                    estacion->simularVenta(cantidadSolicitada, precioPorLitro, categoria, documentoCliente);
                    cout << "Venta simulada exitosamente" << endl;
                    estacionEncontrada = true;
                    break;
                }
            }
            if (!estacionEncontrada) {
                cout << "Estacion no encontrada" << endl;
            }
            break;
        }
        case 6: {
            // Mostrar historial de transacciones
            string codigoEstacion;
            cout <<endl<< "Ingrese el codigo de la estacion: "; cin >> codigoEstacion;

            bool estacionEncontrada = false;
            for (int i = 0; i < redEstaciones.getContadorEstaciones(); i++) {
                EstacionServicio* estacion = redEstaciones.getEstacion(i);
                if (estacion && estacion->getCodigo() == codigoEstacion) {
                    estacion->mostrarSurtidores();
                    estacionEncontrada = true;
                    break;
                }
            }
            if (!estacionEncontrada) {
                cout << "Estacion no encontrada " << std::endl;
            }
            break;
        }
        case 7: {
            // Calcular ventas totales por categoria
            float totalRegular = 0, totalPremium = 0, totalEcoExtra = 0;
            redEstaciones.calcularVentasTotal(totalRegular, totalPremium, totalEcoExtra);

            cout <<endl<< "Ventas totales en la red de estaciones:" << endl;
            cout << "Regular: " << totalRegular << " pesos" << endl;
            cout << "Premium: " << totalPremium << " pesos" << endl;
            cout << "EcoExtra: " << totalEcoExtra << " pesos" << endl;
            break;
        }
        case 8: {
            // Fijar precios del combustible
            float precioRegular, precioPremium, precioEcoExtra;
            cout <<endl<< "Ingrese el precio por litro para Regular: "; cin >> precioRegular;
            cout << "Ingrese el precio por litro para Premium: "; cin >> precioPremium;
            cout << "Ingrese el precio por litro para EcoExtra: "; cin >> precioEcoExtra;

            redEstaciones.fijarPreciosCombustible(precioRegular, precioPremium, precioEcoExtra);
            break;
        }
        case 9: {
            // Verificar Fugas de Combustible
            std::string codigoEstacion;
            std::cout << "\nIngrese el código de la estación para verificar fugas: "; std::cin >> codigoEstacion;

            if (redEstaciones.verificarFugas(codigoEstacion)) {
                std::cout << "Se detectó fuga en la estación." << std::endl;
            } else {
                std::cout << "No se detectaron fugas en la estación." << std::endl;
            }
            break;

        }
        case 10:
            cout << "Gracias por usar nuestros servicios" << endl;
            break;

        default:
            cout << "Opcion invalida seleccione una opcion valida" << endl;
        }

    } while (opcion != 10);

    return 0;
}
