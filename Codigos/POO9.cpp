#include<iostream>
#include <limits>
#include<string>
#include<vector>
using namespace std;
class CLibro {
    private:
    string titulo;
    string autor;
    int paginas;
    public:
    CLibro(string const &titulo="", string const &autor="Anonimo", int const &paginas=1) {
        this->titulo = titulo;
        this->autor = autor;
        this->paginas = paginas;
    }
    string getTitulo() {
        return titulo;
    }
    string getAutor() {
        return autor;
    }
    int getPaginas() const {
        return paginas;
    }
    void setTitulo(string const &_titulo){
        titulo = _titulo;
    }
    void setAutor(string const &_autor) {
        autor = _autor;
    }
    void setPaginas(int const &_paginas) {
        paginas = _paginas;
    }
    //Metodos:
    void leerDatos() {
        cout<<"\nTitulo: ";getline(cin, titulo);
        cout<<"\nAutor: ";getline(cin,  autor);
        cout<<"\nPaginas: ";cin>>paginas;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    bool esLargo()const {
        if (paginas>300) {
            return true;
        }
        return false;
    }
    void MostrarDatos()const {
        cout<<"Titulo: "<<titulo<<endl;
        cout<<"Autor: "<<autor<<endl;
        cout<<"Paginas: "<<paginas<<endl;
        cout<<"Es largo el libro?";
        if (esLargo()) cout<<"Si";
        else cout<<"No";
        cout<<endl;
    }

};
int main() {
    vector<CLibro>Libros;
    int n=0;
    cout<<"lIBROS NUMERO: ";cin>>n;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    for(int i=0;i<n;i++) {
        Libros.emplace_back();
        Libros.back().leerDatos();
    }
    for (int i=0;i<n;i++) {
        Libros[i].MostrarDatos();
    }
    return 0;
}