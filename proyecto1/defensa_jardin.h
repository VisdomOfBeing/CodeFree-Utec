#ifndef ULTIMACHANCE_CLASES_H
#define ULTIMACHANCE_CLASES_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <ctime>
using namespace std;
class Juego;
class Entidad {
protected:
    double vida;
    double dano;
    int fila;
    int columna;
public:
    explicit Entidad(const double HP = 0,const double danio = 0,const int fil = 0, const int col = 0)
        : vida(HP), dano(danio), fila(fil), columna(col) {}
    virtual ~Entidad() = default;
    virtual void atacar() = 0;
    [[nodiscard]]virtual string getRepresentacion() const = 0;
    Entidad &operator-=(const double cantidad) {
        vida -= cantidad;
        if (vida < 0) vida = 0;
        return *this;
    }
    virtual void recibirDano(double cantidad) {
        *this -= cantidad;
    }
    [[nodiscard]] double getVida() const { return vida; }
    [[nodiscard]] double getDano() const { return dano; }
    [[nodiscard]] int getFila() const { return fila; }
    [[nodiscard]] int getColumna() const { return columna; }
    void setVida(double v) { vida = v; }
    friend ostream& operator<<(ostream& os, const Entidad& e) {
        os << "[HP:" << e.vida << " DMG:" << e.dano
           << " Pos:(" << e.fila << "," << e.columna << ")]";
        return os;
    }
};
class Planta : public Entidad {
protected:
    int costo;
    bool ralentiza;
public:
    Planta(double HP, double danio, int fil, int col, int cost)
        : Entidad(HP, danio, fil, col), costo(cost), ralentiza(false) {}

    ~Planta() override = default;

    virtual void ActivarHabilidad(Juego& juego) = 0;

    [[nodiscard]] int getCosto() const { return costo; }

    // Por defecto las plantas no disparan ni ralentizan
    [[nodiscard]] virtual double getDanoProyectil() const { return 0.0; }
    [[nodiscard]] virtual bool puedeRalentizar() const { return ralentiza; }
    friend ostream& operator<<(ostream& os, const Planta& p) {
        os << p.getRepresentacion() << " "
           << static_cast<const Entidad&>(p)
           << " [Costo:" << p.costo << "]";
        return os;
    }
};
class Zombie : public Entidad {
protected:
    int velocity;           // Cada cuántos turnos avanza
    int countTurnos;
    int turnosRalentizado;
public:
    Zombie(const double HP,const double danio,const int fil,const int col,const int vel)
        : Entidad(HP, danio, fil, col),
          velocity(vel),
          countTurnos(0),
          turnosRalentizado(0) {}

    ~Zombie() override = default;

    virtual void move() = 0;

    void atacar() override {} // Ataque desde Juego

    [[nodiscard]] int getVelocidad() const { return velocity; }
    void setColumna(int newCol) { columna = newCol; }

    [[nodiscard]] string getRepresentacion() const override { return "Z"; }

    void aplicarRalentizacion(int turnos = 2) {
        turnosRalentizado = turnos;
        cout << "Zombi ralentizado por " << turnos << " turnos!\n";
    }

    bool estaRalentizado() const { return turnosRalentizado > 0; }

    void actualizarRalentizacion() {
        if (turnosRalentizado > 0) {
            turnosRalentizado--;
        }
    }

    friend ostream& operator<<(ostream& os, const Zombie& z) {
        os << z.getRepresentacion() << " "
           << static_cast<const Entidad&>(z)
           << " [Vel:" << z.velocity << "]";
        return os;
    }
};

class Juego {
private:
    static const int FILAS = 5;
    static const int COLUMNAS = 9;
    Planta* mapaPlantas[FILAS][COLUMNAS]{};
    vector<Zombie*> zombiesActivos;
    int soles;
    int turno;
    int casaHP;
    int oleadaActual;
    int zombiesEliminados;
    int solesRecolectados;
    int danoRecibido;
    static const int OLEADAS_TOTALES = 10;
    void mostrarMapa() const;
    void colocarPlanta(Planta* planta, int fila, int col);
    void plantarInteractivo();
    void generarOleada();
    void fasePreparacion();
    void guardarResultados(const string& resultado) const;
    int calcularPuntos() const;
public:
    Juego();
    ~Juego();

    void Menu();
    void iniciarPartida();
    void ejecutarTurno();

