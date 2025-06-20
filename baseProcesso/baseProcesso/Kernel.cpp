#include "Kernel.h"
#include "Includes.h"

Kernel::Kernel(int tamanhoMemoriaTotalKB) :
    contador_pid(1),
    memoria(tamanhoMemoriaTotalKB)
{
    cout << "Kernel inicializado." << endl;
}

// Cria um processo e tenta alocar memória para ele
void Kernel::criarProcesso(int prioridade, int tempoCPU, int tamanhoMemoriaKB) {
    string nome_processo = "Processo_" + to_string(contador_pid);
    Processo novo_processo(contador_pid, prioridade, nome_processo, 0, tempoCPU, tamanhoMemoriaKB); // Tempo de chegada 0

    // Tenta alocar memória no momento da criação
    if (memoria.alocar(novo_processo.getPID(), novo_processo.getTamanhoMemoriaKB())) {
        novo_processo.setEstado(PRONTO); // Se alocou, já está pronto
        escalonador.adicionarProcesso(novo_processo); // Adiciona ao escalonador
        cout << "Kernel: Processo " << novo_processo.getNome() << " (PID " << novo_processo.getPID()
            << ") criado e memoria alocada. Adicionado ao escalonador." << endl;
    }
    else {
        novo_processo.setEstado(AGUARDANDO_MEMORIA);
        escalonador.adicionarProcesso(novo_processo);
        cerr << "Kernel: Processo " << novo_processo.getNome() << " (PID " << novo_processo.getPID()
            << ") criado, mas memoria NAO alocada. Aguardando memoria." << endl;
    }
    processosCriados.push_back(novo_processo);
    contador_pid++;
}

void Kernel::iniciarSimulacao() {
    cout << "\n--- Iniciando simulacao do Sistema Operacional ---" << endl;
    escalonador.executarSimulacao(memoria);
    cout << "\n--- Simulacao do Sistema Operacional Concluida ---" << endl;
    exibirStatusSO();
}

void Kernel::exibirProcessos(vector<Processo>& lista) {
    for (Processo& meu_processo : lista) {
        cout << "PID: " << meu_processo.getPID()
            << ", Nome: " << meu_processo.getNome()
            << ", Estado: ";
        switch (meu_processo.getEstado()) {
        case PRONTO: cout << "PRONTO"; break;
        case EXECUTANDO: cout << "EXECUTANDO"; break;
        case INSERIDO: cout << "INSERIDO"; break;
        case FINALIZADO: cout << "FINALIZADO"; break;
        case AGUARDANDO_MEMORIA: cout << "AGUARDANDO_MEMORIA"; break;
        default: cout << "DESCONHECIDO"; break;
        }
        cout << ", Prioridade: " << meu_processo.getPrioridade()
            << ", Memoria: " << meu_processo.getTamanhoMemoriaKB() << "KB"
            << ", CPU Total: " << meu_processo.getTempoExecucaoCPU() << endl;
    }
}

void Kernel::exibirStatusSO() {
    cout << "\n--- Status Final do Sistema Operacional ---" << endl;
    memoria.imprimirStatus();
    cout << "\nProcessos Finalizados:" << endl;
    exibirProcessos(escalonador.getProcessosFinalizados());
    cout << "\nProcessos na Fila de Prontos (nao finalizados):" << endl;
    exibirProcessos(escalonador.getFilaDeProntos());
    cout << "\nProcessos Aguardando Memoria (nao finalizados):" << endl;
    exibirProcessos(escalonador.getFilaDeAguardandoMemoria());
}