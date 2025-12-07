#include<iostream>
using namespace std;
class CRectangulo {
private:
    double base;
    double altura;
    public:
    CRectangulo() {
        base=0;
        altura=0;
    }
    ~CRectangulo() {
        cout << "\nDestruccion correcta" << endl;
    }
    void setbase(double b) {
        base = b;
    }
    [[nodiscard]] double getbase() const {
        return base;
    }
    [[nodiscard]] double getaltura() const {
        return altura;
    }
    void setaltura(double a) {
        altura = a;
    }
    [[nodiscard]] double Area() const {
        return base * altura;
    }
    [[nodiscard]] double Perimetro() const {
        return 2*(base + altura);
    }
};
int main() {
    CRectangulo Rectangulo;
    double baze=0;
    double altura=0;
    cout<<"Base: ";cin>>baze;
    cout<<"Altura: ";cin>>altura;
    Rectangulo.setbase(baze);
    Rectangulo.setaltura(altura);
    cout<<"Area: "<<Rectangulo.Area()<<endl;
    cout<<"Perimetro: "<<Rectangulo.Perimetro();
    return 0;
}