// Recurso.h

#ifndef RECURSO_HPP
#define RECURSO_HPP

#include <string>

class Recurso {
private:
    int id;
    std::string nome;
    int pid_ocupante; // PID do processo que atualmente ocupa este recurso. 0 se livre.

public:
    Recurso(int id, const std::string& nome);

    int getID() const;
    std::string getNome() const;
    int getPIDOcupante() const;
    bool isLivre() const;

    void ocupar(int pid);
    void liberar();
};

#endif // RECURSO_HPP