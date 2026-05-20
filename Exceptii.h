#ifndef PROIECT_POO_EXCEPTII_H
#define PROIECT_POO_EXCEPTII_H

#include <stdexcept>
#include <string>

// Exceptii custom pentru clinica veterinara
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

#endif // PROIECT_POO_EXCEPTII_H

