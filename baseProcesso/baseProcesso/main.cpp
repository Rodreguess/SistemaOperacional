// main.cpp

#include "Includes.h"
#include "Kernel.h" // Inclua apenas o Kernel, que já inclui o resto

int main()
{
    // Simula prioridades, tempo de CPU e memória
    random_device semente_aleatoria;
    mt19937 gen(semente_aleatoria());
    uniform_int_distribution<> distrib_prioridade(1, 4);   // Prioridade de 1 a 4
    uniform_int_distribution<> distrib_tempo_cpu(5, 20);    // Tempo de CPU necessário (5 a 20 unidades)
    uniform_int_distribution<> distrib_memoria_kb(10, 100); // Memória em KB (10 a 100 KB)

    // Defina o tamanho total da memória do seu SO simulado
     int MEMORIA_TOTAL_SO_KB = 1024; // Exemplo: 1MB de memória total

    Kernel sistema(MEMORIA_TOTAL_SO_KB); // Cria o Kernel, inicializando a memória

    int numero_de_processos;
    cout << "Numero de processos a criar: ";
    cin >> numero_de_processos;

    for (int i = 0; i < numero_de_processos; ++i) {
        int prio_aleatoria = distrib_prioridade(gen);
        int tempo_cpu_aleatorio = distrib_tempo_cpu(gen);
        int memoria_aleatoria = distrib_memoria_kb(gen);

        sistema.criarProcesso(prio_aleatoria, tempo_cpu_aleatorio, memoria_aleatoria);
    }

    cout << "\nTodos os processos foram criados e encaminhados ao Kernel." << endl;

    // O Kernel agora é responsável por iniciar a simulação
    sistema.iniciarSimulacao();

    cout << "\nPressione qualquer tecla para fechar esta janela...";
    cin.ignore(); // Limpa o buffer do cin
    cin.get();    // Espera por uma tecla

    return 0;
}