#ifndef KERNEL_HPP
#define KERNEL_HPP
#include "Processo.h"

class Kernel
{
private:
    int contador_pid;
    vector<Processo> lista_de_processos; // lista de inicialização
public:
    Kernel(); // construtor
    void criarProcesso(string estado, int prioridade);
    void exibirProcessos();

};
#endif