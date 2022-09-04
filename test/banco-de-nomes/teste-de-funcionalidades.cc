#include "banco-de-nomes.h"

#include <iostream>
#include <stdexcept>

int main() {
  BancoDeNomes banco;

  banco.InsereNome("ter", 1); 
  banco.InsereNome("termo", 2); 
  banco.InsereNome("teremos", 3); 
  banco.InsereNome("terminar", 4);

  std::vector<Id> pesquisas;

  try {
    pesquisas = banco.PesquisaPrefixo("ter");
    for (auto& id : pesquisas)
      std::cout << id << " ";
    std::cout << std::endl;

    pesquisas = banco.PesquisaPrefixo("termo");
    for (auto& id : pesquisas)
      std::cout << id << " ";
    std::cout << std::endl;

    pesquisas = banco.PesquisaPrefixo("teremos");
    for (auto& id : pesquisas)
      std::cout << id << " ";
    std::cout << std::endl;

    pesquisas = banco.PesquisaPrefixo("terminar");
    for (auto& id : pesquisas)
      std::cout << id << " ";
    std::cout << std::endl;
  } catch (std::exception& erro) {
    std::cout << "Erro: " << erro.what() << std::endl;
  }
  
  return 0;
}