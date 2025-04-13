#include "Includes.h"
#include "Kernel.h"

bool compararPorPrioridade(Processo& a, Processo& b) {
    if (a.getPrioridade() == b.getPrioridade()) {
        return a.getPID() < b.getPID(); // desempate pelo PID
    }
    return a.getPrioridade() < b.getPrioridade();
}

int main()
{
    // simula prioridades a partir de um numero gerado aleatoriamente para cada processo
    random_device semente_aleatoria;
    mt19937 gen(semente_aleatoria());
    uniform_int_distribution<> distrib(1, 5);

    Kernel sistema;
    int numero_de_processos;

    cout << "Numero de processo: " << endl;
    cin >> numero_de_processos;

    for (int i = 0; i <= numero_de_processos-1; i++)
    {
        int num_aleatorio = distrib(gen);
        sistema.criarProcesso("Pronto", num_aleatorio);
    }

    cout << numero_de_processos << " Processos criados com sucesso!!" << endl << endl;

    // ordena os processo de acordo com sua prioridade
    vector<Processo> processos = sistema.getListaProcessos();
    sort(processos.begin(), processos.end(), compararPorPrioridade);

    vector<Processo> finalizados;
    for (int i = 0; i < processos.size(); i++) {
        vector<Processo> resultado = sistema.executaFIFO(processos[i]);

        // adiciona todos os processos retornados ao vetor finalizados
        finalizados.insert(finalizados.end(), resultado.begin(), resultado.end());
    }

    sistema.exibirProcessos(finalizados);
}