#include "banco-de-jogadores.h"

#include <stdexcept>
#include <iostream>

void ImprimeInfo(InfoJogador& info) {
  std::cout << "Id:" << info.id << " Nome:" << info.nome << " Posicoes:";
  for (auto& i : info.posicoes)
    std::cout << i << ",";
  std::cout << " Pont. Acumulada:" << info.pont_acumulada << " Num. Avaliacoes:" << info.num_avaliacoes << std::endl;  
}

int main() {
  BancoDeJogadores banco(5);

  banco.InsereJogador(10, "Nome 1", {"AT", "GL"});
  banco.InsereJogador(11, "Nome 2", {"ZG"});
  banco.InsereJogador(22, "Nome 3", {"MLE"});
  banco.InsereJogador(34, "Nome 4", {"MLG", "MLD", "PT"});

  InfoJogador info;
  try {
    info = banco.PesquisaJogador(10);
    ImprimeInfo(info);
    info = banco.PesquisaJogador(11);
    ImprimeInfo(info);
    info = banco.PesquisaJogador(22);
    ImprimeInfo(info);
    info = banco.PesquisaJogador(34);
    ImprimeInfo(info);
    info = banco.PesquisaJogador(35);
    ImprimeInfo(info);
  } catch(std::exception& erro) {
    std::cout << "Mensagem de erro: " << erro.what();
  }

  return 0;
}