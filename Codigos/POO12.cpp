#include<iostream>
#include <limits>
#include <vector>
using namespace std;
class CDispositivo {
private:
    string nombre;
    double consumo;
    int horasUso;
public:
    CDispositivo() {
        nombre = "Check out";
        consumo = 0;
        horasUso = 0;
    }
    ~CDispositivo()= default;
    //Metodos:
    [[nodiscard]] bool esEficiente()const {
        if (ConsumoDiario()<1000) return true;
        return false;
    }
    [[nodiscard]] double ConsumoDiario()const {
        return consumo*horasUso;
    }
    void leerDatos() {
        cout<<"Nombre: "; getline(cin,nombre);
        cout<<"Consumo: "; cin>>consumo;
        cout<<"Horas: "; cin>>horasUso;
    }
    void MostrarDatos() const{
        cout<<"\t\nMOSTRAR DATOS";
        cout<<"\nNombre: "<<nombre<<endl;
        cout<<"Consumo: "<<consumo<<endl;
        cout<<"Horas: "<<horasUso<<endl;
        cout<<"Consumo Diario: "<<ConsumoDiario()<<endl;
        cout<<"Eficiencia: ";
        if(esEficiente()) {
            cout<<"Eficiente";
        }
        else {
            cout<<"Not eficiente";
        }
    }
};
int main() {
    vector<CDispositivo> dispositivos;
    int n=0;
    cout<<"\tDISPOSITIVOS";
    cout<<"\nNumero de dispositivos: ";cin>>n;
    for(int i=0;i<n;i++) {
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        dispositivos.emplace_back();
        dispositivos.back().leerDatos();
    }
    for(int i=0;i<n;i++) {
        dispositivos[i].MostrarDatos();
    }
    return 0;
}