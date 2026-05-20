#ifndef PROIECT_POO_MEDICI_H
#define PROIECT_POO_MEDICI_H
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <list>
#include <algorithm>
#include "Procedura.h"
#include "Animale.h"
using namespace std;

class Angajat {
public:
    virtual ~Angajat() noexcept {
        cout << "~Angajat() a fost apelat. \n";
    }

    void afiseazaTipAngajat() const {
        cout << "Acesta este un angajat al clinicii veterinare.\n";
    }
    virtual void afiseazaAtributii() const = 0;
    virtual float getSalariuLunar() const = 0;
};

class Medici : public Angajat {
    string specializare;
    int IDMedic;
    float salariu;
    vector<int> proceduriFacute; // ID-urile procedurilor facute
    int nrProcFacute;

    static std::list<Medici> medici;

public:
    // --- constructor fara param ---
    Medici() : specializare("Not def") {
        IDMedic = rand() % (1000 - 100);
        nrProcFacute = 0;
        proceduriFacute = vector<int>();
        salariu = 0.0;
    }

    // --- constructor cu toti param ---
    Medici(const string& specializare, const int IDMedic, const float salariu,
           const vector<int>& proceduriFacute, const int nrProceduri)
        : IDMedic(IDMedic), salariu(salariu), nrProcFacute(nrProceduri),
          specializare(specializare) {
        if (nrProceduri > 0 && !proceduriFacute.empty()) {
            this->proceduriFacute = vector<int>(proceduriFacute);
            for (int i = 0; i < nrProceduri; ++i)
                this->proceduriFacute[i] = proceduriFacute[i];
        } else {
            this->proceduriFacute = vector<int>();
            this->nrProcFacute = 0;
        }
    }

    // --- constructor cu ID generat random, salariu fix ---
    Medici(const string& specializare, const float salariu,
           const vector<int>& proceduriFacute, const int nrProceduri)
        : salariu(salariu), nrProcFacute(nrProceduri), specializare(specializare) {
        IDMedic = rand() % (1000 - 100);
        if (nrProceduri > 0 && !proceduriFacute.empty()) {
            this->proceduriFacute = vector<int>(proceduriFacute);
            for (int i = 0; i < nrProceduri; ++i)
                this->proceduriFacute[i] = proceduriFacute[i];
        } else {
            this->proceduriFacute = vector<int>();
            this->nrProcFacute = 0;
        }
        adaugareMedic(*this);
    }

    // --- constructor cu ID random si salariu calculat ---
    Medici(const string& specializare, const vector<int>& proceduriFacute, const int nrProceduri)
        : nrProcFacute(nrProceduri), specializare(specializare) {
        IDMedic = rand() % (1000 - 100);
        if (nrProceduri > 0 && !proceduriFacute.empty()) {
            this->proceduriFacute = vector<int>(proceduriFacute);
            for (int i = 0; i < nrProceduri; ++i)
                this->proceduriFacute[i] = proceduriFacute[i];
        } else {
            this->proceduriFacute = vector<int>();
            this->nrProcFacute = 0;
        }
        salariu = calculSalariu();
        adaugareMedic(*this);
    }

    // --- constructor de copiere ---
    Medici(const Medici& mCpy) : IDMedic(mCpy.IDMedic), salariu(mCpy.salariu),
                                   nrProcFacute(mCpy.nrProcFacute), specializare(mCpy.specializare) {
        if (mCpy.nrProcFacute > 0 && mCpy.proceduriFacute.size() > 0) {
            this->proceduriFacute = vector<int>(mCpy.proceduriFacute);
        } else {
            this->proceduriFacute = vector<int>();
            this->nrProcFacute = 0;
        }
    }

    // --- getters ---
    const string& getSpecializare() const { return specializare; }
    int getID() const { return IDMedic; }
    float getSalariu() const { return salariu; }
    const vector<int>& getProceduriFacute() const { return proceduriFacute; }
    int getNrProcFacute() const { return nrProcFacute; }

    // --- setters ---
    void setSpecializare(const string &specializareNoua) {
        this->specializare = specializareNoua;
    }
    void setIdMedic(const int idNou) { IDMedic = idNou; }
    void setSalariu(const float salariuNou) { salariu = salariuNou; }

    // --- Destructor ---
    ~Medici() noexcept override {
        cout << "~Medici() a fost apelat.\n";
    }

