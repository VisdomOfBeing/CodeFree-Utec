#include<iostream>
#include<string>
using namespace std;
class CCuentaBancaria {
private:
    string titular;
    double saldo;
    public:
    CCuentaBancaria(string _t="", double _s=0) {
        titular=_t;
        saldo=_s;
    }
    ~CCuentaBancaria() {
        cout<<"\nCCuentaBancaria destruida";
    }
    double get_saldo() {
        return saldo;
    }
    void set_saldo(double _s) {
        saldo=_s;
    }
    string get_titular() {
        return titular;
    }
    void set_titular(string _t) {
        titular=std::move(_t);
    }
    //metodos
    double Depositar() {
        double valor=0;
        cout<<"Depósito: ";cin>>valor;
        if(valor<0) {
            cout<<"Valor negativo no depositado";
            cout<<"Proceda a otra opcion";
        }
        saldo=saldo+valor;
        return saldo;
    }
    double Retirar() {
        double retiro=0;
        cout<<"Retiro: ";cin>>retiro;
        if(retiro<0) {
            cout<<"Valor negativo no retiro";
        }
        saldo=saldo-retiro;
        return saldo;
    }

};
int main() {
    CCuentaBancaria p1;
    CCuentaBancaria p2;
    string name;
    double saldo_i=0;
    cout<<"Titular: ";cin>>name;
    cout<<"Saldo: ";cin>>saldo_i;
    p1.set_titular(name);
    p1.set_saldo(saldo_i);
    cout<<"Titular: ";cin>>name;
    p2.set_titular(name);
    cout<<"Saldo: ";cin>>saldo_i;
    p2.set_saldo(saldo_i);
    p1.Depositar();
    cout<<endl;
    p2.Depositar();
    cout<<endl;
    p1.Retirar();
    cout<<endl;
    p2.Retirar();
    cout<<endl;
    cout<<"Titular: "<< p1.get_titular()<<"Saldo: "<<p1.get_saldo();
    cout<<endl;
    cout<<"Titular: "<<p2.get_titular()<<"Saldo: "<<p2.get_saldo();
    return 0;
}