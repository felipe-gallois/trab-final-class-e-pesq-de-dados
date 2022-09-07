#include "banco-de-avaliacoes.h"

#include <iostream>

int main() {
  BancoDeAvaliacoes<5> banco;

  InfoUsuario info;

  info = banco.PesquisaUsuario(1);
  std::cout << "Id:" << info.id_usuario << std::endl;
  for (auto& i : info.avaliacoes)
    std::cout << "\t" << "Jogador:" << i.id_jogador << " Nota:" << i.nota
              << std::endl;

  banco.InsereAvaliacao(1, 1, 5);
  banco.InsereAvaliacao(1, 2, 3);

  info = banco.PesquisaUsuario(1);
  std::cout << "Id:" << info.id_usuario << std::endl;
  for (auto& i : info.avaliacoes)
    std::cout << "  " << "Jogador:" << i.id_jogador << " Nota:" << i.nota
              << std::endl;

  banco.InsereAvaliacao(2, 1, 2);
  banco.InsereAvaliacao(3, 2, 5);

  info = banco.PesquisaUsuario(3);
  std::cout << "Id:" << info.id_usuario << std::endl;
  for (auto& i : info.avaliacoes)
    std::cout << "  " << "Jogador:" << i.id_jogador << " Nota:" << i.nota
              << std::endl;

  return 0;
}