    // --- operator >> ---
    friend istream &operator>>(istream &is, Medici& m) {
        string cpySpecializare;
        cout << "Specializarea medicului : ";
        is >> ws;
        getline(is, cpySpecializare);
        m.specializare = cpySpecializare;
        m.IDMedic = rand() % (1000 - 100);
        cout << "Cate proceduri a facut : ";
        is >> m.nrProcFacute;
        if (m.nrProcFacute > 0) {
            m.proceduriFacute = vector<int>(m.nrProcFacute);
            cout << "Care sunt acestea (ID-urile lor) : ";
            for (int i = 0; i < m.nrProcFacute; ++i) is >> m.proceduriFacute[i];
        }
        m.salariu = m.calculSalariu();
        adaugareMedic(m);
        return is;
    }

    // --- operator << ---
    friend ostream &operator<<(ostream &os, const Medici &m) {
        os << "Medicul salvat in sistem cu ID-ul " << m.IDMedic
           << ", specializat in " << m.specializare
           << " a facut " << m.nrProcFacute << " proceduri";
        if (m.nrProcFacute > 0 && m.proceduriFacute.size() > 0) {
            os << ", iar acestea sunt: ";
            for (int i = 0; i < m.nrProcFacute; ++i) os << m.proceduriFacute[i] << " ";
        }
        os << ". Salariul lunar al acestuia este de " << m.salariu << " LEI.\n";
        return os;
    }

    // --- operator + (adauga procedura) ---
    friend Medici operator+(const Medici& m, int idProc) {
        vector<int> cpyProceduri = m.proceduriFacute;
        cpyProceduri.push_back(idProc);
        Medici m1(m.specializare, m.IDMedic, m.salariu, cpyProceduri, m.nrProcFacute + 1);
        return m1;
    }
    friend Medici operator+(int idProc, const Medici& m) { return m + idProc; }

    // --- operator - (scade taxa din salariu) ---
    friend Medici operator-(const Medici& m, double taxa) {
        float cpySalariu = m.salariu;
        if (cpySalariu - taxa >= 0) cpySalariu -= (float)taxa;
        else cpySalariu = 0;
        Medici m1(m.specializare, m.IDMedic, cpySalariu, m.proceduriFacute, m.nrProcFacute);
        return m1;
    }

    // --- operator = ---
    Medici& operator=(const Medici& m) {
        if (this == &m) return *this;
        IDMedic = m.IDMedic;
        salariu = m.salariu;
        nrProcFacute = m.nrProcFacute;
        specializare = m.specializare;
        if (m.nrProcFacute > 0 && !m.proceduriFacute.empty()) {
            proceduriFacute = m.proceduriFacute;
        } else { proceduriFacute = vector<int>(); }
        return *this;
    }

    // --- operator > ---
    bool operator>(const Medici& m) const { return salariu > m.salariu; }
    // --- operator == ---
    bool operator==(const Medici& m) const { return salariu == m.salariu; }
    // --- operator [] ---
    const int& operator[](int i) const { return proceduriFacute[i]; }
    // --- operator ++ prefixat (bonus 1200 LEI) ---
    Medici& operator++() {
        this->salariu += 1200.0f;
        return *this;
    }
    // --- operator ++ postfixat ---
    Medici operator++(int) {
        Medici cpy = *this;
        this->salariu += 1200.0f;
        return cpy;
    }

    // --- functii statice ---
    static void actualizareSalariu(Animal& a) {
        const vector<int>& vectorProcAnimal = a.getIstoric();
        if (!medici.empty() && !vectorProcAnimal.empty()) {
            for (int i = 0; i < a.getNrProc(); ++i) {
                for (int j = 0; j < Procedura::getNrProceduriCreate(); ++j) {
                    const Procedura& proc = Procedura::getProceduraByIndex(j);
                    if (vectorProcAnimal[i] == proc.getIDProc()) {
                        for (auto it = medici.begin(); it != medici.end(); ++it) {
                            if (it->getSpecializare() == proc.getSpecializare()) {
                                it->setSalariu(it->getSalariu() + (float)proc.getPret());
                            }
                        }
                    }
                }
            }
        }
    }

