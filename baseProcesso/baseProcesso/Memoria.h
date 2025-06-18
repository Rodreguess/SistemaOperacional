#ifndef MEMORIA_HPP
#define MEMORIA_HPP
#include "Processo.h"
#include "Escalonador.h"


class Memoria {
private:
    int tamanhoTotalKB;
    int memoriaLivreKB;
    // Usaremos um mapa para registrar quanto de memória cada PID alocou
   map<int, int> alocacoesPorPID;

public:
    Memoria(int totalKB);

    // Tenta alocar memória para um processo. Retorna true se sucesso, false se falha.
    bool alocar(int pid, int tamanhoKB);

    // Libera memória alocada por um processo.
    void desalocar(int pid, int tamanhoKB);

    // Getters
    int getTamanhoTotalKB() const;
    int getMemoriaLivreKB() const;
    int getMemoriaOcupadaKB() const;

    // Opcional: imprimir o estado atual da memória
    void imprimirStatus() const;
};

#endif // MEMORIA_HPP