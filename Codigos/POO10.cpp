#include <iostream>
#include <limits>
#include <vector>
using namespace std;
class CAlumno {
private:
    string Nombre;
    double nota1;
    double nota2;
    double nota3;
    public:
    CAlumno(string name="Anonimo",double const&n1=0,double const&n2=0,double const&n3=0){
        Nombre = name;
        nota1 = n1;
        nota2 = n2;
        nota3 = n3;
    }
    ~CAlumno()=default;
    //Metodos:
    //gettes
    string getNombre() {
        return Nombre;
    }
    void setNombre(string name) {
        Nombre = name;
    }
    double getnota1() const{
        return nota1;
    }
    double getnota2()const {
        return nota2;
    }
    double getnota3() const{
        return nota3;
    }
    void setnota1(double n1) {
        nota1 = n1;
    }
    void setnota2(double n2) {
        nota2 = n2;
    }
    void setnota3(double n3) {
        nota3 = n3;
    }
    void LeerDatos() {
        cout<<"Nombre: ";getline(cin,Nombre);
        cout<<"nota1: ";cin>>nota1;
        cout<<"nota2: ";cin>>nota2;
        cout<<"nota3: ";cin>>nota3;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    [[nodiscard]] double Promedio()const {
        double prom=0;
        prom=(nota1+nota2+nota3)/3;
        return prom;
    }
    [[nodiscard]] bool estado()const {
        if (Promedio()<=10) {
            return false;
        }
        return true;
    }
    void MostrarDatos()const {
        cout<<"Nombre: "<<Nombre<<endl;
        cout<<"nota1: "<<nota1<<endl;
        cout<<"nota2: "<<nota2<<endl;
        cout<<"nota3: "<<nota3<<endl;
        cout<<"Promedio: "<<Promedio()<<endl;
        cout<<"Estado: ";
        if (estado()) {
            cout<<"Aprobado";
        }
        else {
            cout<<"Desaprobado";
        }
    }
};
int main() {
    int n=0;
    cout<<"Numero de Alumnos en el aula: ";cin>>n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<CAlumno> Alumnos;
    for (int i=0;i<n;i++) {
        Alumnos.emplace_back();
        Alumnos.back().LeerDatos();
    }
    for (int i=0;i<n;i++) {
        Alumnos[i].MostrarDatos();
    }
    return 0;
}