#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "Processo.h"
#include "Includes.h"

class Escalonador
{
private:
    vector<Processo> filaDeProntos;
    vector<Processo> processosFinalizados;
    vector<Processo> filaDeAguardandoMemoria;
public:
    Escalonador(); // Construtor

    void adicionarProcesso(Processo p);

    vector<Processo> executarSimulacao(class Memoria& memoria);

    static bool compararPrioridade( Processo& a,  Processo& b);

     vector<Processo>& getProcessosFinalizados() ;
     vector<Processo>& getFilaDeProntos() ;
     vector<Processo>& getFilaDeAguardandoMemoria() ;
};

#endif // ESCALONADOR_HPP