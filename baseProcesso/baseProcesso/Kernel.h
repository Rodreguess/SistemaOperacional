// Kernel.h (ou Kernel.hpp)

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
    // O Kernel gerencia o escalonador e a memória
    Escalonador escalonador;
    Memoria memoria; // Instância da classe Memoria

    // list_de_processos pode ser o ponto de entrada de todos os processos criados
    std::vector<Processo> processosCriados;

public:
    Kernel(int tamanhoMemoriaTotalKB); // Construtor com o tamanho da memória

    // Novo método para criar processo com os detalhes de simulação
    void criarProcesso(int prioridade, int tempoCPU, int tamanhoMemoriaKB);

    // O método que inicia a simulação do SO, chamando o escalonador
    void iniciarSimulacao();

    // Métodos para obter informações do estado atual do SO
    void exibirProcessos(vector<Processo>& lista); // Recebe const reference
    void exibirStatusSO(); // Exibe status geral do SO
};

#endif // KERNEL_HPP