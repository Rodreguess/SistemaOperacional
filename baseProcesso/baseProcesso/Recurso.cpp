#include "Recurso.h"
#include "Includes.h"

Recurso::Recurso(int id, const string& nome) : id(id), nome(nome), pid_ocupante(0) {
}

int Recurso::getID() const {
    return id; 
}
string Recurso::getNome() const { 
    return nome; 
}
int Recurso::getPIDOcupante() const { 
    return pid_ocupante; 
}
bool Recurso::isLivre() const { 
    return pid_ocupante == 0; 
}

void Recurso::ocupar(int pid) {
    if (pid_ocupante == 0) {
        pid_ocupante = pid;
    }
}

void Recurso::liberar() {
    if (pid_ocupante != 0) {
        pid_ocupante = 0;
    }
}