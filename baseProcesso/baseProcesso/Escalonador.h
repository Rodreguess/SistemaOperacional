#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "Processo.h"

class Escalonador {
private:
    std::queue<Processo> fila;

public:
    Escalonador();
    void adicionarProcesso(Processo& p);
    void executar();
};

#endif