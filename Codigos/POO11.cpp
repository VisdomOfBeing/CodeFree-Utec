#include<iostream>
#include <utility>
#include <vector>
using namespace std;
class CProducto{
private:
    string Nombre;
    double precio;
    int cantidad;
    double descuento;
    public:
    explicit CProducto(string Nombre="", double precio=0, int cantidad=0,double descuento=0){
        this->Nombre = std::move(Nombre);
        this->precio = precio;
        this->cantidad = cantidad;
        this->descuento = descuento;
    }
    ~CProducto()=default;
    [[nodiscard]] double TotalDescuento()const {
        return precio*cantidad*(1-descuento/100);
    }
    void leerDatos() {
        cout<<"Nombre: ";cin>>Nombre;
        cout<<"Precio: ";cin>>precio;
        cout<<"Cantidad: ";cin>>cantidad;
        cout<<"Descuento: ";cin>>descuento;
    }
    void MostrarDatos()const {
        cout<<"\nNombre: "<<Nombre;
        cout<<"\nPrecio: "<<precio;
        cout<<"\nCantidad: "<<cantidad;
        cout<<"\nDescuento: "<<descuento;
        cout<<"\nTotal Descuento: "<<TotalDescuento();
    }
};
int main() {
    int n=0;
    cout<<"Numero de productos: ";cin>>n;
    vector<CProducto> productos;
    for(int i=0;i<n;i++) {
        productos.emplace_back();
        productos.back().leerDatos();
    }
    for(int i=0;i<n;i++) {
        productos[i].MostrarDatos();
    }
    return 0;
}