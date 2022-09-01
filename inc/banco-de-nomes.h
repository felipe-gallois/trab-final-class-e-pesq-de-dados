#ifndef BANCO_DE_NOMES_H_
#define BANCO_DE_NOMES_H_

#include "banco-de-jogadores.h"

#include <list>
#include <string>

struct Letra {
  char caractere;
  Id id;
  Letra* proxima;
};

class BancoDeNomes {
  public:
    BancoDeNomes();
    ~BancoDeNomes();
    void InsereNome(std::string nome, Id id);
    Id PesquisaNome(std::string nome);
  private:
    std::list<Letra>* opcoes_de_letra;
};

#endif