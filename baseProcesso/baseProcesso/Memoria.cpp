#include "Memoria.h"

Memoria::Memoria(int totalKB) :
    tamanhoTotalKB(totalKB),
    memoriaLivreKB(totalKB) {
    cout << "Memoria inicializada com " << tamanhoTotalKB << "KB." << endl;
}

bool Memoria::alocar(int pid, int tamanhoKB) {
    if (tamanhoKB <= 0) {
        cout << "Erro: Tamanho de memoria para alocacao deve ser positivo." << endl;
        return false;
    }
    if (memoriaLivreKB >= tamanhoKB) {
        memoriaLivreKB -= tamanhoKB;
        alocacoesPorPID[pid] += tamanhoKB; // Adiciona ao que o PID já alocou
        cout << "Memoria: " << tamanhoKB << "KB alocados para PID " << pid
            << ". Memoria livre: " << memoriaLivreKB << "KB." << endl;
        return true;
    }
    else {
        cout << "Memoria: Falha ao alocar " << tamanhoKB << "KB para PID " << pid
            << ". Memoria livre insuficiente (" << memoriaLivreKB << "KB)." << endl;
        return false;
    }
}

void Memoria::desalocar(int pid, int tamanhoKB) {
    if (tamanhoKB <= 0) {
        cout << "Erro: Tamanho de memoria para desalocacao deve ser positivo." << endl;
        return;
    }
    // Verifica se o PID realmente tinha essa quantidade ou mais alocada
    if (alocacoesPorPID.count(pid) && alocacoesPorPID[pid] >= tamanhoKB) {
        memoriaLivreKB += tamanhoKB;
        alocacoesPorPID[pid] -= tamanhoKB;
        if (alocacoesPorPID[pid] == 0) {
            alocacoesPorPID.erase(pid); // Remove a entrada se não houver mais alocação para este PID
        }
        cout << "Memoria: " << tamanhoKB << "KB desalocados do PID " << pid
            << ". Memoria livre: " << memoriaLivreKB << "KB." << endl;
    }
    else {
        cout << "Memoria: Tentativa de desalocar " << tamanhoKB << "KB do PID " << pid
            << ", mas nao estava alocado ou alocado menos que isso." << endl;
    }
}

int Memoria::getTamanhoTotalKB()  {
    return tamanhoTotalKB;
}

int Memoria::getMemoriaLivreKB()  {
    return memoriaLivreKB;
}

int Memoria::getMemoriaOcupadaKB()  {
    return tamanhoTotalKB - memoriaLivreKB;
}

void Memoria::imprimirStatus()  {
    cout << "\n--- Status da Memoria ---" << endl;
    cout << "Total: " << tamanhoTotalKB << "KB" << endl;
    cout << "Livre: " << memoriaLivreKB << "KB" << endl;
    cout << "Ocupada: " << getMemoriaOcupadaKB() << "KB" << endl;
    if (!alocacoesPorPID.empty()) {
        cout << "Alocacoes por PID:" << endl;
        for ( auto& pair : alocacoesPorPID) {
            cout << "  PID " << pair.first << ": " << pair.second << "KB" << endl;
        }
    }
    else {
        cout << "Nenhuma memoria alocada por processos." << endl;
    }
    cout << "-------------------------" << endl;
}