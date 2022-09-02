#include "banco-de-jogadores.h"

#include <iostream>

int main() {
  BancoDeJogadores banco(10000);

  std::cout << "Estrutura de dados criada!" << std::endl;

  for (int i = 0; i < 1000000; i++)
    banco.InsereJogador(i, "Nome", {"AT", "ZG", "GL"});

  std::cout << "Jogadores inseridos!" << std::endl;

  for (int i = 999999; i >= 0; i--)
    banco.PesquisaJogador(i);

  std::cout << "Jogadores pesquisados!" << std::endl;

  return 0;
}