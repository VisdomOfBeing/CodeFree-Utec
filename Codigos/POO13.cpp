#include<iostream>
#include<string>
#include<vector>
using namespace std;
class CVehiculo {
private:
    string marca;
    string modelo;
    int año;
    double kilometraje;
    public:
    [[nodiscard]] int getaño()const {
        return año;
    }
    CVehiculo() {
        marca="Undefined";
        modelo="Undefined";
        año= 1900;
        kilometraje= 0;
    }
    ~CVehiculo()= default;
    void LeerDatos() {
        cout<<"Marca: ";cin>>marca;
        cout<<"Modelo: ";cin>>modelo;
        cout<<"Año: ";cin>>año;
        cout<<"Kilometraje: ";cin>>kilometraje;
    }
    [[nodiscard]] bool esAntiguo() const{
        if (año<2015) {
            return true;
        }
        return false;
    }
    static int Antiguos(const vector<CVehiculo>&vehiculos) {
        int count=0;
        for (const auto & vehiculo : vehiculos) {
            if (vehiculo.getaño()<2015) {
                count++;
            }
        }
        return count;
    }

    void MostrarDatos(const vector<CVehiculo>&vehiculos) const{
        cout<<"Marca: "<<marca;
        cout<<"Modelo: "<<modelo;
        cout<<"Año: "<<año;
        cout<<"Kilometraje: "<<kilometraje;
        cout<<"Carro Antiguo? ";
        if(esAntiguo()) {
            cout<<"Si"<<endl;
        }
        else {
            cout<<"No"<<endl;
        }
    }
    static void NuevosDatos(const vector<CVehiculo>&vehiculos){
        cout<<"Cuantos son Antiguos: "<< Antiguos(vehiculos);
        cout<<"Menor Kilometraje: ";
        double kilometraje2= vehiculos[0].kilometraje;
        for (auto&vehiculo: vehiculos) {
            if (kilometraje2>vehiculo.kilometraje) {
                kilometraje2=vehiculo.kilometraje;
            }
        }
        cout<<kilometraje2<<endl;
    }
};
int main() {
    vector<CVehiculo>vehiculos;
    int n=0;
    cout<<"Numero de autos: ";cin>>n;
    for(int i=0;i<n;i++) {
        vehiculos.emplace_back();
        vehiculos.back().LeerDatos();
    }
    for(int i=0;i<n;i++) {
        vehiculos[i].MostrarDatos(vehiculos);
        vehiculos[i].NuevosDatos(vehiculos);
    }
    return 0;
}