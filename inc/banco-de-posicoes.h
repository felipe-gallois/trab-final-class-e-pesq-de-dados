#ifndef BANCO_DE_POSICOES_H_
#define BANCO_DE_POSICOES_H_

#include "typedefs.h"

#include <list>

struct JogadoresDaPosicao {
  Posicao nome;
  std::list<Id> lista_de_jogadores;
};

class BancoDePosicoes {
  public:
    void AdicionaJogador(Id id_jogador, std::list<Posicao> posicoes);
    JogadoresDaPosicao PesquisaPosicao(Posicao posicao);
  private:
    std::list<JogadoresDaPosicao> lista_de_posicoes;
    void AdicionaEmPosicao(Id& id_jogador, Posicao& posicao);
};

#endif