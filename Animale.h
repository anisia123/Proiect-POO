#ifndef PROIECT_POO_ANIMALE_H
#define PROIECT_POO_ANIMALE_H
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "Procedura.h"
#include "Exceptii.h"
#include <vector>
using namespace std;

class Animal {
protected:
    string nume;
    int ID;
    vector<int> istoric; // ID-urile procedurilor facute
    int nrProc;
    char gen;

private:
    static Animal* animale;
    static int nrAnimale;

public:
    // --- constructor fara param ---
    Animal() : nume("Not def"), gen('N') {
        ID = rand() % (1000 - 100);
        nrProc = 0;
        istoric = vector<int>();
        cout << "Animal() a fost apelat.\n";
    }

    // --- constructor cu toti param ---
    Animal(const string &nume, const int ID, const vector<int>& istoric, const int nrProc, const char gen)
        : nume(nume), ID(ID), nrProc(nrProc), gen(gen) {
        if (ID < 0) throw ExceptieAnimalInvalid("ID invalid pentru animal", ID);
        if (this->nume.empty()) throw ExceptieAnimalInvalid("Nume invalid pentru animal", ID);
        if (nrProc > 0 && !istoric.empty()) {
            this->istoric = vector<int>(istoric);
        }
        else {
            this->istoric = vector<int>();
            this->nrProc = 0;
        }
        cout << "Animal() a fost apelat.\n";
    }

    // --- constructor cu param (ID generat random) ---
    Animal(const string &nume, const vector<int>& istoric, const int nrProc, const char gen)
        : nume(nume), nrProc(nrProc), gen(gen) {
        ID = rand() % (1000 - 100);
        if (this->nume.empty()) throw ExceptieAnimalInvalid("Nume invalid pentru animal", ID);
        if (nrProc > 0 && !istoric.empty()) {
            this->istoric = vector<int>(istoric);
            for (int i = 0; i < nrProc; ++i) this->istoric[i] = istoric[i];
        } else {
            this->istoric = vector<int>();
            this->nrProc = 0;
        }
        adaugareAnimal(*this);
        cout << "Animal() a fost apelat.\n";
    }

    // --- constructor cu nrProc si proceduri (ID random, fara nume) ---
    Animal(const vector<int>& istoric, const int nrProc) : nume("Not def"), nrProc(nrProc) {
        ID = rand() % (1000 - 100);
        if (nrProc > 0 && !istoric.empty()) {
            this->istoric = vector<int>(istoric);
            for (int i = 0; i < nrProc; ++i) this->istoric[i] = istoric[i];
        } else {
            this->istoric = vector<int>();
            this->nrProc = 0;
        }
        gen = 'N';
        adaugareAnimal(*this);
        cout << "Animal() a fost apelat.\n";
    }

    // --- constructor de copiere ---
    Animal(const Animal& aCpy) : nume(aCpy.nume), ID(aCpy.ID), nrProc(aCpy.nrProc), gen(aCpy.gen) {
        if (aCpy.nrProc > 0 && aCpy.istoric.size() > 0) {
            this->istoric = vector<int>(aCpy.istoric);
        } else {
            this->istoric = vector<int>();
            this->nrProc = 0;
        }
    }

    // --- getters ---
    const string& getNume() const { return nume; }
    int getID() const { return ID; }
    const vector<int>& getIstoric() const { return istoric; }
    int getNrProc() const { return nrProc; }
    char getGen() const { return gen; }

    // --- setters ---
    void setNume(const string &numeNou) {
        if (numeNou.empty()) throw ExceptieAnimalInvalid("Nume invalid pentru animal");
        this->nume = numeNou;
    }
    void setGen(const char genNou) { gen = genNou; }
    void setID(const int idNou) { if (idNou < 0) throw ExceptieAnimalInvalid("ID invalid pentru animal", idNou); ID = idNou; }

    // --- Destructor ---
    virtual ~Animal() noexcept {
        cout << "~Animal() a fost apelat\n";
    }

