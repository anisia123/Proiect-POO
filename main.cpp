#include <iostream>
#include <cstring>
#include "Procedura.h"
#include "Animale.h"
#include "Clinica.h"
#include "Medici.h"
#include "Proprietari.h"
#include "Database.h"
using namespace std;

void demonstreazaPolimorfism() {
    cout << "\n--- DEMONSTRATIE POLIMORFISM (CERINTA 4) ---\n";

    int nrAngajati = 2;
    Angajat** echipa = new Angajat*[nrAngajati];

    int proceduri[] = {101};
    echipa[0] = new Medici("Chirurgie", 3500.5f, proceduri, 1);
    echipa[1] = new Asistent(2500.0f);

    for(int i = 0; i < nrAngajati; i++) {
        cout << "\nAngajatul " << i + 1 << ":\n";
        echipa[i]->afiseazaTipAngajat();
        echipa[i]->afiseazaAtributii();
        cout << "Salariu: " << echipa[i]->getSalariuLunar() << " LEI\n";
    }

    for(int i = 0; i < nrAngajati; i++) {
        delete echipa[i];
    }
    delete[] echipa;
}

void demonstreazaDowncasting() {
    cout << "\n--- DEMONSTRATIE DOWNCASTING (CERINTA 6) ---\n";

    int proceduri[] = {101};
    Angajat* angajat1 = new Medici("Cardiologie", 4500.0f, proceduri, 1);
    Angajat* angajat2 = new Asistent(2800.0f);

    // Folosim dynamic_cast deoarece verifica la runtime daca obiectul pointat
    // este cu adevarat de tipul in care incercam sa il convertim. Daca foloseam
    // static_cast pe un obiect care nu e Medic, compilatorul ar fi permis cast-ul
    // orbeste, ducand la Undefined Behavior in momentul apelului functiilor specifice.

    Medici* medicValid = dynamic_cast<Medici*>(angajat1);
    if (medicValid != nullptr) {
        cout << "Succes!:) Primul angajat este Medic! Specializarea lui: "
             << medicValid->getSpecializare() << "\n";
    } else {
        cout << "Esec!:( Primul angajat nu este medic.\n";
    }

    Medici* medicInvalid = dynamic_cast<Medici*>(angajat2);
    if (medicInvalid != nullptr) {
        cout << "Succes!:) Al doilea angajat este Medic! Specializarea lui: "
             << medicInvalid->getSpecializare() << "\n";
    } else {
        cout << "Esec!:( Al doilea angajat NU este medic (dynamic_cast a returnat nullptr).\n";
    }

    delete angajat1;
    delete angajat2;
}

