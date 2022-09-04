#ifndef BANCO_DE_NOMES_H_
#define BANCO_DE_NOMES_H_

#include "banco-de-jogadores.h"

#include <string>
#include <vector>

class BancoDeNomes {
  public:
    BancoDeNomes();
    ~BancoDeNomes();
    void InsereNome(std::string nome, Id id);
    std::vector<Id> PesquisaPrefixo(std::string nome);
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
    void ColetaNomes(Letra* iterador, std::vector<Id>& coletor);
};

#endif