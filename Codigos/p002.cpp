#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
class Viaje {
private:
    string destino;
    int tiempoViaje;
    bool temporadaAlta; // false no, true si 0 1
    string clase;
public:
    Viaje(string dest, int tiempo, bool alta, string cls)
    : destino(dest), tiempoViaje(tiempo), temporadaAlta(alta), clase(cls) {}
    virtual ~Viaje() {}
    double calcularCosto() const {
        double costo = tiempoViaje * 50.0;

        if (temporadaAlta) {
            costo *= 2;
        }

        if (clase == "business") {
            costo *= 4;
        }

        if (destino == "Madrid") {
            costo += 500;
        } else if (destino == "Berlin") {
            costo += 1000;
        } else if (destino == "Sidney") {
            costo += 1500;
        } else if (destino == "Seul") {
            costo += 2000;
        }
        return costo;
    }
    void imprimirDetalles() const {
        cout << left
             << setw(10) << destino
             << setw(10) << tiempoViaje
             << setw(18) << (temporadaAlta ? "Si (Alta)" : "No (Baja)")
             << setw(10) << clase
             << setw(10) << "Costo: $"
             << fixed << setprecision(2) << calcularCosto() << endl;
    }
};
int main() {
    vector<Viaje*> viajes;
    viajes.push_back(new Viaje("Madrid", 5, false, "economy"));
    viajes.push_back(new Viaje("Berlin", 10, true, "business"));
    viajes.push_back(new Viaje("Sidney", 8, true, "economy"));
    viajes.push_back(new Viaje("Seul", 12, false, "business"));
    viajes.push_back(new Viaje("Madrid", 3, true, "business"));
    cout << "--- Resultados de los Costos de Viaje ---" << endl;
    cout << left
         << setw(10) << "Destino"
         << setw(10) << "Tiempo"
         << setw(18) << "Temporada"
         << setw(10) << "Clase"
         << "Costo Calculado" << endl;
    cout << string(60, '-') << endl;

    for (const Viaje* viajePtr : viajes) {
        if (viajePtr != nullptr) {
            viajePtr->imprimirDetalles();
        }
    }

    for (Viaje* viajePtr : viajes) {
        delete viajePtr;
    }
    viajes.clear();

    cout << string(60, '-') << endl;

    return 0;
}