#ifndef PROIECT_POO_PROCEDURA_H
#define PROIECT_POO_PROCEDURA_H
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <map>

#include "Exceptii.h"

using namespace std;

class Procedura {
    int IDProc;
    const int pretPeMinut;
    double pret;
    int durata;
    string specializare;

    static map<int, Procedura> proceduri;
public:
    // --- constructor fara param ---
    Procedura() : pretPeMinut(3), specializare("Not def") {
        IDProc = rand() % (1000 - 100);
        pret = 0.0;
        durata = 0;
    }
    // --- constructor cu toti param ---
    Procedura(const string& specializare, const int IDProc, const double pret,
              const int durata, const int pretPeMinut)
        : IDProc(IDProc), pret(pret), durata(durata), pretPeMinut(pretPeMinut),
          specializare(specializare) {
        if (durata < 0) throw ExceptieProcedura("Durata procedurii nu poate fi negativa", IDProc);
        if (this->specializare.empty())
            throw ExceptieProcedura("Specializare invalida pentru procedura", IDProc);
    }
    // --- constructor cu param (ID generat random) ---
    Procedura(const string& specializare, const int durata)
        : pretPeMinut(3), pret(durata * 3), durata(durata), specializare(specializare) {
        IDProc = rand() % (1000 - 100);
        if (durata < 0) throw ExceptieProcedura("Durata procedurii nu poate fi negativa", IDProc);
        if (this->specializare.empty())
            throw ExceptieProcedura("Specializare invalida pentru procedura", IDProc);
        adaugareProcedura(*this);
    }
    // --- constructor fara specializare (cu ID dat) ---
    Procedura(const int IDProc, const int durata)
        : pretPeMinut(3), pret(durata * 3), durata(durata), IDProc(IDProc),
          specializare("Orice specializare") {
        if (durata < 0) throw ExceptieProcedura("Durata procedurii nu poate fi negativa", IDProc);
        adaugareProcedura(*this);
    }
    // --- constructor fara specializare & ID random ---
    Procedura(const int durata)
        : pretPeMinut(3), pret(durata * 3), durata(durata),
          specializare("Orice specializare") {
        IDProc = rand() % (1000 - 100);
        if (durata < 0) throw ExceptieProcedura("Durata procedurii nu poate fi negativa", IDProc);
        adaugareProcedura(*this);
    }

    // Destructor (compiler-generated default is sufficient for string)
    ~Procedura() noexcept { cout << "~Procedura() a fost apelat\n"; }

    // --- getters ---
    const string& getSpecializare() const { return specializare; }
    int getIDProc() const { return IDProc; }
    double getPret() const { return pret; }
    int getDurata() const { return durata; }
    int getPretMinut() const { return pretPeMinut; }

    // --- setters ---
    void setSpecializare(const string& cpySpecializare) {
        if (cpySpecializare.empty()) throw ExceptieProcedura("Specializare invalida (sir gol)");
        this->specializare = cpySpecializare;
    }
    void setIdProc(const int idNou) { IDProc = idNou; }
    void setPret(const double pretNou) { pret = pretNou; }
    void setDurata(const int durataNoua) {
        if (durataNoua < 0) throw ExceptieProcedura("Durata procedurii nu poate fi negativa", IDProc);
        durata = durataNoua;
    }

    // --- operator >> ---
    friend istream &operator>>(istream &is, Procedura &p) {
        cout << "Care este durata procedurii (in minute) : ";
        is >> p.durata;
        cout << "Ce specializare este necesara : ";
        is >> ws;
        getline(is, p.specializare);
        p.pret = p.durata * 3.0;
        adaugareProcedura(p);
        return is;
    }

    // --- operator << ---
    friend ostream &operator<<(ostream &os, const Procedura &p) {
        os << "Procedura ID=" << p.IDProc << ", durata=" << p.durata
           << " min, pret=" << p.pret << " LEI, specializare: " << p.specializare << "\n";
        return os;
    }

    // --- operator + (adauga minute) ---
    friend Procedura operator+(const Procedura& p, int nrMin) {
        int cpyDurata = p.durata + nrMin;
        double cpyPret = cpyDurata * 3.0;
        Procedura p1(p.specializare, p.IDProc, cpyPret, cpyDurata, p.pretPeMinut);
        return p1;
    }
    friend Procedura operator+(int nrMin, const Procedura& p) { return p + nrMin; }

    // --- operator - (scade minute) ---
    friend Procedura operator-(const Procedura& p, int nrMin) {
        if (p.durata - nrMin >= 0) {
            int cpyDurata = p.durata - nrMin;
            double cpyPret = cpyDurata * 3.0;
            Procedura p1(p.specializare, p.IDProc, cpyPret, cpyDurata, p.pretPeMinut);
            return p1;
        }
        throw ExceptieProcedura("Scaderea ar face durata negativa pentru procedura", p.IDProc);
    }

    // --- operator > ---
    bool operator>(const Procedura& m) const { return pret > m.pret; }
    // --- operator == ---
    bool operator==(const Procedura& m) const { return pret == m.pret; }
    // --- operator [] ---
    const char& operator[](int i) const { return specializare[i]; }
    // --- operator ++ prefixat ---
    Procedura& operator++() { this->durata += 1; return *this; }
    // --- operator ++ postfixat ---
    Procedura operator++(int) {
        Procedura cpy = *this;
        this->durata += 1;
        return cpy;
    }

    // --- lista statica ---
    static void adaugareProcedura(const Procedura& p) {
        // insereaza procedura in map; daca exista deja, sterge si reemplaceaza
        proceduri.erase(p.IDProc);
        proceduri.emplace(p.IDProc, p);
    }

    static void stergereProceduraDupaID(int id) {
        if (proceduri.empty()) {
            cout << "Lista proceduri este goala.\n";
            return;
        }
        auto it = proceduri.find(id);
        if (it == proceduri.end()) {
            cout << "Procedura cu ID-ul " << id << " nu a fost gasita.\n";
            return;
        }
        proceduri.erase(it);
        cout << "Procedura a fost stearsa cu succes.\n";
    }

    static void golesteListaProceduri() { proceduri.clear(); }

    static const map<int, Procedura>& getProceduri() { return proceduri; }
    static int getNrProceduriCreate() { return static_cast<int>(proceduri.size()); }
    // Acces compatibil index-based (pentru codul existent care itereaza prin indice)
    static Procedura& getProceduraByIndex(int index) {
        if (index < 0 || index >= (int)proceduri.size()) throw std::out_of_range("Index procedura invalid");
        auto it = proceduri.begin();
        std::advance(it, index);
        return it->second;
    }
};

inline map<int, Procedura> Procedura::proceduri = map<int, Procedura>();

// Functie demonstrativa care arata stack-unwinding (destructorul localului e apelat)
inline void demoStackUnwinding() {
    try {
        Procedura p("DemoSpecializare", 5);
        cout << "Procedura locala a fost creata. ID=" << p.getIDProc() << "\n";
        throw ExceptieProcedura("Eroare demonstrativa", p.getIDProc());
    } catch (const ExceptieClinica &e) {
        cout << "Exceptie prinsa: " << e.what() << ", id=" << e.getID() << "\n";
    }
}

#endif //PROIECT_POO_PROCEDURA_H
