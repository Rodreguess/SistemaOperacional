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
    Processo(); // construtor padrao
    void setPID(int p);
    void setEstado(string e);
    void setPrioridade(int prio);

    int getPID();
    string getEstado();
    int getPrioridade();
};

#endif // !PROCESSO_HPP



