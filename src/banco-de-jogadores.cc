#include "banco-de-jogadores.h"

#include <list>
#include <stdexcept>

BancoDeJogadores::BancoDeJogadores(int tamanho_tabela) {
  this->tamanho_tabela = tamanho_tabela;
  for (int i = 0; i < tamanho_tabela; i++) {
    tabela.push_back(std::list<InfoJogador>());
  }
}

void BancoDeJogadores::InsereJogador(Id id, Nome nome, std::vector<Posicao> posicoes) {
  tabela[CalculaHash(id)].push_back({id, nome, posicoes, 0, 0});  // TODO
}

InfoJogador BancoDeJogadores::PesquisaJogador(Id id) {
  std::list<InfoJogador>& lista_jogadores = tabela[CalculaHash(id)];
  for (auto& i : lista_jogadores) {
    if (i.id == id) return i; 
  }
  throw std::invalid_argument("Nao foi possivel encontrar jogador com id informado");
}

int BancoDeJogadores::CalculaHash(Id id) {
  return id % tamanho_tabela; 
}