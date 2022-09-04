#ifndef BANCO_DE_NOMES_H_
#define BANCO_DE_NOMES_H_

#include "banco-de-jogadores.h"

#include <string>

class BancoDeNomes {
  public:
    BancoDeNomes();
    ~BancoDeNomes();
    void InsereNome(std::string nome, Id id);
    Id PesquisaNome(std::string nome);
  private:
    class Letra {
      public:
        ~Letra();
        char caractere;
        Id id;
        Letra* esquerda;
        Letra* direita;
        Letra* proxima;
    };
    Letra* base; 
    void InsereRestante(std::string& nome, int posicao, int& id,
                        Letra** destino);
};

#endif