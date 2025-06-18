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
    Escalonador();

    // Adiciona um processo ao escalonador (ele decidirá onde colocá-lo)
    void adicionarProcesso(Processo p); // Recebe por valor ou rvalue reference para Processo recém-criado

    // O método principal que executa a simulação do escalonamento
    vector<Processo> executarSimulacao(class Memoria& memoria); // Precisa interagir com a memória

    // Funções auxiliares (static para não depender de uma instância, ou membro)
    static bool compararPrioridade( Processo& a,  Processo& b);

    // Getters para as listas de processos
     vector<Processo>& getProcessosFinalizados() ;
     vector<Processo>& getFilaDeProntos() ;
     vector<Processo>& getFilaDeAguardandoMemoria() ;
};

#endif // ESCALONADOR_HPP