#ifndef PROIECT_POO_DATABASE_H
#define PROIECT_POO_DATABASE_H

#include <iostream>
#include <string>
#include "Animale.h"
#include "Medici.h"
#include "Procedura.h"
using namespace std;

// Clasa mock Database - implementare simplificata fara SQLite
class Database {
    string databaseName;
    bool connected;

public:
    // Constructor
    Database(const string& dbName) : databaseName(dbName), connected(false) {
        cout << "[Database] Constructor apelat pentru: " << databaseName << "\n";
    }

    // Destructor
    ~Database() {
        cout << "[Database] Destructor apelat\n";
    }

    // Conectare la baza de date
    bool connect() {
        cout << "[Database] Incercare conexiune la: " << databaseName << "\n";
        connected = true;
        return true;
    }

    // Initializare tabele
    void initializeazaTabele() {
        if (!connected) {
            cout << "[Database] Nu exista conexiune la baza de date.\n";
            return;
        }
        cout << "[Database] Tabele initializate (sau deja existente).\n";
    }

    // Verifica daca baza de date are date
    bool areDate() {
        cout << "[Database] Verificare date in baza de date...\n";
        return false; // Intoarce false daca DB este goala
    }

    // Insereaza date initiale in baza de date
    void inserateDateInitiale() {
        if (!connected) {
            cout << "[Database] Nu exista conexiune la baza de date.\n";
            return;
        }
        cout << "[Database] Date initiale inserate.\n";
    }

    // Incarca toate datele din baza de date
    void incarcaToate() {
        if (!connected) {
            cout << "[Database] Nu exista conexiune la baza de date.\n";
            return;
        }
        cout << "[Database] Date incarcate din baza de date.\n";
    }

    // Salveaza un animal in baza de date
    void salveazaAnimal(const Animal& a) {
        if (!connected) {
            cout << "[Database] Nu exista conexiune la baza de date.\n";
            return;
        }
        cout << "[Database] Animal salvat: ID=" << a.getID() << "\n";
    }

    // Salveaza un medic in baza de date
    void salveazaMedic(const Medici& m) {
        if (!connected) {
            cout << "[Database] Nu exista conexiune la baza de date.\n";
            return;
        }
        cout << "[Database] Medic salvat: ID=" << m.getID() << "\n";
    }

    // Sterge un animal din baza de date
    void stergeAnimalDB(int id) {
        if (!connected) {
            cout << "[Database] Nu exista conexiune la baza de date.\n";
            return;
        }
        cout << "[Database] Animal sters din DB: ID=" << id << "\n";
    }

    // Getter pentru starea conexiunii
    bool isConnected() const { return connected; }

    // Getter pentru numele bazei de date
    const string& getDatabaseName() const { return databaseName; }
};

#endif //PROIECT_POO_DATABASE_H
