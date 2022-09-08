#include "banco-de-posicoes.h"

#include <string>

void BancoDePosicoes::AdicionaJogador(Id id_jogador, std::list<Posicao> posicoes) {
  for (auto& posicao : posicoes)
    AdicionaEmPosicao(id_jogador, posicao);
}

JogadoresDaPosicao BancoDePosicoes::PesquisaPosicao(Posicao posicao) {
  for (auto& pos : lista_de_posicoes)
    if (pos.nome.compare(posicao) == 0)
      return pos;
}

void BancoDePosicoes::AdicionaEmPosicao(Id& id_jogador, Posicao& posicao) {
  for (auto& pos : lista_de_posicoes) {
    if (pos.nome.compare(posicao) == 0) {
      pos.lista_de_jogadores.push_back(id_jogador);
      return;
    }
  }
  lista_de_posicoes.push_back({posicao, std::list<Id>(1, id_jogador)});
}