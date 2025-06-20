#include "Escalonador.h"
#include "Memoria.h"
#include "Includes.h"

Escalonador::Escalonador() {}

// Comparador de prioridade
bool Escalonador::compararPrioridade(Processo& a,  Processo& b) {
    if (a.getPrioridade() != b.getPrioridade()) {
        return a.getPrioridade() < b.getPrioridade();
    }
    return a.getPID() < b.getPID();
}

void Escalonador::adicionarProcesso(Processo p) {
    p.setEstado(PRONTO); // Ao ser adicionado ao escalonador, ele está pronto
    filaDeProntos.push_back(p);
    sort(filaDeProntos.begin(), filaDeProntos.end(), compararPrioridade);
}

vector<Processo> Escalonador::executarSimulacao(Memoria& memoria) {
    int tempoGlobal = 0;

    cout << "\n--- Iniciando Simulacao de Escalonamento ---" << endl;

    while (!filaDeProntos.empty() || !filaDeAguardandoMemoria.empty()) {
        tempoGlobal++; // Incrementa o tempo do sistema a cada "ciclo"

        cout << "\n--- Tempo Global: " << tempoGlobal << " ---" << endl;
        memoria.imprimirStatus();

        vector<Processo> processosMovidosParaProntos;
        auto it_mem = filaDeAguardandoMemoria.begin();
        while (it_mem != filaDeAguardandoMemoria.end()) {
            if (memoria.alocar(it_mem->getPID(), it_mem->getTamanhoMemoriaKB())) {
                it_mem->setEstado(PRONTO);
                processosMovidosParaProntos.push_back(*it_mem);
                it_mem = filaDeAguardandoMemoria.erase(it_mem);
            }
            else {
                ++it_mem;
            }
        }
        // Adiciona os processos que agora estão prontos à fila de prontos
        for (auto& p : processosMovidosParaProntos) {
            filaDeProntos.push_back(p);
        }
        sort(filaDeProntos.begin(), filaDeProntos.end(), compararPrioridade);

        if (!filaDeProntos.empty()) {
            Processo& processoAtual = filaDeProntos[0]; // Pega o de maior prioridade

            // Simula o consumo de 1 unidade de CPU
            processoAtual.setEstado(EXECUTANDO);
            processoAtual.decrementarTempoRestanteCPU(1);

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

                // Desaloca a memória do processo
                memoria.desalocar(processoAtual.getPID(), processoAtual.getTamanhoMemoriaKB());

                processosFinalizados.push_back(processoAtual);
                filaDeProntos.erase(filaDeProntos.begin()); // Remove da lista de prontos
            }
        }
        else if (filaDeAguardandoMemoria.empty()) {
            cout << "  Nenhum processo pronto para execucao no momento." << endl;
            // Isso pode indicar que todos os processos estão finalizados ou bloqueados por algum motivo que não seja falta de memória aqui.
            if (processosFinalizados.size() == (processosFinalizados.size() + filaDeAguardandoMemoria.size() + filaDeProntos.size())) {
                break;
            }
        }
    }

    cout << "\n--- Simulacao Concluida ---" << endl;
    memoria.imprimirStatus();
    return processosFinalizados;
}

 vector<Processo>& Escalonador::getProcessosFinalizados()  {
    return processosFinalizados;
}

 vector<Processo>& Escalonador::getFilaDeProntos()  {
    return filaDeProntos;
}

 vector<Processo>& Escalonador::getFilaDeAguardandoMemoria()  {
    return filaDeAguardandoMemoria;
}