    // --- operator >> ---
    friend istream &operator>>(istream &is, Animal &a) {
        string cpyNume;
        cout << "Numele Animalului : ";
        is >> ws;
        getline(is, cpyNume);
        if (cpyNume.empty()) throw ExceptieAnimalInvalid("Nume invalid pentru animal la citire");
        a.nume = cpyNume;
        cout << "Genul animalului (M/F) : ";
        is >> a.gen;
        cout << "Cate proceduri a avut : ";
        is >> a.nrProc;
        if (a.nrProc > 0) {
            a.istoric = vector<int>(a.nrProc);
            cout << "Care sunt acestea (ID-urile lor) : ";
            for (int i = 0; i < a.nrProc; ++i) is >> a.istoric[i];
        }
        adaugareAnimal(a);
        return is;
    }

    // --- operator << ---
    friend ostream &operator<<(ostream &os, const Animal &a) {
        os << a.nume << ", salvat/a in sistem cu ID-ul " << a.ID
           << ", genul: " << a.gen
           << ", a avut nevoie de " << a.nrProc << " proceduri";
        if (a.nrProc > 0 && a.istoric.size() > 0) {
            os << ", iar acestea sunt: ";
            for (int i = 0; i < a.nrProc; ++i) os << a.istoric[i] << " ";
        }
        os << "\n";
        return os;
    }

    // --- operator + (adauga procedura) ---
    friend Animal operator+(const Animal& a, int idProc) {
        vector<int> cpyIstoric = a.istoric;
        cpyIstoric.push_back(idProc);
        Animal a1(a.nume, a.ID, cpyIstoric, a.nrProc + 1, a.gen);
        return a1;
    }
    friend Animal operator+(int idProc, const Animal& a) { return a + idProc; }

    // --- operator - (scoate procedura cu ID dat) ---
    friend Animal operator-(const Animal& a, int idProc) {
        int n = 0;
        for (int i = 0; i < a.nrProc; ++i)
            if (a.istoric[i] == idProc) n++;
        int newSize = a.nrProc - n;
        vector<int> cpyIstoric = (newSize > 0) ? vector<int>(newSize) : vector<int>();
        int k = 0;
        for (int i = 0; i < a.nrProc; ++i)
            if (a.istoric[i] != idProc) cpyIstoric[k++] = a.istoric[i];
        Animal a1(a.nume, a.ID, cpyIstoric, newSize, a.gen);
        return a1;
    }

    // --- operator = ---
    Animal& operator=(const Animal& a1) {
        if (this == &a1) return *this;
        nrProc = a1.nrProc;
        ID = a1.ID;
        gen = a1.gen;
        nume = a1.nume;
        istoric = (nrProc > 0) ? vector<int>(a1.istoric) : vector<int>();
        for (int i = 0; i < nrProc; ++i) istoric[i] = a1.istoric[i];
        return *this;
    }

    // --- operator < ---
    bool operator<(const Animal& m) const { return nrProc < m.nrProc; }
    // --- operator == ---
    bool operator==(const Animal& m) const { return nrProc == m.nrProc; }
    // --- operator [] ---
    const int& operator[](int i) const { return istoric[i]; }
    // --- operator ++ prefixat ---
    Animal& operator++() {
        this->nrProc += 1;
        return *this;
    }
    // --- operator ++ postfixat ---
    Animal operator++(int) {
        Animal cpy = *this;
        this->nrProc += 1;
        return cpy;
    }

