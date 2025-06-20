#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "Memoria.h"
#include "Processo.h"
#include "GerenciadorRecursos.h"
#include "Includes.h"

class Escalonador
{
private:
    vector<Processo> filaDeProntos;
    vector<Processo> processosFinalizados;
    vector<Processo> filaDeAguardandoMemoria;
    vector<Processo> filaDeAguardandoRecurso; // Nova fila para processos esperando recursos

public:
    Escalonador();

    void adicionarProcesso(Processo p);

    // Agora aceita GerenciadorRecursos também
    vector<Processo> executarSimulacao(Memoria& mr, GerenciadorRecursos& gr);

    static bool compararPrioridade(Processo& a, Processo& b);

    vector<Processo>& getProcessosFinalizados();
    vector<Processo>& getFilaDeProntos();
    vector<Processo>& getFilaDeAguardandoMemoria();
    vector<Processo>& getFilaDeAguardandoRecurso(); // Novo getter
};

#endif // ESCALONADOR_HPP