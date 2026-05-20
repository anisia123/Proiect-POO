#ifndef PROIECT_POO_PROPRIETARI_H
#define PROIECT_POO_PROPRIETARI_H
#include <iostream>
#include <string>
#include "Animale.h"
#include "Procedura.h"
using namespace std;

class Proprietar {
    string nume;
    double sumaPlata;
    bool urgenta;
    // PARTEA A 2A - CERINTA 2
    Animal animal;
public:
    // --- constructor fara param ---
    Proprietar() : nume("Not def"), sumaPlata(0.0), urgenta(false) {
        cout << "Proprietar() a fost apelat.\n";
    }

    // --- constructor cu toti param ---
    Proprietar(const string& nume, const Animal& animal, const double sumaPlata, bool urgenta)
        : nume(nume), animal(animal), sumaPlata(sumaPlata), urgenta(urgenta) {
        cout << "Proprietar() a fost apelat.\n";
    }

    // --- constructor cu animal, urgenta & nume ---
    Proprietar(const string& nume, const Animal& animal, bool urgenta)
        : nume(nume), animal(animal), urgenta(urgenta) {
        CalcSumaPlata();
        cout << "Proprietar() a fost apelat.\n";
    }

    // --- constructor cu animal ---
    Proprietar(const Animal& animal) : nume("Not def"), animal(animal), urgenta(false) {
        CalcSumaPlata();
        cout << "Proprietar() a fost apelat.\n";
    }

    // --- constructor de copiere (FIX: const ref) ---
    Proprietar(const Proprietar& p) = default;

    // --- getters ---
    const string& getNume() const { return nume; }
    double getPlata() const { return sumaPlata; }
    bool getUrgenta() const { return urgenta; }
    const Animal& getAnimal() const { return animal; }

    // --- setters ---
    void setNume(const string& numeNou) {
        this->nume = numeNou;
    }
    void setPlata(const double plataNoua) { sumaPlata = plataNoua; }
    void setUrgenta(const bool urgentaNoua) { urgenta = urgentaNoua; }

    // --- Destructor ---
    ~Proprietar() noexcept {
        cout << "~Proprietar() a fost apelat.\n";
    }

    const vector<int>& gasireProceduriAnimal() const {
        return animal.getIstoric();
    }

    int gasireNrProceduri() const {
        return animal.getNrProc();
    }

    void CalcSumaPlata() {
        double plataNoua = 0.0;
        int nrProcAnimal = gasireNrProceduri();
        const vector<int>& istoricCpy = gasireProceduriAnimal();
        int nrListaProc = Procedura::getNrProceduriCreate();

        if (!istoricCpy.empty() && nrListaProc > 0) {
            for (int i = 0; i < nrProcAnimal; ++i) {
                for (int j = 0; j < nrListaProc; ++j) {
                    const Procedura& proc = Procedura::getProceduraByIndex(j);
                    if (istoricCpy[i] == proc.getIDProc()) {
                        plataNoua += proc.getPret();
                    }
                }
            }
        }
        if (urgenta) plataNoua += 100.0;
        setPlata(plataNoua);
    }

    // --- operator >> ---
    friend istream& operator>>(istream& is, Proprietar& p) {
        string cpyNume;
        cout << "Numele proprietarului : ";
        is >> ws;
        getline(is, cpyNume);
        p.nume = cpyNume;
        cout << "Datele Animalului : ";
        is >> p.animal;
        cout << "Este o urgenta? (1 pentru DA sau 0 pentru NU) : ";
        is >> p.urgenta;
        p.CalcSumaPlata();
        return is;
    }

    // --- operator << ---
    friend ostream& operator<<(ostream& os, const Proprietar& p) {
        os << p.nume << ", proprietar al animalului cu Id-ul " << p.animal.getID()
           << " are de platit: " << p.sumaPlata << " LEI.\n";
        if (p.urgenta) os << "Acesta a fost un caz urgent! (+100 LEI taxa urgenta)\n";
        return os;
    }

    // --- operator = ---
    Proprietar& operator=(const Proprietar& p1) = default;

    // --- operator > ---
    bool operator>(const Proprietar& m) const { return sumaPlata > m.sumaPlata; }
    // --- operator == ---
    bool operator==(const Proprietar& m) const { return sumaPlata == m.sumaPlata; }
    // --- operator [] ---
    const char& operator[](int i) const { return nume[i]; }
    // --- operator ++ postfixat (urgenta => taxa +100) ---
    Proprietar operator++(int) {
        Proprietar cpy = *this;
        urgenta = true;
        sumaPlata += 100.0;
        return cpy;
    }
    // --- operator + adauga taxa (FIX: returna p in loc de p1) ---
    friend Proprietar operator+(const Proprietar& p, double const taxa) {
        double cpySumaPlata = p.sumaPlata + taxa;
        Proprietar p1(p.nume, p.animal, cpySumaPlata, p.urgenta);
        return p1;
    }
    friend Proprietar operator+(double const taxa, const Proprietar& p) {
        return p + taxa;
    }
    // --- operator - elimina taxa ---
    friend Proprietar operator-(const Proprietar& p, double const taxa) {
        double cpySumaPlata = p.sumaPlata;
        if (cpySumaPlata - taxa >= 0) cpySumaPlata -= taxa;
        else cpySumaPlata = 0;
        Proprietar p1(p.nume, p.animal, cpySumaPlata, p.urgenta);
        return p1;
    }
};
#endif //PROIECT_POO_PROPRIETARI_H
