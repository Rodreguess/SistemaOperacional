#include "Kernel.h"

Kernel::Kernel() : contador_pid(1) {
    // inicializa o contador de PID com 1
}

// criando um processo e adicionando na minha lista
void Kernel::criarProcesso(string estado, int prioridade) {
    Processo novo_processo;
    novo_processo.setPID(contador_pid++);
    novo_processo.setEstado(estado);
    novo_processo.setPrioridade(prioridade);

    lista_de_processos.push_back(novo_processo);
    cout << "Processo " << novo_processo.getPID() << " criado com sucesso!" << endl;
}

void Kernel::exibirProcessos() {
    for (Processo& meu_processo : lista_de_processos) {
        cout << "PID: " << meu_processo.getPID() << ", Estado: " << meu_processo.getEstado()
            << ", Prioridade: " << meu_processo.getPrioridade() << endl;
    }
}