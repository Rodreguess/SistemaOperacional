#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "Processo.h"

class Escalonador {
private:
    std::queue<Processo> fila; //minha fila de processos, ordenada de acordo com a prioridade do processo

public:
    Escalonador();
    void adicionarProcesso(Processo& p);
    vector<Processo> executar();
};

#endif