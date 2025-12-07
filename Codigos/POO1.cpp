#include<iostream>
using namespace std;
class CPersona {
    public:
    string nombre;
    int edad=0;
    void saludar() {
        cout <<"Hola soy "<< nombre <<" tengo "<<edad<<" anios"<< endl;
    }
};
int main() {
    string name;
    int edad;
    CPersona p1;
    CPersona p2;
    cout<<"Nombre: ";cin>>name;
    cout<<"Edad: ";cin>>edad;
    p1.nombre=name;
    p1.edad=edad;
    cout<<"Nombre : ";cin>>name;
    cout<<"Edad: ";cin>>edad;
    p2.nombre=name;
    p2.edad=edad;
    cout<<endl;
    p1.saludar();
    p2.saludar();
    return 0;
}