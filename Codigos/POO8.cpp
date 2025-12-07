#include<iostream>
#include<string>
#include<iomanip>
#include <utility>
#include <vector>
using namespace std;
class CProducto {
private:
    string Nombre;
    double Precio;
    int stock;
public:
    CProducto() {
        Nombre = "Undefined";
        Precio = 0;
        stock = 0;
    }
    ~CProducto() = default;
    void setNombre(string name) {
        Nombre = std::move(name);
    }
    void setPrecio(double _Precio) {
        Precio = _Precio;
    }
    void setStock(int _stock) {
        stock = _stock;
    }
    int getStock() const{
        return stock;
    }
    //Metodos:
    void leerDatos() {
        cout<<"Nombre: ";cin>>Nombre;
        cout<<"Precio: ";cin>>Precio;
        cout<<"Stock: ";cin>>stock;
    }
    double CalcularTotal(int const cantidad)const {
        return Precio*cantidad;
    }
    void mostrarDatos(int const cantidad) const{
        cout<<"Nombre: "<<Nombre<<setw(2)<<"Precio: "<<Precio;
        cout<<"Stock: "<<stock;
        cout<<endl;
        cout<<"Total: "<<CalcularTotal(cantidad);
    }
};
int main() {
    int n=0;
    cout<<"TAMANIO: ";cin>>n;
    vector<CProducto> productos;
    for(int i=0;i<n;i++) {
        productos.emplace_back();
        productos.back().leerDatos();
    }
    for(int i=0;i<n;i++) {
        int cantidades=0;
        if (cantidades > productos[i].getStock()) {
            cout << "No hay suficiente stock.\n";
        } else
        productos[i].mostrarDatos(cantidades);
    }
    return 0;
}