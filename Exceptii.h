#ifndef PROIECT_POO_EXCEPTII_H
#define PROIECT_POO_EXCEPTII_H

#include <stdexcept>
#include <string>
#include <sstream>

// Exceptii custom pentru clinica veterinara - CERINTA 1: Ierarhie proprie minimum 3 clase
class ExceptieClinica : public std::runtime_error {
protected:
    int id_; // id-ul asociat erorii, daca exista
    std::string msg_;
public:
    explicit ExceptieClinica(const std::string &msg, int id = -1)
        : std::runtime_error(msg), id_(id), msg_(msg) {}

    int getID() const noexcept { return id_; }

    const char* what() const noexcept override {
        return msg_.c_str();
    }
};

class ExceptieAnimalInvalid : public ExceptieClinica {
public:
    ExceptieAnimalInvalid(const std::string &msg, int id = -1)
        : ExceptieClinica(msg, id) {}
};

class ExceptieProcedura : public ExceptieClinica {
public:
    ExceptieProcedura(const std::string &msg, int id = -1)
        : ExceptieClinica(msg, id) {}
};

// CERINTA 1: A 3-a clasa custom pentru erori de resurse (noi)
class ExceptieResursa : public ExceptieClinica {
private:
    int resurseDisponibile;
public:
    ExceptieResursa(const std::string &msg, int id = -1, int resurse = 0)
        : ExceptieClinica(msg, id), resurseDisponibile(resurse) {
        // Mesaj imbunatatit cu info resurse
        std::ostringstream oss;
        oss << msg << " [Resurse disponibile: " << resurse << "]";
        msg_ = oss.str();
    }

    int getResurseDisponibile() const noexcept { return resurseDisponibile; }
};

#endif // PROIECT_POO_EXCEPTII_H