    void sumarSoles(int cantidad) {
        soles += cantidad;
        solesRecolectados += cantidad;
        cout << "+" << cantidad << " Soles! Total: " << soles << "\n";
    }

    bool restarSoles(int costo) {
        if (soles >= costo) {
            soles -= costo;
            return true;
        }
        return false;
    }

    // Accesores necesarios para habilidades de plantas
    vector<Zombie*>& getZombiesActivos() { return zombiesActivos; }

    static int getFilas()    { return FILAS; }
    static int getColumnas() { return COLUMNAS; }
};

// ======================= SUBCLASES DE PLANTAS =======================

class Girasol : public Planta {
private:
    const int frecuenciaGeneracion;
    int turnosTranscurridos;
public:
    Girasol(int fil, int col)
        : Planta(50.0, 0.0, fil, col, 50),
          frecuenciaGeneracion(2),
          turnosTranscurridos(0) {}

    ~Girasol() override = default;

    [[nodiscard]] string getRepresentacion() const override { return "S"; }

    void atacar() override {}

    void ActivarHabilidad(Juego& juego) override {
        turnosTranscurridos++;
        if (turnosTranscurridos >= frecuenciaGeneracion) {
            juego.sumarSoles(25);
            turnosTranscurridos = 0;
        }
    }
};

class Lanzaguizantes : public Planta {
public:
    Lanzaguizantes(const int fil,const int col)
        : Planta(100.0, 20.0, fil, col, 100) {}

    ~Lanzaguizantes() override = default;

    void atacar() override {}

    void ActivarHabilidad(Juego& /*juego*/) override {
        atacar();
    }

    [[nodiscard]]double getDanoProyectil() const override { return dano; }
    [[nodiscard]] string getRepresentacion() const override { return "P"; }
};

class Nuez : public Planta {
public:
    Nuez(const int fil, const int col)
        : Planta(500.0, 0.0, fil, col, 50) {}
    ~Nuez() override = default;
    void atacar() override {}
    void ActivarHabilidad(Juego& /*juego*/) override {}
    [[nodiscard]] string getRepresentacion() const override { return "O"; }
};
class PlantaHielo : public Planta {
public:
    PlantaHielo(int fil, int col)
        : Planta(80.0, 15.0, fil, col, 175) {
        ralentiza = true;
    }
    ~PlantaHielo() override = default;
    void atacar() override {}
    void ActivarHabilidad(Juego& juego) override {
        for (Zombie* z : juego.getZombiesActivos()) {
            if (z->getFila() == fila && z->getColumna() > columna) {
                z->aplicarRalentizacion(2);
                break;
            }
        }
    }

    [[nodiscard]]double getDanoProyectil() const override { return dano; }
    [[nodiscard]]bool puedeRalentizar() const override { return true; }
    [[nodiscard]] string getRepresentacion() const override { return "I"; }
};
class Petacereza : public Planta { // explosiva
private:
    int turnosParaExplotar;
public:
    Petacereza(const int fil,const int col)
        : Planta(50.0, 150.0, fil, col, 150),
          turnosParaExplotar(1) {}

    ~Petacereza() override = default;
    void atacar() override {}
    void ActivarHabilidad(Juego& juego) override {
        if (turnosParaExplotar > 0) {
            turnosParaExplotar--;
            if (turnosParaExplotar == 0) {
                cout << "BOOM! Petacereza explota en (" << fila << "," << columna << ")!\n";
                for (Zombie* z : juego.getZombiesActivos()) {
                    int difFila = abs(z->getFila()      - fila);
                    int difCol  = abs(z->getColumna()   - columna);
                    if (difFila <= 1 && difCol <= 1) {
                        *z -= dano;
                        cout << "Zombi en (" << z->getFila() << "," << z->getColumna()
                             << ") recibe " << dano << " de dano!\n";
                    }
                }
                vida = 0; // se destruye a sí misma
            }
        }
    }
    [[nodiscard]] string getRepresentacion() const override { return "C"; }
};

class ZombieNormal : public Zombie {
public:
    ZombieNormal(int fil, int col)
        : Zombie(200.0, 25.0, fil, col, 2) {}

    ~ZombieNormal() override = default;

