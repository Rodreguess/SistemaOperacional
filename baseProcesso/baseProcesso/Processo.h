#ifndef PROCESSO_HPP
#define PROCESSO_HPP
#include "Includes.h"

class Processo
{
private:
    int pid;
    string estado_do_processo;
    int prioridade;
public:
    Processo() {}; // construtor padrao
    void setPID(int p) { pid = p; }
    void setEstado(string e) { estado_do_processo = e; }
    void setPrioridade(int prio) { prioridade = prio; }

    int getPID() { return pid; }
    string getEstado() { return estado_do_processo; }
    int getPrioridade() { return prioridade; }
};

#endif // !PROCESSO_HPP



