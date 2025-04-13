#include "Kernel.h"

Kernel::Kernel() : contador_pid(1) {
    // inicializa o contador de PID com 1
}

vector<Processo> Kernel::executaFIFO(Processo& p) {
    Escalonador E;
    vector<Processo> A;
    E.adicionarProcesso(p); //adiciono o processo na fila
    A = E.executar();
    return A;
}

vector<Processo>& Kernel::getListaProcessos()
{
    return lista_de_processos;
}

// criando um processo e adicionando na minha lista
void Kernel::criarProcesso(string estado, int prioridade) {
    Processo novo_processo;
    novo_processo.setPID(contador_pid++);
    novo_processo.setEstado(estado);
    novo_processo.setPrioridade(prioridade);

    lista_de_processos.push_back(novo_processo);
}

void Kernel::exibirProcessos(vector<Processo> lista) {
    for (Processo& meu_processo : lista) {
        cout << "PID: " << meu_processo.getPID() << ", Estado: " << meu_processo.getEstado()
            << ", Prioridade: " << meu_processo.getPrioridade() << endl;
    }
}