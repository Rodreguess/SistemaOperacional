#include "GerenciadorRecursos.h"

GerenciadorRecursos::GerenciadorRecursos() : proximoIDRecurso(1) {}

void GerenciadorRecursos::adicionarRecurso(const string& nome) {
    recursosDisponiveis.emplace_back(proximoIDRecurso++, nome);
    cout << "Recurso '" << nome << "' (ID " << (proximoIDRecurso - 1) << ") adicionado." << endl;
}

bool GerenciadorRecursos::solicitarRecurso(int pid, int idRecurso) {
    for (auto& rec : recursosDisponiveis) {
        if (rec.getID() == idRecurso) {
            if (rec.isLivre()) {
                rec.ocupar(pid);
                recursosPossuidosPorPID[pid].push_back(idRecurso);
                cout << "GR: PID " << pid << " solicitou e obteve " << rec.getNome() << " (ID " << idRecurso << ")." << endl;
                // Remover do que estava esperando, se estava esperando
                auto& esperados = recursosEsperadosPorPID[pid];
                esperados.erase(remove(esperados.begin(), esperados.end(), idRecurso), esperados.end());
                return true;
            }
            else {
                cout << "GR: PID " << pid << " solicitou " << rec.getNome() << " (ID " << idRecurso << "), mas esta OCUPADO por PID " << rec.getPIDOcupante() << ". Adicionado a espera." << endl;
                // Marca que o PID está esperando por este recurso
                if (find(recursosEsperadosPorPID[pid].begin(), recursosEsperadosPorPID[pid].end(), idRecurso) == recursosEsperadosPorPID[pid].end()) {
                    recursosEsperadosPorPID[pid].push_back(idRecurso);
                }
                return false;
            }
        }
    }
    cerr << "GR: Recurso com ID " << idRecurso << " nao encontrado." << endl;
    return false;
}

void GerenciadorRecursos::liberarRecurso(int pid, int idRecurso) {
    for (auto& rec : recursosDisponiveis) {
        if (rec.getID() == idRecurso && rec.getPIDOcupante() == pid) {
            rec.liberar();
            // Remove o recurso da lista de possuídos pelo PID
            auto& possuidos = recursosPossuidosPorPID[pid];
            possuidos.erase(remove(possuidos.begin(), possuidos.end(), idRecurso), possuidos.end());
            cout << "GR: PID " << pid << " liberou " << rec.getNome() << " (ID " << idRecurso << ")." << endl;
            return;
        }
    }
    cerr << "GR: PID " << pid << " tentou liberar Recurso com ID " << idRecurso << " que nao possui ou nao existe." << endl;
}

const vector<Recurso>& GerenciadorRecursos::getRecursos() const {
    return recursosDisponiveis;
}

void GerenciadorRecursos::imprimirStatus() const {
    cout << "\n--- Status dos Recursos ---" << endl;
    if (recursosDisponiveis.empty()) {
        cout << "Nenhum recurso configurado." << endl;
        return;
    }
    for (const auto& rec : recursosDisponiveis) {
        cout << "  Recurso " << rec.getNome() << " (ID " << rec.getID() << "): ";
        if (rec.isLivre()) {
            cout << "LIVRE";
        }
        else {
            cout << "OCUPADO por PID " << rec.getPIDOcupante();
        }
        cout << endl;
    }
    cout << "--- Recursos Possuidos ---" << endl;
    for (const auto& pair : recursosPossuidosPorPID) {
        cout << "  PID " << pair.first << " possui: ";
        for (int recID : pair.second) {
            cout << recID << " ";
        }
        cout << endl;
    }
    cout << "--- Recursos Esperados ---" << endl;
    for (const auto& pair : recursosEsperadosPorPID) {
        cout << "  PID " << pair.first << " espera: ";
        for (int recID : pair.second) {
            cout << recID << " ";
        }
        cout << endl;
    }
    cout << "--------------------------" << endl;
}

vector<int> GerenciadorRecursos::getRecursosPossuidosPorPID(int pid) const {
    // Verifica se o PID existe no mapa
    map<int, vector<int>>::const_iterator it = recursosPossuidosPorPID.find(pid); // Use const_iterator
    if (it != recursosPossuidosPorPID.end()) {
        return it->second; // Retorna uma cópia do vetor de IDs
    }
    return vector<int>(); // Retorna um vetor vazio se o PID não tiver recursos
}