    // --- lista statica ---
    static void adaugareAnimal(const Animal& a) {
        Animal* temporar = nullptr;
        if (animale != nullptr) {
            temporar = new Animal[nrAnimale];
            for (int i = 0; i < nrAnimale; ++i) temporar[i] = animale[i];
            delete[] animale;
            animale = nullptr;
        }
        animale = new Animal[nrAnimale + 1];
        for (int i = 0; i < nrAnimale; ++i) animale[i] = temporar[i];
        animale[nrAnimale] = a;
        nrAnimale++;
        if (temporar != nullptr) { delete[] temporar; temporar = nullptr; }
    }
    static void stergereAnimalDupaID(int id) {
        if (animale == nullptr) return;
        int poz = -1;
        for (int i = 0; i < nrAnimale; ++i)
            if (animale[i].getID() == id) { poz = i; break; }
        if (poz == -1) { cout << "Animalul cu ID-ul " << id << " nu a fost gasit.\n"; return; }
        if (nrAnimale == 1) {
            delete[] animale;
            animale = nullptr;
            nrAnimale = 0;
            return;
        }
        Animal* temporar = new Animal[nrAnimale - 1];
        int k = 0;
        for (int i = 0; i < nrAnimale; ++i)
            if (i != poz) temporar[k++] = animale[i];
        delete[] animale;
        animale = new Animal[nrAnimale - 1];
        for (int i = 0; i < nrAnimale - 1; ++i) animale[i] = temporar[i];
        nrAnimale--;
        delete[] temporar;
        cout << "Animalul a fost sters cu succes.\n";
    }
    static void golesteListaAnimale() {
        if (animale != nullptr) { delete[] animale; animale = nullptr; }
        nrAnimale = 0;
    }
    static Animal* getAnimale() { return animale; }
    static int getNrAnimale() { return nrAnimale; }

    // --- metoda virtuala (suprascrisa) ---
    virtual void afiseazaDetalii() const {
        cout << "Nume animal: " << nume << ", ID: " << ID << "\n";
    }
};

inline int Animal::nrAnimale = 0;
inline Animal* Animal::animale = nullptr;

// NIVELUL 2 DIN MOSTENIRE
class Mamifer : public Animal {
protected:
    bool areBlana;
public:
    // -- Constructor Mamifer --
    Mamifer(const string& nume, const int ID, const vector<int>& istoric, const int nrProc, const char gen, bool areBlana)
        : Animal(nume, ID, istoric, nrProc, gen), areBlana(areBlana) {
        cout << "Mamifer() a fost apelat.\n";
    }

    // -- Destructor Mamifer --
    virtual ~Mamifer() noexcept {
        cout << "~Mamifer() a fost apelat.\n";
    }

    bool getAreBlana() const { return areBlana; }

    // -- Suprascrie metoda afisareDetalii --
    void afiseazaDetalii() const override {
        Animal::afiseazaDetalii();
        cout << "Are blana: " << (areBlana ? "Da" : "Nu") << "\n";
    }
};

// NIVELUL 3.1 DIN MOSTENIRE
class Caine : public Mamifer {
private:
    string rasa;
public:
    // -- Constructorul --
    Caine(const string& nume, const int ID, const vector<int>& istoric, const int nrProc, const char gen, bool areBlana, const string& rasa)
        : Mamifer(nume, ID, istoric, nrProc, gen, areBlana), rasa(rasa) {
        cout << "Caine() a fost apelat.\n";
    }

    // -- Destructorul --
    ~Caine() noexcept override {
        cout << "~Caine() a fost apelat.\n";
    }

    const string& getRasa() const { return rasa; }

    void afiseazaDetalii() const override {
        Mamifer::afiseazaDetalii();
        cout << "Rasa caine: " << rasa << "\n";
    }
};

// NIVELUL 3.2 DIN MOSTENIRE
class Pisica : public Mamifer {
private:
    string rasa;
public:
    // -- Constructorul --
    Pisica(const string& nume, const int ID, const vector<int>& istoric, const int nrProc, const char gen, bool areBlana, const string& rasa)
        : Mamifer(nume, ID, istoric, nrProc, gen, areBlana), rasa(rasa) {
        cout << "Pisica() a fost apelat.\n";
    }

    // -- Destructorul --
    ~Pisica() noexcept override {
        cout << "~Pisica() a fost apelat.\n";
    }

    const string& getRasa() const { return rasa; }

    // Suprascrie metoda afiseazaDetalii
    void afiseazaDetalii() const override {
        Mamifer::afiseazaDetalii();
        cout << "Rasa pisica: " << rasa << "\n";
    }
};
#endif //PROIECT_POO_ANIMALE_H
