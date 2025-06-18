#ifndef PROCESSO_HPP
#define PROCESSO_HPP

#include "Includes.h"

enum EstadoProcesso {
    PRONTO,
    EXECUTANDO,
    INSERIDO,
    FINALIZADO,
    AGUARDANDO_MEMORIA
};

class Processo
{
private:
    int pid;
    EstadoProcesso estado;
    int prioridade;
    std::string nome;
    int tempoChegada;       // Momento em que o processo "chegou" ao sistema
    int tempoExecucaoCPU;   // Tempo total de CPU que o processo precisa
    int tempoRestanteCPU;   // Tempo de CPU restante para o processo
    int tamanhoMemoriaKB;   // Tamanho da memória em KB que o processo consome

public:
    Processo(); // Construtor
    Processo(int p, int prio,  std::string& n, int chegada, int execucaoCPU, int memoriaKB);

    // Setters
    void setPID(int p);
    void setEstado(EstadoProcesso e);
    void setPrioridade(int prio);
    void setNome( std::string& n);
    void setTempoChegada(int tc);
    void decrementarTempoRestanteCPU(int deltaTempo = 1);

    // Getters
    int getPID();
    EstadoProcesso getEstado();
    int getPrioridade();
    std::string getNome();
    int getTempoChegada() ;
    int getTempoExecucaoCPU() ;
    int getTempoRestanteCPU() ;
    int getTamanhoMemoriaKB() ;

    bool isFinalizado() ; // Verifica se o processo finalizou sua execução de CPU
};

#endif // PROCESSO_HPP