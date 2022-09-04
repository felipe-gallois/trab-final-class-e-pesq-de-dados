#include "banco-de-nomes.h"

#include <iostream>
#include <stdexcept>

int main() {
  BancoDeNomes banco;

  banco.InsereNome("ter", 1); 
  banco.InsereNome("termo", 2); 
  banco.InsereNome("teremos", 3); 
  banco.InsereNome("terminar", 4); 

  try {
    if (banco.PesquisaNome("termo") == 2)
      std::cout << "Pesquisa 1 correta" << std::endl;

    if (banco.PesquisaNome("ter") == 1)
      std::cout << "Pesquisa 2 correta" << std::endl;
      
    if (banco.PesquisaNome("teremos") == 3)
      std::cout << "Pesquisa 3 correta" << std::endl;

    if (banco.PesquisaNome("terminar") == 4)
      std::cout << "Pesquisa 4 correta" << std::endl;
  } catch (std::exception& erro) {
    std::cout << "Erro: " << erro.what() << std::endl;
  }
  
  return 0;
}