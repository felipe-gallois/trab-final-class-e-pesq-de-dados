#include "banco-de-posicoes.h"

#include <iostream>

void ImprimeLista(JogadoresDaPosicao& lista_jogadores) {
  for (auto& i : lista_jogadores.lista_de_jogadores)
    std::cout << i << ", ";
  std::cout << std::endl;
}

int main() {
  BancoDePosicoes banco;

  banco.AdicionaJogador(1, {"GL", "AT", "ZG"});
  banco.AdicionaJogador(2, {"AT", "MLE"});
  banco.AdicionaJogador(3, {"AT", "MLE"});

  JogadoresDaPosicao lista_jogadores;

  lista_jogadores = banco.PesquisaPosicao("GL");
  ImprimeLista(lista_jogadores);

  lista_jogadores = banco.PesquisaPosicao("MLE");
  ImprimeLista(lista_jogadores);

  lista_jogadores = banco.PesquisaPosicao("AT");
  ImprimeLista(lista_jogadores);

  return 0;
}