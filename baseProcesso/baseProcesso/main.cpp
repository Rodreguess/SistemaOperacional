#include "Kernel.h"
#include "Includes.h"

int main()
{
    const int MEMORIA_TOTAL_SO_KB = 500;

    int escolha;
    do {
        cout << "\n--- Menu de Simulacao de SO ---" << endl;
        cout << "1. Rodar simulacao de processos (FIFO por Prioridade)" << endl;
        cout << "2. Ver cenario de DEADLOCK (Exemplo 1)" << endl;
        cout << "3. Ver cenario SEM DEADLOCK (Exemplo 2)" << endl;
        cout << "0. Sair" << endl;
        cout << "Selecione uma opcao: ";

        cin >> escolha;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Kernel sistema(MEMORIA_TOTAL_SO_KB); // Cria o Kernel para cada simulacao

        if (escolha == 1) {
            random_device semente_aleatoria;
            mt19937 gen(semente_aleatoria());
            uniform_int_distribution<> distrib_prioridade(1, 4);
            uniform_int_distribution<> distrib_tempo_cpu(5, 20);
            uniform_int_distribution<> distrib_memoria_kb(10, 100);

            sistema.adicionarRecurso("Impressora"); // Adiciona alguns recursos para a simulação geral
            sistema.adicionarRecurso("Scanner");

            int numero_de_processos;
            cout << "Numero de processos a criar: ";
            cin >> numero_de_processos;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (int i = 0; i < numero_de_processos; ++i) {
                int prio_aleatoria = distrib_prioridade(gen);
                int tempo_cpu_aleatorio = distrib_tempo_cpu(gen);
                int memoria_aleatoria = distrib_memoria_kb(gen);

                sistema.criarProcesso(prio_aleatoria, tempo_cpu_aleatorio, memoria_aleatoria);
            }

            cout << "\nTodos os processos foram criados e encaminhados ao Kernel." << endl;
            sistema.iniciarSimulacao();

        }
        else if (escolha == 2) {
            sistema.iniciarSimulacaoDeadlock(1); // Chama o cenário 1 de deadlock
        }
        else if (escolha == 3) {
            sistema.iniciarSimulacaoDeadlock(2); // Chama o cenário 2 (sem deadlock)
        }
        else if (escolha != 0) {
            cout << "Opcao invalida. Tente novamente." << endl;
        }

        if (escolha != 0) {
            cout << "\nPressione Enter para continuar...";
            cin.get(); // Espera por uma tecla (Enter)
        }

    } while (escolha != 0);

    return 0;
}