    void move() override {
        actualizarRalentizacion();
        countTurnos++;
        int velActual = estaRalentizado() ? velocity * 2 : velocity;
        if (countTurnos >= velActual) {
            columna--;
            countTurnos = 0;
        }
    }
};

class ZombieConCasco : public Zombie {
public:
    ZombieConCasco(int fil, int col)
        : Zombie(400.0, 20.0, fil, col, 3) {}

    ~ZombieConCasco() override = default;

    void move() override {
        actualizarRalentizacion();
        countTurnos++;
        int velActual = estaRalentizado() ? velocity * 2 : velocity;
        if (countTurnos >= velActual) {
            columna--;
            countTurnos = 0;
        }
    }

    [[nodiscard]] string getRepresentacion() const override { return "H"; }
};

class ZombieToxico : public Zombie {
public:
    ZombieToxico(int fil, int col)
        : Zombie(150.0, 15.0, fil, col, 1) {}

    ~ZombieToxico() override = default;

    void move() override {
        actualizarRalentizacion();
        countTurnos++;
        int velActual = estaRalentizado() ? velocity * 2 : velocity;
        if (countTurnos >= velActual) {
            columna--;
            countTurnos = 0;
        }
    }

    [[nodiscard]] string getRepresentacion() const override { return "T"; }
};

class ZombieRapido : public Zombie {
public:
    ZombieRapido(int fil, int col)
        : Zombie(100.0, 10.0, fil, col, 1) {}

    ~ZombieRapido() override = default;

    void move() override {
        actualizarRalentizacion();
        countTurnos++;
        int velActual = estaRalentizado() ? velocity * 2 : velocity;
        if (countTurnos >= velActual) {
            columna--;
            countTurnos = 0;
        }
    }

    [[nodiscard]] string getRepresentacion() const override { return "R"; }
};

// ======================= IMPLEMENTACION JUEGO =======================

inline Juego::Juego()
    : soles(100),
      turno(0),
      casaHP(100),
      oleadaActual(0),
      zombiesEliminados(0),
      solesRecolectados(0),
      danoRecibido(0) {
    // Inicializar mapa
    for (auto & mapaPlanta : mapaPlantas) {
        for (auto & j : mapaPlanta) {
            j = nullptr;
        }
    }
    srand(static_cast<unsigned>(time(nullptr)));
}

inline Juego::~Juego() {
    for (auto & mapaPlanta : mapaPlantas) {
        for (auto & j : mapaPlanta) {
            delete j;
            j = nullptr;
        }
    }
    for (const Zombie* z : zombiesActivos) {
        delete z;
    }
    zombiesActivos.clear();
}
inline void Juego::mostrarMapa() const {
    cout << "\n===============================================\n";
    cout << "  TURNO: " << turno
         << " | OLEADA: " << oleadaActual << "/" << OLEADAS_TOTALES
         << " | Soles: " << soles
         << " | Casa HP: " << casaHP << "\n";
    cout << "  Zombis eliminados: " << zombiesEliminados
         << " | Activos: " << zombiesActivos.size() << "\n";
    cout << "===============================================\n";

    cout << "    | SPAWN <--- Col " << (COLUMNAS - 1)
         << " | DEFENSA ---> Col 0 |\n";
    cout << " Fila |";
    for (int j = 0; j < COLUMNAS; ++j) {
        cout << setw(3) << j;
    }
    cout << " |\n";

    cout << "------";
    for (int j = 0; j < COLUMNAS; ++j) {
        cout << "----";
    }
    cout << "-\n";

    for (int i = 0; i < FILAS; ++i) {
        cout << setw(4) << i << " |";
        for (int j = 0; j < COLUMNAS; ++j) {
            string celda = " . ";
            if (mapaPlantas[i][j] != nullptr) {
                celda = " " + mapaPlantas[i][j]->getRepresentacion() + " ";
            }
            for (Zombie* z : zombiesActivos) {
                if (z->getFila() == i && z->getColumna() == j) {
                    celda = " " + z->getRepresentacion() + " ";
                    break;
                }
            }
            cout << celda;
        }
        cout << " |\n";
    }
    cout << "\nLEYENDA: S=Girasol | P=Lanzaguisantes | O=Nuez | I=Hielo | C=Cereza\n";
    cout << "         Z=Normal | H=Casco | T=Toxico | R=Rapido\n";
}