void demonstreazaOperatori() {
    cout << "\n===== DEMO OPERATORI =====\n";

    // ---- PROCEDURA ----
    cout << "\n[Procedura]\n";
    Procedura p1("Chirurgie", 101, 135.0, 45, 3);
    Procedura p2("Dermatologie", 102, 90.0, 30, 3);

    Procedura p3 = p1 + 15;
    cout << "p1 + 15 minute: "; cout << p3;

    Procedura p4 = 10 + p2;
    cout << "10 + p2: "; cout << p4;

    Procedura p5 = p1 - 5;
    cout << "p1 - 5 minute: "; cout << p5;

    ++p1;
    cout << "++p1 (durata+1): "; cout << p1;

    Procedura p6 = p2++;
    cout << "p2++ (returnat inainte): "; cout << p6;
    cout << "p2 dupa postfix++: "; cout << p2;

    cout << "p1 == p2 ? " << (p1 == p2 ? "DA" : "NU") << "\n";
    cout << "p1 > p2 (pret) ? " << (p1 > p2 ? "DA" : "NU") << "\n";
    cout << "Primul caracter din specializarea p1: " << p1[0] << "\n";

    // ---- ANIMAL ----
    cout << "\n[Animal]\n";
    int procA[] = {101, 102};
    Animal a1("Bobita", 201, procA, 2, 'F');
    Animal a2("Rex", 202, procA, 1, 'M');

    Animal a3 = a1 + 103;
    cout << "a1 + proc103: "; cout << a3;

    Animal a4 = 104 + a2;
    cout << "104 + a2: "; cout << a4;

    Animal a5 = a3 - 101;
    cout << "a3 - proc101: "; cout << a5;

    ++a1;
    cout << "++a1 (nrProc+1): nrProc=" << a1.getNrProc() << "\n";

    Animal a6 = a2++;
    cout << "a2++ (returnat cu nrProc=" << a6.getNrProc() << ")\n";

    cout << "a1 < a2 (nrProc) ? " << (a1 < a2 ? "DA" : "NU") << "\n";
    cout << "a1 == a2 ? " << (a1 == a2 ? "DA" : "NU") << "\n";

    if (a3.getNrProc() > 0)
        cout << "a3[0] (primul ID procedura): " << a3[0] << "\n";

    Animal aCopy;
    aCopy = a1;
    cout << "aCopy = a1: " << aCopy.getNume() << " ID=" << aCopy.getID() << "\n";

    // ---- MEDICI ----
    cout << "\n[Medici]\n";
    int procM[] = {101};
    Medici m1("Chirurgie", 301, 135.0f, procM, 1);
    Medici m2("Dermatologie", 302, 90.0f, procM, 1);

    Medici m3 = m1 + 102;
    cout << "m1 + proc102: "; cout << m3;

    Medici m4 = m1 - 50.0;
    cout << "m1 - 50 LEI: salariu=" << m4.getSalariu() << "\n";

    ++m1;
    cout << "++m1 bonus: salariu=" << m1.getSalariu() << "\n";

    Medici m5 = m2++;
    cout << "m2++ (salariu returnat=" << m5.getSalariu()
         << ", salariu curent m2=" << m2.getSalariu() << ")\n";

    cout << "m1 > m2 (salariu) ? " << (m1 > m2 ? "DA" : "NU") << "\n";
    cout << "m1 == m2 ? " << (m1 == m2 ? "DA" : "NU") << "\n";

    // ---- PROPRIETAR ----
    cout << "\n[Proprietar]\n";
    Animal aPr1, aPr2;
    aPr1.setID(201);
    aPr2.setID(202);
    Proprietar pr1("Ion Popescu", aPr1, 200.0, false);
    Proprietar pr2("Maria Ionescu", aPr2, 150.0, true);

    Proprietar pr3 = pr1 + 50.0;
    cout << "pr1 + 50 LEI: suma=" << pr3.getPlata() << "\n";

    Proprietar pr4 = 30.0 + pr2;
    cout << "30 + pr2: suma=" << pr4.getPlata() << "\n";

    Proprietar pr5 = pr1 - 20.0;
    cout << "pr1 - 20 LEI: suma=" << pr5.getPlata() << "\n";

    Proprietar pr6 = pr1++;
    cout << "pr1++ (suma inainte=" << pr6.getPlata()
         << ", suma curenta=" << pr1.getPlata() << ")\n";

    cout << "pr1 > pr2 (suma) ? " << (pr1 > pr2 ? "DA" : "NU") << "\n";
    cout << "pr1 == pr2 ? " << (pr1 == pr2 ? "DA" : "NU") << "\n";
    cout << "pr1[0] (primul char din nume): " << pr1[0] << "\n";

    // ---- CLINICA ----
    cout << "\n[Clinica]\n";
    Clinica c1("Vet Pro", "Str. Eminescu 5, Bucuresti", 4, 80.0f, true);
    Clinica c2("Vet Mini", "Str. Lalelelor 2", 2, 60.0f, true);

    Clinica c3 = c1 + 2;
    cout << "c1 + 2 cabinete: nrCabinete=" << c3.getNrCabinete() << "\n";

    Clinica c4 = 3 + c2;
    cout << "3 + c2: nrCabinete=" << c4.getNrCabinete() << "\n";

    Clinica c5 = c1 - 1;
    cout << "c1 - 1 cabinet: nrCabinete=" << c5.getNrCabinete() << "\n";

    cout << "c1 inainte ++: " << (c1.getDeschisa() ? "DESCHISA" : "INCHISA") << "\n";
    ++c1;
    cout << "c1 dupa ++: " << (c1.getDeschisa() ? "DESCHISA" : "INCHISA") << "\n";

    cout << "c2 < c1 (nrCabinete) ? " << (c2 < c1 ? "DA" : "NU") << "\n";
    cout << "c1 == c2 ? " << (c1 == c2 ? "DA" : "NU") << "\n";
    cout << "c1[0] (primul char din adresa): " << c1[0] << "\n";

    cout << "===== SFARSIT DEMO =====\n\n";
}

