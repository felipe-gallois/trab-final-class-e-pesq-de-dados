#include "banco-de-avaliacoes.h"

#include <iostream>

void ImprimeInfo(InfoUsuario& info) {
  std::cout << "Id:" << info.id_usuario << std::endl;
  for (auto& i : info.avaliacoes)
    std::cout << "  " << "Jogador:" << i.id_jogador << " Nota:" << i.nota
              << std::endl;
}

int main() {
  BancoDeAvaliacoes<5> banco;

  InfoUsuario info;

  info = banco.PesquisaUsuario(1);
  ImprimeInfo(info);

  banco.InsereAvaliacao(1, 1, 5);
  banco.InsereAvaliacao(1, 2, 3);

  info = banco.PesquisaUsuario(1);
  ImprimeInfo(info);

  banco.InsereAvaliacao(2, 1, 2);
  banco.InsereAvaliacao(3, 2, 2.5);
  banco.InsereAvaliacao(3, 3, 3);
  banco.InsereAvaliacao(3, 4, 1);
  banco.InsereAvaliacao(3, 5, 5);
  banco.InsereAvaliacao(3, 6, 4);
  banco.InsereAvaliacao(3, 7, 4.5);
  banco.InsereAvaliacao(3, 8, 5);

  info = banco.PesquisaUsuario(3);
  ImprimeInfo(info);

  return 0;
}