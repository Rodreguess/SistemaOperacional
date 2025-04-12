#include "Escalonador.h"

void Escalonador::adicionarProcesso(Processo& p) {
    fila.push(p);
}

void Escalonador::executar() {
    while (!fila.empty()) {
        Processo atual = fila.front();
        fila.pop();

        std::cout << "Executando processo PID: " << atual.getPID()
            << " | Estado: " << atual.getEstado()
            << " | Prioridade: " << atual.getPrioridade() << "s" << std::endl;

        std::cout << "Processo " << atual.getPID() << " finalizado.\n" << std::endl;
    }
}