    float calculSalariu() const {
        float salariuTemp = 0.0;
        if (proceduriFacute.empty() || nrProcFacute == 0) return 0.0;
        for (int i = 0; i < Procedura::getNrProceduriCreate(); ++i) {
            const Procedura& proc = Procedura::getProceduraByIndex(i);
            for (int j = 0; j < nrProcFacute; ++j) {
                if (proceduriFacute[j] == proc.getIDProc())
                    salariuTemp += (float)proc.getPret();
            }
        }
        return salariuTemp;
    }

    static void adaugareMedic(const Medici& m) {
        medici.push_back(m);
    }

    static void stergeMedicDupaID(int id) {
        if (medici.empty()) return;
        auto it = std::find_if(medici.begin(), medici.end(), [id](const Medici& m) { return m.getID() == id; });
        if (it == medici.end()) { cout << "Medicul cu ID-ul " << id << " nu a fost gasit.\n"; return; }
        medici.erase(it);
        cout << "Medicul a fost sters cu succes.\n";
    }

    static void golesteListaMedici() {
        medici.clear();
    }
    static const std::list<Medici>& getMedici() { return medici; }
    static int getNrMedici() { return static_cast<int>(medici.size()); }
    // Acces compatibil index-based
    static Medici& getMedicByIndex(int index) {
        if (index < 0 || index >= (int)medici.size()) throw std::out_of_range("Index medic invalid");
        auto it = medici.begin();
        std::advance(it, index);
        return *it;
    }

    // --- Algoritmi din <algorithm> folosind lambda-uri (cerinta) ---
    // 1) count_if - numara medicii cu salariu > threshold
    static int countMediciWithSalaryGreater(float threshold) {
        return (int)std::count_if(medici.begin(), medici.end(), [threshold](const Medici& m) {
            return m.getSalariu() > threshold;
        });
    }

    // 2) any_of - verifica daca exista medic cu o anumita specializare
    static bool anyMedicWithSpecializare(const string& spec) {
        return std::any_of(medici.begin(), medici.end(), [&spec](const Medici& m) {
            return m.getSpecializare() == spec;
        });
    }

    // 3) for_each - acorda un bonus tuturor medicilor cu o specializare data
    static void acordaBonusSpecializare(const string& spec, float bonus) {
        std::for_each(medici.begin(), medici.end(), [&spec, bonus](Medici& m) {
            if (m.getSpecializare() == spec) m.setSalariu(m.getSalariu() + bonus);
        });
    }

    // 4) copy_if - obtine o lista (vector) cu medicii ce au o anumita specializare
    static std::vector<Medici> getMediciBySpecializare(const string& spec) {
        std::vector<Medici> rez;
        std::copy_if(medici.begin(), medici.end(), std::back_inserter(rez), [&spec](const Medici& m) {
            return m.getSpecializare() == spec;
        });
        return rez;
    }

    // 5) remove_if + erase - sterge toti medicii cu salariul <= 0
    static void removeMediciWithZeroSalary() {
        auto newEnd = std::remove_if(medici.begin(), medici.end(), [](const Medici& m) {
            return m.getSalariu() <= 0.0f;
        });
        medici.erase(newEnd, medici.end());
    }

    // 6) transform + sort - obtine vectorul cu salariile si il sorteaza descrescator
    static std::vector<float> getSalariesSortedDesc() {
        std::vector<float> salaries;
        salaries.reserve(medici.size());
        std::transform(medici.begin(), medici.end(), std::back_inserter(salaries), [](const Medici& m) {
            return m.getSalariu();
        });
        std::sort(salaries.begin(), salaries.end(), [](float a, float b) { return a > b; });
        return salaries;
    }

    void afiseazaAtributii() const override {
        cout << "Atributii: Medicul cu specializarea " << specializare
             << " diagnosticheaza animalele si efectueaza proceduri medicale.\n";
    }

    float getSalariuLunar() const override {
        return salariu;
    }
};

inline std::list<Medici> Medici::medici = std::list<Medici>();

class Asistent : public Angajat {
    float salariu;
public:
    // -- constructor --
    Asistent(float salariu) : salariu(salariu) {}

    // -- destructor --
    ~Asistent() noexcept override {
        cout << "~Asistent() a fost apelat. \n";
    }

    void afiseazaAtributii() const override {
        cout << "Asistentul pregateste sala de operatie si asista medicul veterinar!\n";
    }

    float getSalariuLunar() const override {
        return salariu;
    }
};
#endif //PROIECT_POO_MEDICI_H
