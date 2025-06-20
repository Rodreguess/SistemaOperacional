#include "Kernel.h"

Kernel::Kernel(int tamanhoMemoriaTotalKB) :
    contador_pid(1),
    memoria(tamanhoMemoriaTotalKB)
{
    cout << "Kernel inicializado." << endl;
}

void Kernel::adicionarRecurso(const string& nome) {
    gerenciadorRecursos.adicionarRecurso(nome);
}

void Kernel::criarProcesso(int prioridade, int tempoCPU, int tamanhoMemoriaKB) {
    string nome_processo = "Processo_" + to_string(contador_pid);
    Processo novo_processo(contador_pid, prioridade, nome_processo, 0, tempoCPU, tamanhoMemoriaKB);

    if (memoria.alocar(novo_processo.getPID(), novo_processo.getTamanhoMemoriaKB())) {
        novo_processo.setEstado(PRONTO);
        escalonador.adicionarProcesso(novo_processo);
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
    escalonador.executarSimulacao(memoria, gerenciadorRecursos); // Passa o gerenciador de recursos também
    cout << "\n--- Simulacao do Sistema Operacional Concluida ---" << endl;
    exibirStatusSO();
}

// Implementação dos cenários de deadlock
void Kernel::iniciarSimulacaoDeadlock(int cenario) {
    cout << "\n--- Iniciando simulacao de Deadlock - Cenario " << cenario << " ---" << endl;

    // Limpa estado anterior se houver
    processosCriados.clear();

    // Reinicializa recursos
    gerenciadorRecursos = GerenciadorRecursos(); // Cria nova instancia para limpar
    gerenciadorRecursos.adicionarRecurso("Impressora"); // ID 1
    gerenciadorRecursos.adicionarRecurso("Scanner");    // ID 2
    gerenciadorRecursos.adicionarRecurso("Disco");      // ID 3

    if (cenario == 1) { // Deadlock simples (2 processos, 2 recursos)
        cout << "\nCenario 1: Deadlock entre P1 e P2 (Esperando Circularmente)" << endl;

        // P1: Tenta obter Recurso 1, depois Recurso 2
        Processo p1(101, 1, "P1", 0, 10, 20);
        if (memoria.alocar(p1.getPID(), p1.getTamanhoMemoriaKB())) {
            p1.setEstado(PRONTO);
            escalonador.adicionarProcesso(p1);
            gerenciadorRecursos.solicitarRecurso(p1.getPID(), 1); // P1 pega Recurso 1
        }
        else { cerr << "Memoria insuficiente para P1." << endl; return; }

        // P2: Tenta obter Recurso 2, depois Recurso 1
        Processo p2(102, 1, "P2", 0, 10, 20);
        if (memoria.alocar(p2.getPID(), p2.getTamanhoMemoriaKB())) {
            p2.setEstado(PRONTO);
            escalonador.adicionarProcesso(p2);
            gerenciadorRecursos.solicitarRecurso(p2.getPID(), 2); // P2 pega Recurso 2
        }
        else { cerr << "Memoria insuficiente para P2." << endl; return; }

        cout << "\nStatus Atual dos Recursos (Cenario 1 - Deadlock):" << endl;
        gerenciadorRecursos.imprimirStatus();
        cout << "\nPID " << p1.getPID() << " possui Recurso 1 e espera Recurso 2." << endl;
        cout << "PID " << p2.getPID() << " possui Recurso 2 e espera Recurso 1." << endl;
        cout << "Condicoes para deadlock satisfeitas (Espera Circular)." << endl;

    }
    else if (cenario == 2) {
        cout << "\nCenario 2: Sem Deadlock (Alocacao Ordenada de Recursos)" << endl;

        // P1: Tenta obter R1, depois R2
        Processo p1(201, 1, "P1_NoDeadlock", 0, 10, 20);
        if (memoria.alocar(p1.getPID(), p1.getTamanhoMemoriaKB())) {
            p1.setEstado(PRONTO);
            escalonador.adicionarProcesso(p1);
            gerenciadorRecursos.solicitarRecurso(p1.getPID(), 1); // P1 pega Recurso 1
        }
        else { cerr << "Memoria insuficiente para P1." << endl; return; }

        // P2: Tenta obter R1, depois R2 (mesma ordem que P1)
        Processo p2(202, 1, "P2_NoDeadlock", 0, 10, 20);
        if (memoria.alocar(p2.getPID(), p2.getTamanhoMemoriaKB())) {
            p2.setEstado(PRONTO);
            escalonador.adicionarProcesso(p2);
            // P2 tenta pegar R1, mas P1 já tem. P2 vai esperar.
            gerenciadorRecursos.solicitarRecurso(p2.getPID(), 1);
        }
        else { cerr << "Memoria insuficiente para P2." << endl; return; }

        cout << "\nStatus Atual dos Recursos (Cenario 2 - Sem Deadlock):" << endl;
        gerenciadorRecursos.imprimirStatus();
        cout << "P1 possui Recurso 1." << endl;
        cout << "P2 espera Recurso 1 (e so depois tentaria R2)." << endl;
        cout << "Nao ha espera circular. P2 eventualmente obterá R1 apos P1 liberar." << endl;

    }
    else {
        cout << "Cenario de deadlock invalido." << endl;
    }

    cout << "\n--- Simulacao de Deadlock Concluida (Apenas status, sem execucao) ---" << endl;
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
    gerenciadorRecursos.imprimirStatus();
    cout << "\nProcessos Finalizados:" << endl;
    exibirProcessos(escalonador.getProcessosFinalizados());
    cout << "\nProcessos na Fila de Prontos (nao finalizados):" << endl;
    exibirProcessos(escalonador.getFilaDeProntos());
    cout << "\nProcessos Aguardando Memoria (nao finalizados):" << endl;
    exibirProcessos(escalonador.getFilaDeAguardandoMemoria());
    cout << "\nProcessos esperando Recursos:" << endl;
}