void meniuOptiuni() {
    cout << "\n===== CLINICA VETERINARA - MENIU =====\n";
    cout << "--- CREATE ---\n";
    cout << "1. Adauga Procedura\n";
    cout << "2. Adauga Medic\n";
    cout << "3. Adauga Animal si Proprietar\n";
    cout << "--- READ ---\n";
    cout << "4. Afiseaza toti medicii\n";
    cout << "5. Afiseaza toate animalele\n";
    cout << "6. Afiseaza toate procedurile\n";
    cout << "7. Raport clinica\n";
    cout << "--- UPDATE ---\n";
    cout << "8. Adauga o procedura unui animal\n";
    cout << "9. Elimina o procedura de la un animal\n";
    cout << "10. Ofera bonus unui medic (1200 LEI)\n";
    cout << "11. Actualizeaza durata unei proceduri (+/- minute)\n";
    cout << "--- DELETE ---\n";
    cout << "12. Sterge animal dupa ID\n";
    cout << "13. Sterge medic dupa ID\n";
    cout << "14. Sterge procedura dupa ID\n";
    cout << "--- ALTELE ---\n";
    cout << "15. Demo operatori\n";
    cout << "16. Goleste baza de date (memorie)\n";
    cout << "0. Iesire\n";
    cout << "Alege o optiune: ";
}

