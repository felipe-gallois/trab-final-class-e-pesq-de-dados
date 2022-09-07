#ifndef BANCO_DE_JOGADORES_H
#define BANCO_DE_JOGADORES_H

#include <string>
#include <list>
#include <array>
#include <stdexcept>

typedef int Id;
typedef std::string Nome;
typedef std::string Posicao;
typedef float PontuacaoAcumulada;
typedef int NumeroAvaliacoes;

struct InfoJogador {
  Id id;
  Nome nome;
  std::list<Posicao> posicoes;
  PontuacaoAcumulada pont_acumulada;
  NumeroAvaliacoes num_avaliacoes;
};

template <int tamanho>
class BancoDeJogadores {
  public:
    explicit BancoDeJogadores();
    void InsereJogador(Id id, Nome nome, std::list<Posicao> posicoes);
    InfoJogador PesquisaJogador(Id id);
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
  tabela[CalculaHash(id)].push_back({id, nome, posicoes, 5, 1});  // TODO
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
int BancoDeJogadores<tamanho>::CalculaHash(Id id) {
  return id % tamanho; 
}

#endif