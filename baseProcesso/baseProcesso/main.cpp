#include "Includes.h"
#include "Kernel.h"

int main()
{
    // Simulando prioridades a partir de um numero gerado aleatoriamente para cada processo
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

    sistema.exibirProcessos();
}