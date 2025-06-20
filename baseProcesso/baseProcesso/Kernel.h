#ifndef KERNEL_HPP
#define KERNEL_HPP

#include "Processo.h"
#include "Escalonador.h"
#include "Memoria.h"
#include "GerenciadorRecursos.h"

#include <vector>
#include <string>

class Kernel
{
private:
    int contador_pid;
    Escalonador escalonador;
    Memoria memoria;
    GerenciadorRecursos gerenciadorRecursos;

    vector<Processo> processosCriados;

public:
    Kernel(int tamanhoMemoriaTotalKB);

    void adicionarRecurso(const std::string& nome);

    void criarProcesso(int prioridade, int tempoCPU, int tamanhoMemoriaKB);
    void iniciarSimulacao();

    void iniciarSimulacaoDeadlock(int cenario);

    void exibirProcessos(std::vector<Processo>& lista);
    void exibirStatusSO() ;
};

#endif // KERNEL_HPP