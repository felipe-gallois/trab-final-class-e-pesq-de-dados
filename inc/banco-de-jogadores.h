#ifndef BANCO_DE_JOGADORES_H
#define BANCO_DE_JOGADORES_H

#include "tipos.h"

#include <string>
#include <list>
#include <array>
#include <stdexcept>

struct InfoJogador {
  Id id;
  Nome nome;
  std::list<Posicao> posicoes;
  PontuacaoAcumulada pont_acumulada;
  NumeroAvaliacoes num_avaliacoes;
  std::list<Tag> tags;
  bool operator<(const InfoJogador&) const;
};

template <int tamanho>
class BancoDeJogadores {
  public:
    explicit BancoDeJogadores();
    void InsereJogador(Id id, Nome nome, std::list<Posicao> posicoes);
    InfoJogador PesquisaJogador(Id id);
    void AdicionaAvaliacao(Id id, Avaliacao avaliacao);
    void AdicionaTag(Id id, Tag tag);
    bool EncontrouTag(Id id, Tag& tag);
  private:
    std::array<std::list<InfoJogador>, tamanho> tabela;
    int CalculaHash(Id id);
};

template <int tamanho>
BancoDeJogadores<tamanho>::BancoDeJogadores() {
  if (tamanho < 1)
    throw std::invalid_argument("Tentou inicializar tabela com valor \
                                invalido");
  tabela.fill(std::list<InfoJogador>());
}

template <int tamanho>
void BancoDeJogadores<tamanho>::InsereJogador(Id id, Nome nome, std::list<Posicao> posicoes) {
  tabela[CalculaHash(id)].push_back({id, nome, posicoes, 0, 0});  // TODO
}

template <int tamanho>
InfoJogador BancoDeJogadores<tamanho>::PesquisaJogador(Id id) {
  std::list<InfoJogador>& lista_jogadores = tabela[CalculaHash(id)];
  for (auto& i : lista_jogadores) {
    if (i.id == id) return i;
  }
  return {0, "", {}, 0, 0};
}

template <int tamanho>
void BancoDeJogadores<tamanho>::AdicionaAvaliacao(Id id, Avaliacao avaliacao) {
  std::list<InfoJogador>& lista_jogadores = tabela[CalculaHash(id)];
  for (auto& i : lista_jogadores) {
    if (i.id == id) {
      i.pont_acumulada += avaliacao;
      i.num_avaliacoes++;
      return;
    }
  }
}

template <int tamanho>
void BancoDeJogadores<tamanho>::AdicionaTag(Id id, Tag tag) {
  std::list<InfoJogador>& lista_jogadores = tabela[CalculaHash(id)];
  for (auto& i : lista_jogadores) {
    if (i.id == id) {
      i.tags.push_back(tag);
      return;
    }
  }
}

template <int tamanho>
int BancoDeJogadores<tamanho>::CalculaHash(Id id) {
  return id % tamanho; 
}

template <int tamanho>
bool BancoDeJogadores<tamanho>::EncontrouTag(Id id, Tag& tag) {
  InfoJogador jogador = PesquisaJogador(id);
  if (jogador.id == 0)
    return false;
  for (auto& t : jogador.tags) {
    if (t == tag)
      return true;
  }
  return false;
}

#endif