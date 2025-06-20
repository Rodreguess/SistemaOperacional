#ifndef MEMORIA_HPP
#define MEMORIA_HPP

#include "Processo.h"
#include "Escalonador.h"

class Memoria {
private:
    int tamanhoTotalKB;
    int memoriaLivreKB;
    map<int, int> alocacoesPorPID;
public:
    Memoria(int totalKB);

    // Tenta alocar memória para um processo. Retorna true se sucesso, false se falha.
    bool alocar(int pid, int tamanhoKB);

    // Libera memória alocada por um processo.
    void desalocar(int pid, int tamanhoKB);

    // Getters
    int getTamanhoTotalKB();
    int getMemoriaLivreKB();
    int getMemoriaOcupadaKB();

    void imprimirStatus();
};

#endif // MEMORIA_HPP