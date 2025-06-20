#ifndef MEMORIA_HPP
#define MEMORIA_HPP

#include "Processo.h"

class Memoria {
private:
    int tamanhoTotalKB;
    int memoriaLivreKB;
    map<int, int> alocacoesPorPID;
public:
    Memoria(int totalKB);
    bool alocar(int pid, int tamanhoKB);
    void desalocar(int pid, int tamanhoKB);

    int getTamanhoTotalKB();
    int getMemoriaLivreKB();
    int getMemoriaOcupadaKB();

    void imprimirStatus();
};

#endif // MEMORIA_HPP