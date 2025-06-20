#ifndef KERNEL_HPP
#define KERNEL_HPP

#include "Processo.h"
#include "Escalonador.h"
#include "Memoria.h"
#include "Includes.h"

class Kernel
{
private:
    int contador_pid;
    Escalonador escalonador;
    Memoria memoria;
    vector<Processo> processosCriados;

public:
    Kernel(int tamanhoMemoriaTotalKB); // Construtor

    void criarProcesso(int prioridade, int tempoCPU, int tamanhoMemoriaKB);
    void iniciarSimulacao();

    void exibirProcessos(vector<Processo>& lista);
    void exibirStatusSO();
};

#endif // KERNEL_HPP