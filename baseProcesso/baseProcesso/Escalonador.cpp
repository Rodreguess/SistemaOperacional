#include "Escalonador.h"

Escalonador::Escalonador() {

}

void Escalonador::adicionarProcesso(Processo& p) {
    fila.push(p);
}

vector<Processo> Escalonador::executar() {
    vector<Processo> novoProcesso;
    while (!fila.empty()) {
        Processo atual = fila.front();
        fila.pop();

        cout << "Executando processo PID: " << atual.getPID()
            << " | Prioridade: " << atual.getPrioridade() << endl;

        cout << "Processo " << atual.getPID() << " finalizado.\n" << endl;

        novoProcesso.push_back(atual);
    }

    for (int i = 0; i < novoProcesso.size(); i++)
    {
        novoProcesso[i].setEstado("Finalizado");
    }

    return novoProcesso;
}