#include<iostream>
#include<string>
#include<vector>
using namespace std;
class CNotas {
    private:
    string Nombre;
    int cantNotas;
    double *notas;
    public:
    explicit CNotas(int _cantNotas) {
        Nombre = "";
        cantNotas= _cantNotas;
        notas= new double[cantNotas];
    }
    ~CNotas() {
        delete[] notas;
    }
    [[nodiscard]] double promedio()const {
        double prom=0;
        for(int i=0;i<cantNotas;i++) {
            prom+=notas[i];
        }
        return prom/cantNotas;
    }
    void leerNotas() {
        cout<<"Alumno "<<": ";cin>>Nombre;
        for (int i = 0; i < cantNotas; i++) {
            cout<<"Nota"<<i+1<<": ";cin>>notas[i];
        }
    }
    void MostrarDatos()const {
        cout<<"Nombre: "<<Nombre<<endl;
        for(int i=0;i<cantNotas;i++) {
            cout<<"Nota "<<i+1<<": "<<notas[i];
        }
        cout<<"Promoedio: "<<fixed<<promedio()<<endl;
    }
};
int main() {
    int n=0;
    cout<<"Numero de notas: ";cin>>n;
    CNotas p1(n);
    p1.leerNotas();
    p1.MostrarDatos();


    return 0;
}