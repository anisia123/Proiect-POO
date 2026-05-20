#ifndef PROIECT_POO_CLINICA_H
#define PROIECT_POO_CLINICA_H
#include <iostream>
#include <string>
#include "Animale.h"
#include "Medici.h"
#include "Procedura.h"
using namespace std;

// Clasa Clinica - gestioneaza informatii despre clinica veterinara
class Clinica {
    string numeClinică;
    string adresa;
    int nrCabinete;
    float taxaConsultatie;
    bool deschisa;

    static int nrPacientiTotali;

public:
    // --- constructor fara param ---
    Clinica() : numeClinică("Clinica Veterinara"), adresa("Adresa necunoscuta"),
                nrCabinete(1), taxaConsultatie(50.0f), deschisa(true) {}

    // --- constructor cu toti param ---
    Clinica(const string& nume, const string& adresa, const int nrCabinete,
            const float taxaConsultatie, const bool deschisa)
        : numeClinică(nume), adresa(adresa), nrCabinete(nrCabinete),
          taxaConsultatie(taxaConsultatie), deschisa(deschisa) {}

    // --- constructor cu nume si adresa (valori default pt rest) ---
    Clinica(const string& nume, const string& adresa)
        : numeClinică(nume), adresa(adresa), nrCabinete(3),
          taxaConsultatie(50.0f), deschisa(true) {}

    // --- constructor cu parametru deschisa ---
    Clinica(const string& nume, bool deschisa)
        : numeClinică(nume), adresa("Adresa necunoscuta"), nrCabinete(1),
          taxaConsultatie(50.0f), deschisa(deschisa) {}

    // --- constructor de copiere ---
    Clinica(const Clinica& c) = default;

    // --- Destructor ---
    ~Clinica() = default;

    // --- getters ---
    const string& getNumeClinica() const { return numeClinică; }
    const string& getAdresa() const { return adresa; }
    int getNrCabinete() const { return nrCabinete; }
    float getTaxaConsultatie() const { return taxaConsultatie; }
    bool getDeschisa() const { return deschisa; }
    static int getNrPacientiTotali() { return nrPacientiTotali; }

    // --- setters ---
    void setNumeClinica(const string& numeNou) {
        numeClinică = numeNou;
    }
    void setAdresa(const string& adresaNoua) {
        adresa = adresaNoua;
    }
    void setNrCabinete(int n) { nrCabinete = n; }
    void setTaxaConsultatie(float taxa) { taxaConsultatie = taxa; }
    void setDeschisa(bool d) { deschisa = d; }

    // --- operator >> ---
    friend istream& operator>>(istream& is, Clinica& c) {
        string cpyNume, cpyAdresa;
        cout << "Numele clinicii: ";
        is >> ws;
        getline(is, cpyNume);
        c.setNumeClinica(cpyNume);
        cout << "Adresa clinicii: ";
        is >> ws;
        getline(is, cpyAdresa);
        c.setAdresa(cpyAdresa);
        cout << "Numar cabinete: ";
        is >> c.nrCabinete;
        cout << "Taxa consultatie (LEI): ";
        is >> c.taxaConsultatie;
        cout << "Este deschisa? (1=DA, 0=NU): ";
        is >> c.deschisa;
        return is;
    }

    // --- operator << ---
    friend ostream& operator<<(ostream& os, const Clinica& c) {
        os << "=== " << c.numeClinică << " ===\n"
           << "Adresa: " << c.adresa << "\n"
           << "Cabinete: " << c.nrCabinete << "\n"
           << "Taxa consultatie: " << c.taxaConsultatie << " LEI\n"
           << "Status: " << (c.deschisa ? "DESCHISA" : "INCHISA") << "\n"
           << "Pacienti inregistrati: " << nrPacientiTotali << "\n"
           << "Animale active: " << Animal::getNrAnimale() << "\n"
           << "Medici angajati: " << Medici::getNrMedici() << "\n"
           << "Proceduri disponibile: " << Procedura::getNrProceduriCreate() << "\n";
        return os;
    }

    // --- operator = ---
    Clinica& operator=(const Clinica& c) = default;

    // --- operator + adauga cabinete ---
    friend Clinica operator+(const Clinica& c, int nrCabNoi) {
        Clinica c1(c.numeClinică, c.adresa, c.nrCabinete + nrCabNoi,
                   c.taxaConsultatie, c.deschisa);
        return c1;
    }
    friend Clinica operator+(int nrCabNoi, const Clinica& c) { return c + nrCabNoi; }

    // --- operator - scade cabinete ---
    friend Clinica operator-(const Clinica& c, int nrCabScazute) {
        int nou = (c.nrCabinete - nrCabScazute > 0) ? c.nrCabinete - nrCabScazute : 1;
        Clinica c1(c.numeClinică, c.adresa, nou, c.taxaConsultatie, c.deschisa);
        return c1;
    }

    // --- operator < (comparare dupa nrCabinete) ---
    bool operator<(const Clinica& c) const { return nrCabinete < c.nrCabinete; }
    // --- operator == ---
    bool operator==(const Clinica& c) const { return nrCabinete == c.nrCabinete; }
    // --- operator [] acces la litera din adresa ---
    const char& operator[](int i) const { return adresa[i]; }
    // --- operator ++ (deschide/inchide) ---
    Clinica& operator++() {
        deschisa = !deschisa;
        return *this;
    }
    Clinica operator++(int) {
        Clinica cpy = *this;
        deschisa = !deschisa;
        return cpy;
    }

    // --- functii specifice clinicii ---
    void afiseazaRaport() const {
        cout << "\n--- RAPORT CLINICA ---\n";
        cout << *this;

        // Cel mai bine platit medic
        if (Medici::getNrMedici() > 0) {
            int maxIdx = 0;
            for (int i = 1; i < Medici::getNrMedici(); ++i)
                if (Medici::getMedicByIndex(i) > Medici::getMedicByIndex(maxIdx))
                    maxIdx = i;
            cout << "Cel mai bine platit medic: " << Medici::getMedicByIndex(maxIdx);
        }
        // Animalul cu cele mai multe proceduri
        if (Animal::getNrAnimale() > 0) {
            int maxIdx = 0;
            for (int i = 1; i < Animal::getNrAnimale(); ++i)
                if (Animal::getAnimale()[maxIdx] < Animal::getAnimale()[i])
                    maxIdx = i;
            cout << "Animalul cu cele mai multe proceduri: " << Animal::getAnimale()[maxIdx];
        }
    }
    static void incrementPacienti() { nrPacientiTotali++; }
};

int Clinica::nrPacientiTotali = 0;
#endif //PROIECT_POO_CLINICA_H
