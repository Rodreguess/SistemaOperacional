#ifndef GERENCIADOR_RECURSOS_HPP
#define GERENCIADOR_RECURSOS_HPP

#include "Recurso.h"
#include "Includes.h"

class GerenciadorRecursos {
private:
    vector<Recurso> recursosDisponiveis;
    int proximoIDRecurso;
    map<int, vector<int>> recursosPossuidosPorPID;
    map<int, vector<int>> recursosEsperadosPorPID;

public:
    GerenciadorRecursos();

    void adicionarRecurso(const string& nome);

    bool solicitarRecurso(int pid, int idRecurso);
    void liberarRecurso(int pid, int idRecurso);

    const vector<Recurso>& getRecursos() const;
    void imprimirStatus() const;
    vector<int> getRecursosPossuidosPorPID(int pid) const;
};

#endif // GERENCIADOR_RECURSOS_HPP