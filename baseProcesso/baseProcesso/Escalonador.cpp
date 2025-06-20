#include "Escalonador.h"

Escalonador::Escalonador() {
    // Construtor
}

bool Escalonador::compararPrioridade(Processo& a, Processo& b) {
    if (a.getPrioridade() != b.getPrioridade()) {
        return a.getPrioridade() < b.getPrioridade();
    }
    return a.getPID() < b.getPID();
}

void Escalonador::adicionarProcesso(Processo p) {
    if (p.getEstado() == AGUARDANDO_MEMORIA) {
        filaDeAguardandoMemoria.push_back(p);
    }
    else {
        filaDeProntos.push_back(p);
        sort(filaDeProntos.begin(), filaDeProntos.end(), compararPrioridade);
    }
}

void simularComportamentoDeRecursos(Processo& p, GerenciadorRecursos& gr, int tempoGlobal) {
    if (p.getPID() == 101 && p.getTempoExecucaoCPU() - p.getTempoRestanteCPU() == 2) { // Exemplo: apos 2 unidades de CPU
        gr.solicitarRecurso(p.getPID(), 2); // P1 ja tem R1, agora pede R2
    }
    if (p.getPID() == 102 && p.getTempoExecucaoCPU() - p.getTempoRestanteCPU() == 2) { // Exemplo: apos 2 unidades de CPU
        gr.solicitarRecurso(p.getPID(), 1); // P2 ja tem R2, agora pede R1
    }
}


vector<Processo> Escalonador::executarSimulacao(Memoria& mr, GerenciadorRecursos& gr) {
    int tempoGlobal = 0;

    cout << "\n--- Iniciando Simulacao de Escalonamento ---" << endl;

    while (!filaDeProntos.empty() || !filaDeAguardandoMemoria.empty() || !filaDeAguardandoRecurso.empty()) {
        tempoGlobal++;
        cout << "\n--- Tempo Global: " << tempoGlobal << " ---" << endl;
        mr.imprimirStatus();
        gr.imprimirStatus(); // Imprime o status dos recursos a cada ciclo

        // 1. Tentar mover processos da fila de espera de memória para a fila de prontos
        auto it_mem = filaDeAguardandoMemoria.begin();
        while (it_mem != filaDeAguardandoMemoria.end()) {
            if (mr.alocar(it_mem->getPID(), it_mem->getTamanhoMemoriaKB())) {
                it_mem->setEstado(PRONTO);
                filaDeProntos.push_back(*it_mem);
                it_mem = filaDeAguardandoMemoria.erase(it_mem);
            }
            else {
                ++it_mem;
            }
        }
        sort(filaDeProntos.begin(), filaDeProntos.end(), compararPrioridade);

        vector<Processo> processosMovidosParaProntosDeRecurso;
        auto it_rec = filaDeAguardandoRecurso.begin();
        while (it_rec != filaDeAguardandoRecurso.end()) {
            ++it_rec;
        }

        // 3. Selecionar e executar o próximo processo na fila de prontos
        if (!filaDeProntos.empty()) {
            Processo& processoAtual = filaDeProntos[0];

            // Simula o consumo de 1 unidade de CPU
            processoAtual.setEstado(EXECUTANDO);
            processoAtual.decrementarTempoRestanteCPU(1);

            // Chamada para a função que simula o comportamento de recursos do processo
            simularComportamentoDeRecursos(processoAtual, gr, tempoGlobal);

            cout << "  Executando " << processoAtual.getNome()
                << " (PID: " << processoAtual.getPID()
                << ", Pri: " << processoAtual.getPrioridade()
                << ", Mem: " << processoAtual.getTamanhoMemoriaKB() << "KB"
                << ", CPU Rest: " << processoAtual.getTempoRestanteCPU() << ")" << endl;

            // Verifica se o processo terminou sua execução
            if (processoAtual.isFinalizado()) {
                processoAtual.setEstado(FINALIZADO);
                cout << "  " << processoAtual.getNome()
                    << " (PID: " << processoAtual.getPID() << ") FINALIZADO." << endl;

                mr.desalocar(processoAtual.getPID(), processoAtual.getTamanhoMemoriaKB());
                vector<int> recursosDoProcesso = gr.getRecursosPossuidosPorPID(processoAtual.getPID());
                for (int recID : recursosDoProcesso) {
                    gr.liberarRecurso(processoAtual.getPID(), recID);
                }

                processosFinalizados.push_back(processoAtual);
                filaDeProntos.erase(filaDeProntos.begin());
            }
        }
        else if (filaDeAguardandoMemoria.empty() && filaDeAguardandoRecurso.empty()) {
            cout << "  Nenhum processo pronto para execucao no momento." << endl;
            // Se não há processos prontos, nem aguardando memória, nem aguardando recurso, a simulação pode parar.
            if (processosFinalizados.size() == (processosFinalizados.size() + filaDeAguardandoMemoria.size() + filaDeProntos.size() + filaDeAguardandoRecurso.size())) {
                break;
            }
        }
    }

    cout << "\n--- Simulacao Concluida ---" << endl;
    mr.imprimirStatus();
    gr.imprimirStatus();

    return processosFinalizados;
}

vector<Processo>& Escalonador::getProcessosFinalizados(){ return processosFinalizados; }
vector<Processo>& Escalonador::getFilaDeProntos() { return filaDeProntos; }
vector<Processo>& Escalonador::getFilaDeAguardandoMemoria() { return filaDeAguardandoMemoria; }
vector<Processo>& Escalonador::getFilaDeAguardandoRecurso() { return filaDeAguardandoRecurso; }