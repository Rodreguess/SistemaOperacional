#include "Includes.h"

struct Processo {
    int pid;
    string estado_do_processo;
    int prioridade;
};

class Sistema {
private:
    int contador_pid;
    vector<Processo> lista_de_processos; // lista de inicialização
public:
    Sistema() : contador_pid(1) {
        // construtor inicializando contador_pid com o valor 1
    } 
     
    // criando um processo e adicionando na minha lista
    void criarProcesso(string estado, int prioridade) {
        Processo novo_processo;
        novo_processo.pid = contador_pid++;
        novo_processo.estado_do_processo = estado;
        novo_processo.prioridade = prioridade;

        lista_de_processos.push_back(novo_processo);
        cout << "Processo " << novo_processo.pid << " criado com sucesso!" << endl;
    }

    // exibindo os processos criados
    void exibirProcessos() {
        for (Processo& p : lista_de_processos) {
            cout << "PID: " << p.pid << ", Estado: " << p.estado_do_processo
                << ", Prioridade: " << p.prioridade << endl;
        }
    }
};

int main()
{
    // Simulando prioridades a partir de um numero gerado aleatoriamente para cada processo
    random_device semente_aleatoria;
    mt19937 gen(semente_aleatoria());
    uniform_int_distribution<> distrib(1, 5);

    Sistema sistema;
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