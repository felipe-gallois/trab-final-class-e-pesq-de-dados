#include "leitor-csv.h"

#include "banco-de-jogadores.h"

#include <iostream>

int main() {
  LeitorCSV leitor("arquivo-teste.csv");

  /* sofifa_id,name,player_positions */
  std::string id;
  std::string nome;
  std::list<std::string> posicoes;
  while (!leitor.FimDoArquivo()) {
    leitor.LeLinha();
    leitor.Copia(0, id);
    leitor.Copia(1, nome);
    leitor.CopiaLista(2, posicoes);
    std::cout << id << "  " << nome << "  ";
    for (auto& i : posicoes)
      std::cout << i << "  ";
    std::cout << std::endl;
  }

  return 0;
}