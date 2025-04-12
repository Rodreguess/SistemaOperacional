#include "Processo.h"
// aqui vao ficar os getters e setters

Processo::Processo() {};

void Processo::setPID(int p){
	pid = p;
}

void Processo::setEstado(string e) { 
	estado_do_processo = e;
}

void Processo::setPrioridade(int prio) {
	prioridade = prio;
}

int Processo::getPID() {
	return pid;
}

string Processo::getEstado() {
	return estado_do_processo;
}

int Processo::getPrioridade() {
	return prioridade;
}