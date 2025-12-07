#include <vector>
#include<iostream>
using namespace std;
class CEmpleado {
private:
    string nombre;
    int horas;
    double pagoHoras;
public:
    CEmpleado(const string &_nombre,int _horas,double _pagoHoras) {
        nombre=_nombre;
        horas=_horas;
        pagoHoras=_pagoHoras;
    }
    ~CEmpleado() {
        cout<<endl;
        cout<<"Destruido!"<<endl;
    }
    [[nodiscard]] string nombre1() const {
        return nombre;
    }
    void set_nombre(const string &_nombre) {
        nombre = _nombre;
    }
    [[nodiscard]] int horas1() const {
        return horas;
    }
    void set_horas(int _horas) {
        horas = _horas;
    }
    [[nodiscard]] double pago_horas() const {
        return pagoHoras;
    }
    void set_pago_horas(double _pagoHoras) {
        pagoHoras = _pagoHoras;
    }
    [[nodiscard]] double CalcularSueldo() const {
        return pagoHoras*horas;
    }
    static CEmpleado MostrarDatos(const string &nombre, int horas, int pago_horas) {
        return CEmpleado(nombre,horas, pago_horas);
    }
};
int main() {
    int n=0;
    int horas=0;
    double pago=0;
    string nombre;
    cout<<"Tamanio: ";cin>>n;
    vector<CEmpleado>empleados;
    empleados.reserve(n);
    for (int i=0;i<n;i++) {
        cout<<"\nNombre: ";cin>>nombre;
        cout<<"\nHoras: ";cin>>horas;
        cout<<"\nPago: ";cin>>pago;
        empleados.emplace_back(nombre,horas,pago);
    }
    cout<<endl;
    for (int i=0;i<n;i++) {
        cout<<"\nNombre: "<<nombre;
        cout<<"\nHoras: "<<horas;
        cout<<"\nPago: "<<pago;
        cout<<endl;
    }
    return 0;
}