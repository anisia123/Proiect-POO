#ifndef PROIECT_POO_IOBJECT_H
#define PROIECT_POO_IOBJECT_H

#include <iostream>
#include <string>
#include <sstream>

// CERINTA 5: Interfata IObject - identificatori unici si toString polimorf

class IObject {
private:
    static int contor_; // Contor static pentru generare ID-uri unice
    int id_;            // ID unic pentru fiecare obiect

protected:
    IObject() : id_(++contor_) {}

public:
    virtual ~IObject() noexcept = default;

    // Getter pentru ID unic
    int getId() const noexcept { return id_; }

    // Getter pentru ID-ul urmator care va fi alocat
    static int getNextId() noexcept { return contor_ + 1; }

    // Reinitializare contor (pentru teste)
    static void resetContor() noexcept { contor_ = 0; }

    // Metoda virtuala pura - toString polimorf
    virtual std::string toString() const = 0;

    // Operator << apelat polimorfic (friend)
    friend std::ostream& operator<<(std::ostream& os, const IObject& obj) {
        os << obj.toString();
        return os;
    }

    // Operator == pe baza ID-ului
    bool operator==(const IObject& other) const noexcept {
        return this->id_ == other.id_;
    }

    bool operator!=(const IObject& other) const noexcept {
        return !(*this == other);
    }
};

inline int IObject::contor_ = 0;

#endif // PROIECT_POO_IOBJECT_H
