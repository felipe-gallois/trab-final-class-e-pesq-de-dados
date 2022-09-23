#ifndef BANCO_DE_TAGS_H_
#define BANCO_DE_TAGS_H_

#include "tipos.h"

#include <string>
#include <list>

class BancoDeTags {
  public:
    BancoDeTags();
    ~BancoDeTags();
    void InsereTag(Tag tag, Id id);
    std::list<Id> PesquisaTag(Tag tag);
  private:
    class Letra {
      public:
        ~Letra();
        char caractere;
        std::list<Id> lista_ids;
        Letra* esquerda;
        Letra* direita;
        Letra* proxima;
    };
    Letra* base; 
    void InsereRestante(Tag& tag, int posicao, int& id,
                        Letra** destino);
};

#endif