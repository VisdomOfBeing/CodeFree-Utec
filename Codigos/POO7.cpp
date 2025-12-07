#include<iostream>
#include <utility>
#include <vector>
using namespace std;
class CEmplado {
private:
    string nombre;
    int horas;
    int pagoHora;
public:
    CEmplado(string const &_nombre, int _horas, int _pagoHora) {
        nombre = _nombre;
        horas = _horas;
        pagoHora = _pagoHora;
    }
    ~CEmplado()= default;
    //Getters:
    string getNombre() {
        return nombre;
    }
    [[nodiscard]] int getHoras() const {
        return horas;
    }
    [[nodiscard]] int getPago() const {
        return pagoHora;
    }
    //Setters:
    void setNombre(string _nombre) {
        nombre = std::move(_nombre);
    }
    void setHoras(int _horas) {
        horas = _horas;
    }
    void setPago(int _pago) {
        pagoHora = _pago;
    }
    // Metodos:
    void leerDatos() {
        cout<<"Nombre: ";cin>>nombre;
        cout<<"Horas: "; cin>>horas;
        cout<<"Pago por Hora: ";cin>>pagoHora;
    }
    void mostrarDatos()const {
        cout<<"Nombre: "<<nombre<<" ";
        cout<<"Horas: "<<horas<<"h"<<" ";
        cout<<"Pago: "<<pagoHora<<"$"<<endl;
        cout<<"Sueldo total: "<<CalcularSueldo()<<endl;
    }
    [[nodiscard]] double CalcularSueldo() const {
        return pagoHora * horas;
    }
    bool GanaMasQue(const CEmplado &otro)const  {
        return CalcularSueldo()>otro.CalcularSueldo();
    }
};
int main() {
    int nempleados=0;
    cout<<"Numero de empleados en la cartilla: ";cin>>nempleados;
    vector<CEmplado> empleados;
    for (int i=0;i<nempleados;i++) {
        CEmplado empleado(" ",0,0);
        empleado.leerDatos();
        empleados.push_back(empleado);
    }
    for (int i=0;i<nempleados;i++) {
        empleados[i].mostrarDatos();
    }
    empleados[0].GanaMasQue(empleados[1]);

    return 0;
}