int main() {
    srand((unsigned int)time(nullptr));

    // ===================== BAZA DE DATE =====================
    Database db("clinica.db");

    if (db.connect()) {
        db.initializeazaTabele();

        if (!db.areDate()) {
            cout << "[DB] Baza de date este goala. Se insereaza date initiale...\n";
            db.inserateDateInitiale();
        }

        cout << "[DB] Se incarca datele din baza de date...\n";
        db.incarcaToate();
    } else {
        cout << "[ATENTIE] Functionare fara baza de date (SQLite indisponibil).\n";
    }
    // =========================================================

    Clinica clinica("Vet Pro Bucuresti", "Str. Eminescu 5", 5, 80.0f, true);

    int optiune = 10;
    do {
        meniuOptiuni();
        cin >> optiune;

        switch (optiune) {
            // ===== CREATE =====
            case 1: {
                Procedura p;
                cin >> p;
                cout << "Procedura adaugata: " << p;
                break;
            }
            case 2: {
                Medici m;
                cin >> m;
                cout << "Medic adaugat: " << m;
                for (int i = 0; i < Animal::getNrAnimale(); ++i)
                    Medici::actualizareSalariu(Animal::getAnimale()[i]);
                break;
            }
            case 3: {
                Animal a;
                cin >> a;
                cout << "Animal adaugat: " << a;

                char numeProprietar[256];
                bool urgenta;
                cout << "Numele proprietarului: ";
                cin >> ws; cin.getline(numeProprietar, 256);
                cout << "Este o urgenta? (1=DA, 0=NU): ";
                cin >> urgenta;

                Proprietar pr(numeProprietar, a, urgenta);
                cout << pr;

                Medici::actualizareSalariu(a);
                Clinica::incrementPacienti();
                db.salveazaAnimal(a);
                break;
            }
            // ===== READ =====
            case 4: {
                if (Medici::getNrMedici() == 0) {
                    cout << "Nu exista medici inregistrati.\n"; break;
                }
                for (int i = 0; i < Medici::getNrMedici(); ++i)
                    cout << Medici::getMedicByIndex(i);
                break;
            }
            case 5: {
                if (Animal::getNrAnimale() == 0) {
                    cout << "Nu exista animale inregistrate.\n"; break;
                }
                for (int i = 0; i < Animal::getNrAnimale(); ++i)
                    cout << Animal::getAnimale()[i];
                break;
            }
            case 6: {
                if (Procedura::getNrProceduriCreate() == 0) {
                    cout << "Nu exista proceduri inregistrate.\n"; break;
                }
                for (int i = 0; i < Procedura::getNrProceduriCreate(); ++i)
                    cout << Procedura::getProceduraByIndex(i);
                break;
            }
            case 7: {
                clinica.afiseazaRaport();
                break;
            }
            // ===== UPDATE =====
            case 8: {
                cout << "ID-ul Animalului: ";
                int idAnimal, idProc;
                cin >> idAnimal;
                cout << "ID-ul procedurii de adaugat: ";
                cin >> idProc;
                bool gasit = false;
                for (int i = 0; i < Animal::getNrAnimale(); ++i) {
                    if (Animal::getAnimale()[i].getID() == idAnimal) {
                        Animal::getAnimale()[i] = Animal::getAnimale()[i] + idProc;
                        cout << "Procedura adaugata. Animal actualizat:\n" << Animal::getAnimale()[i];
                        Medici::actualizareSalariu(Animal::getAnimale()[i]);
                        db.salveazaAnimal(Animal::getAnimale()[i]);
                        gasit = true;
                    }
                }
                if (!gasit) cout << "Animalul cu ID-ul " << idAnimal << " nu a fost gasit.\n";
                break;
            }
            case 9: {
                cout << "ID-ul Animalului: ";
                int idAnimal, idProc;
                cin >> idAnimal;
                cout << "ID-ul procedurii de eliminat: ";
                cin >> idProc;
                bool gasit = false;
                for (int i = 0; i < Animal::getNrAnimale(); ++i) {
                    if (Animal::getAnimale()[i].getID() == idAnimal) {
                        Animal::getAnimale()[i] = Animal::getAnimale()[i] - idProc;
                        cout << "Procedura eliminata. Animal actualizat:\n" << Animal::getAnimale()[i];
                        db.salveazaAnimal(Animal::getAnimale()[i]);
                        gasit = true;
                    }
                }
                if (!gasit) cout << "Animalul cu ID-ul " << idAnimal << " nu a fost gasit.\n";
                break;
            }
            case 10: {
                cout << "ID-ul medicului caruia i se da bonusul: ";
                int idMedic;
                cin >> idMedic;
                bool gasit = false;
                for (int i = 0; i < Medici::getNrMedici(); ++i) {
                    Medici& m = Medici::getMedicByIndex(i);
                    if (m.getID() == idMedic) {
                        float salariuVechi = m.getSalariu();
                        ++m;
                        cout << "Bonus acordat! Salariu: " << salariuVechi
                             << " -> " << m.getSalariu() << " LEI\n";
                        db.salveazaMedic(m);
                        gasit = true;
                    }
                }
                if (!gasit) cout << "Medicul cu ID-ul " << idMedic << " nu a fost gasit.\n";
                break;
            }
            case 11: {
                cout << "ID-ul procedurii de actualizat: ";
                int idProc, minute;
                cin >> idProc;
                cout << "Minute de adaugat (+) sau scazut (-): ";
                cin >> minute;
                bool gasit = false;
                for (int i = 0; i < Procedura::getNrProceduriCreate(); ++i) {
                    Procedura& proc = Procedura::getProceduraByIndex(i);
                    if (proc.getIDProc() == idProc) {
                        if (minute > 0) {
                            Procedura updated = proc + minute;
                            Procedura::stergereProceduraDupaID(proc.getIDProc());
                            Procedura::adaugareProcedura(updated);
                            cout << "Procedura actualizata:\n" << updated;
                        } else {
                            Procedura updated = proc - (-minute);
                            Procedura::stergereProceduraDupaID(proc.getIDProc());
                            Procedura::adaugareProcedura(updated);
                            cout << "Procedura actualizata:\n" << updated;
                        }
                        gasit = true;
                    }
                }
                if (!gasit) cout << "Procedura cu ID-ul " << idProc << " nu a fost gasita.\n";
                break;
            }
            // ===== DELETE =====
            case 12: {
                cout << "ID-ul animalului de sters: ";
                int id; cin >> id;
                Animal::stergereAnimalDupaID(id);
                db.stergeAnimalDB(id);
                break;
            }
            case 13: {
                cout << "ID-ul medicului de sters: ";
                int id; cin >> id;
                Medici::stergeMedicDupaID(id);
                break;
            }
            case 14: {
                cout << "ID-ul procedurii de sters: ";
                int id; cin >> id;
                Procedura::stergereProceduraDupaID(id);
                break;
            }
            // ===== ALTELE =====
            case 15: {
                demonstreazaOperatori();
                break;
            }
            case 16: {
                Animal::golesteListaAnimale();
                Medici::golesteListaMedici();
                Procedura::golesteListaProceduri();
                cout << "Memoria a fost resetata (DB-ul SQLite ramane intact).\n";
                break;
            }
            case 0:
                cout << "La revedere!\n";
                break;
            default:
                cout << "Optiune invalida.\n";
        }
    } while (optiune != 0);

    return 0;
}
