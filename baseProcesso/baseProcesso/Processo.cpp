#include "Processo.h"
#include "Includes.h"

Processo::Processo() :
    pid(0), estado(INSERIDO), prioridade(0), nome(""), tempoChegada(0),
    tempoExecucaoCPU(0), tempoRestanteCPU(0), tamanhoMemoriaKB(0)
{
}

Processo::Processo(int p, int prio,  string& n, int chegada, int execucaoCPU, int memoriaKB) :
    pid(p), estado(INSERIDO), prioridade(prio), nome(n), tempoChegada(chegada),
    tempoExecucaoCPU(execucaoCPU), tempoRestanteCPU(execucaoCPU), tamanhoMemoriaKB(memoriaKB)
{
}

void Processo::setPID(int p) { 
    pid = p; 
}
void Processo::setEstado(EstadoProcesso e) {
    estado = e; 
}
void Processo::setPrioridade(int prio) { 
    prioridade = prio; 
}
void Processo::setNome( string& n) { 
    nome = n; 
}
void Processo::setTempoChegada(int tc) { 
    tempoChegada = tc; 
}

void Processo::decrementarTempoRestanteCPU(int deltaTempo) {
    tempoRestanteCPU -= deltaTempo;
    if (tempoRestanteCPU < 0) {
        tempoRestanteCPU = 0;
    }
}

int Processo::getPID()  { 
    return pid; 
}
EstadoProcesso Processo::getEstado()  { 
    return estado; 
}
int Processo::getPrioridade()  { 
    return prioridade; 
}
string Processo::getNome()  { 
    return nome; 
}
int Processo::getTempoChegada()  { 
    return tempoChegada; 
}
int Processo::getTempoExecucaoCPU()  { 
    return tempoExecucaoCPU; 
}
int Processo::getTempoRestanteCPU()  { 
    return tempoRestanteCPU; 
}
int Processo::getTamanhoMemoriaKB()  { 
    return tamanhoMemoriaKB; 
}
bool Processo::isFinalizado()  { 
    return tempoRestanteCPU <= 0; 
}