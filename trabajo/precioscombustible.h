#ifndef PRECIOSCOMBUSTIBLE_H
#define PRECIOSCOMBUSTIBLE_H

class PreciosCombustible {
public:
    float precioRegularNorte;
    float precioPremiumNorte;
    float precioEcoNorte;

    float precioRegularCentro;
    float precioPremiumCentro;
    float precioEcoCentro;

    float precioRegularSur;
    float precioPremiumSur;
    float precioEcoSur;

    PreciosCombustible() {
        precioRegularNorte = 10000;
        precioPremiumNorte = 12000;
        precioEcoNorte = 9000;

        precioRegularCentro = 11000;
        precioPremiumCentro = 13000;
        precioEcoCentro = 95000;

        precioRegularSur = 10500;
        precioPremiumSur = 12500;
        precioEcoSur = 9200;
    }
};

#endif // PRECIOSCOMBUSTIBLE_H