inline void Juego::colocarPlanta(Planta* planta, int fila, int col) {
    if (fila >= 0 && fila < FILAS && col >= 0 && col < COLUMNAS) {
        if (mapaPlantas[fila][col] == nullptr) {
            if (restarSoles(planta->getCosto())) {
                mapaPlantas[fila][col] = planta;
                cout << "Planta " << planta->getRepresentacion()
                     << " colocada en (" << fila << "," << col << ")\n";
                return;
            }
            else {
                cout << "Soles insuficientes (Necesitas "<< planta->getCosto() << ").\n";
            }
        }
        else {
            cout << "Casilla ocupada.\n";
        }
    }
    else {
        cout << "Posicion invalida.\n";
    }
    delete planta;
}
inline void Juego::plantarInteractivo() {
    int opcion_planta, fil, col;
    cout << "\n========== PLANTAR (Soles: " << soles << ") ==========\n";
    cout << "1. Girasol        (50)  [S] - Genera soles\n";
    cout << "2. Lanzaguizantes (100) [P] - Ataque basico\n";
    cout << "3. Nuez           (50)  [O] - Defensa alta\n";
    cout << "4. Planta Hielo   (175) [I] - Ralentiza y dispara\n";
    cout << "5. Petacereza     (150) [C] - Explota area\n";
    cout << "6. Cancelar\n";
    cout << "===================================================\n";
    cout << "Elige planta: ";

    if (!(cin >> opcion_planta)) {
        cout << "Entrada invalida.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (opcion_planta >= 1 && opcion_planta <= 5) {
        cout << "Fila (0-" << (FILAS - 1) << "): ";
        if (!(cin >> fil)) {
            cout << "Entrada invalida.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cout << "Columna (0-" << (COLUMNAS - 1) << "): ";
        if (!(cin >> col)) {
            cout << "Entrada invalida.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Planta* nuevaPlanta = nullptr;
        switch (opcion_planta) {
        case 1:{ nuevaPlanta = new Girasol(fil, col);        break;}
        case 2: {nuevaPlanta = new Lanzaguizantes(fil, col); break;}
        case 3: {nuevaPlanta = new Nuez(fil, col);           break;}
        case 4: {nuevaPlanta = new PlantaHielo(fil, col);    break;}
        case 5: {nuevaPlanta = new Petacereza(fil, col);     break;}
        default: break;
        }
        if (nuevaPlanta != nullptr) {
            colocarPlanta(nuevaPlanta, fil, col);
        }
    } else {
        // limpiar buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Cancelado.\n";
    }
}
inline void Juego::generarOleada() {
    oleadaActual++;
    cout << "\n=======================================\n";
    cout << "    OLEADA " << oleadaActual
         << " DE " << OLEADAS_TOTALES << "\n";
    cout << "=======================================\n";
    // OLEADAS, inspiracion de la PC3 estrategia
    int cantidadZombis = 2 + oleadaActual;
    for (int i = 0; i < cantidadZombis; ++i) {
        int filaAleatoria = rand() % FILAS;
        if (oleadaActual >= 7 && rand() % 2 == 0) {
            zombiesActivos.push_back(
                new ZombieConCasco(filaAleatoria, COLUMNAS - 1));
        } else if (oleadaActual >= 4 && rand() % 3 == 0) {
            zombiesActivos.push_back(
                new ZombieRapido(filaAleatoria, COLUMNAS - 1));
        } else if (rand() % 4 == 0) {
            zombiesActivos.push_back(
                new ZombieToxico(filaAleatoria, COLUMNAS - 1));
        } else {
            zombiesActivos.push_back(
                new ZombieNormal(filaAleatoria, COLUMNAS - 1));
        }
    }
    cout << cantidadZombis << " zombis generados!\n";
}

inline void Juego::fasePreparacion() {
    bool preparacionTerminada = false;
    while (!preparacionTerminada) {
        mostrarMapa();
        cout << "\n======= FASE DE PREPARACION =======\n";
        cout << "1. Plantar\n";
        cout << "2. Comenzar oleada\n";
        cout << "Opcion: ";
        string opc;
        cin >> opc;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (opc == "1") {
            plantarInteractivo();
        } else if (opc == "2") {
            preparacionTerminada = true;
        } else {
            cout << "Opcion invalida.\n";
        }
    }
}
inline int Juego::calcularPuntos() const {
    int puntos = 0;
    puntos += zombiesEliminados * 100;
    puntos += solesRecolectados * 2;
    puntos += oleadaActual * 500;
    puntos += casaHP * 10;
    return puntos;
}
inline void Juego::guardarResultados(const string& resultado) const {
    ofstream archivo("Estadisticas.txt", ios::app);//append, al final
    if (archivo.is_open()) {
        archivo << "========================================\n";
        archivo << "Fecha: " << __DATE__ << " " << __TIME__ << "\n";
        archivo << "Resultado: " << resultado << "\n";
        archivo << "Oleadas: " << oleadaActual << "/" << OLEADAS_TOTALES << "\n";
        archivo << "Zombis eliminados: " << zombiesEliminados << "\n";
        archivo << "Soles recolectados: " << solesRecolectados << "\n";
        archivo << "Dano recibido: " << danoRecibido << "\n";
        archivo << "Casa HP final: " << (casaHP < 0 ? 0 : casaHP) << "\n";
        archivo << "PUNTOS: " << calcularPuntos() << "\n";
        archivo << "========================================\n\n";
        archivo.close();
        cout << "Estadisticas guardadas.\n";
    } else {
        cout << "Error al guardar estadisticas.\n";
    }
}
inline void Juego::Menu() {
    string opc;
    bool salir = false;
    while (!salir) {
        cout << "\n========================================\n";
        cout << "          DEFENSA DEL JARDIN\n";
        cout << "========================================\n";
        cout << "1. Jugar\n";
        cout << "2. Ver estadisticas\n";
        cout << "3. Salir\n";
        cout << "========================================\n";
        cout << "Elige opcion: ";
        cin >> opc;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (opc == "1") {
            iniciarPartida();
        } else if (opc == "2") {
            ifstream archivo("Estadisticas.txt");
            if (archivo.is_open()) {
                string linea;
                cout << "\n========== HISTORIAL ==========\\n";
                while (getline(archivo, linea)) {
                    cout << linea << "\n";
                }
                cout << "================================\n";
                archivo.close();
            } else {
                cout << "No hay estadisticas guardadas.\n";
            }
        } else if (opc == "3") {
            cout << "Hasta pronto!\n";
            salir = true;
        } else {
            cout << "Opcion invalida. Intenta de nuevo.\n";
        }
    }
}
inline void Juego::iniciarPartida() {
    turno = 0;
    casaHP = 100;
    soles = 100;
    oleadaActual = 0;
    zombiesEliminados = 0;
    solesRecolectados = 0;
    danoRecibido = 0;
    // Limpiar mapa y zombis
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            delete mapaPlantas[i][j];
            mapaPlantas[i][j] = nullptr;
        }
    }
    for (const Zombie* z : zombiesActivos) {
        delete z;
    }
    zombiesActivos.clear();
    // Planta inicial
    colocarPlanta(new Girasol(2, 2), 2, 2);
    cout << "\nPartida iniciada! Defiende tu jardin.\n";
    while (casaHP > 0 && oleadaActual < OLEADAS_TOTALES) {
        fasePreparacion();
        generarOleada();
        // Mientras haya zombis en esta oleada y la casa no haya caido
        while (casaHP > 0 && !zombiesActivos.empty()) {
            ejecutarTurno();
        }
    }
    string resultado;
    if (casaHP <= 0) {
        resultado = "DERROTA";
        cout << "\n=============================\n";
        cout << "   LOS ZOMBIS HAN GANADO\n";
        cout << "=============================\n";
    } else {
        resultado = "VICTORIA";
        cout << "\n=============================\n";
        cout << "  VICTORIA! JARDIN DEFENDIDO\n";
        cout << "=============================\n";
    }
    int puntosFinal = calcularPuntos();
    cout << "\n====== ESTADISTICAS FINALES ======\n";
    cout << "Oleadas completadas: " << oleadaActual << "/" << OLEADAS_TOTALES << "\n";
    cout << "Zombis eliminados:   " << zombiesEliminados << "\n";
    cout << "Soles recolectados:  " << solesRecolectados << "\n";
    cout << "Dano a la casa:      " << danoRecibido << "\n";
    cout << "Casa HP final:       " << (casaHP < 0 ? 0 : casaHP) << "\n"; //ternario
    cout << "PUNTOS TOTALES:      " << puntosFinal << "\n";
    cout << "==================================\n";
    guardarResultados(resultado);
}
inline void Juego::ejecutarTurno() {
    //  decisión del jugador
    bool avanzarTurno = false; // turnos y oleadas
    while (!avanzarTurno && casaHP > 0 && !zombiesActivos.empty()) {
        cout << "\n--- TURNO " << (turno + 1)<< " | Soles: " << soles
             << " | Casa HP: " << casaHP<< " | Zombis activos: " << zombiesActivos.size()
             << " ---\n";
        mostrarMapa();
        cout << "1. Plantar\n";
        cout << "2. Ejecutar turno (plantas y zombis actuan)\n";
        cout << "3. Rendirse (terminar partida)\n";
        cout << "Opcion: ";
        string opc;
        cin >> opc;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (opc == "1") {
            plantarInteractivo();
        } else if (opc == "2") {
            avanzarTurno = true;
        } else if (opc == "3") {
            casaHP = 0;
            return;
        } else {
            cout << "Opcion invalida. Intenta de nuevo.\n";
        }
    }
    if (casaHP <= 0 || zombiesActivos.empty()) return;
    // Ejecutar el turno r
    turno++;
    cout << "\n======== EJECUTANDO TURNO " << turno << " ========\n";
    // FASE DE PLANTAS
    for (int i = 0; i < FILAS; ++i) {
        //Habilidades
        for (int j = 0; j < COLUMNAS; ++j) {
            if (mapaPlantas[i][j] != nullptr) {
                mapaPlantas[i][j]->ActivarHabilidad(*this);
            }
        }
        // Disparos
        for (int j = 0; j < COLUMNAS; ++j) {
            if (mapaPlantas[i][j] != nullptr &&
                mapaPlantas[i][j]->getDanoProyectil() > 0) {

                double danioProyectil = mapaPlantas[i][j]->getDanoProyectil();
                bool esHielo = mapaPlantas[i][j]->puedeRalentizar();

                for (Zombie* z : zombiesActivos) {
                    if (z->getFila() == i && z->getColumna() > j) {
                        cout << "Pew! Planta en (" << i << "," << j
                             << ") ataca zombi en ("
                             << z->getFila() << "," << z->getColumna() << ")\n";

                        *z -= danioProyectil;
                        if (esHielo && !z->estaRalentizado()) {
                            z->aplicarRalentizacion(2);
                        }
                        break; // solo al primer zombi a la derecha
                    }
                }
            }
        }
    }
    // FASE DE ZOMBIS
    for (Zombie* z : zombiesActivos) {
        Planta* plantaBloqueando = nullptr;
        if (z->getColumna() > 0) {
            plantaBloqueando = mapaPlantas[z->getFila()][z->getColumna() - 1];
        }
        if (plantaBloqueando != nullptr) {
            cout << "Zombi ataca planta en ("
                 << z->getFila() << "," << (z->getColumna() - 1) << ")\n";
            *plantaBloqueando -= z->getDano();
        } else {
            z->move();
        }
        // Ataque a la casa
        if (z->getColumna() < 0) {
            int d = static_cast<int>(z->getDano());
            casaHP -= d;
            danoRecibido += d;
            cout << "CASA ATACADA! -" << d
                 << " HP (Restante: " << casaHP << ")\n";
        }
    }
    //LIMPIEZA DE PLANTAS MUERTAS
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            if (mapaPlantas[i][j] != nullptr &&
                mapaPlantas[i][j]->getVida() <= 0) {
                cout << "Planta en (" << i << "," << j << ") destruida.\n";
                delete mapaPlantas[i][j];
                mapaPlantas[i][j] = nullptr;
            }
        }
    }
    // LIMPIEZA DE ZOMBIS
    for (int i = 0; i < static_cast<int>(zombiesActivos.size()); ) {
        if (zombiesActivos[i]->getVida() <= 0) {
            cout << "Zombi eliminado!\n";
            zombiesEliminados++;
            delete zombiesActivos[i];
            zombiesActivos.erase(zombiesActivos.begin() + i);
        } else if (zombiesActivos[i]->getColumna() < 0) {
            delete zombiesActivos[i];
            zombiesActivos.erase(zombiesActivos.begin() + i);
        } else {
            ++i;
        }
    }
    cout << "======== FIN TURNO " << turno << " ========\n";
}
#endif //ULTIMACHANCE_CLASES_H