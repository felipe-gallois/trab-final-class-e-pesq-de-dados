#include "banco-de-tags.h"

#include <list>
#include <iostream>

void PesquisaTag(Tag tag, BancoDeTags& banco) {
  std::list<Id> lista_ids = banco.PesquisaTag(tag);
  std::cout << tag << ": ";
  for (auto& i : lista_ids)
    std::cout << i << ",";
  std::cout << std::endl;
}

int main() {
  BancoDeTags banco;

  banco.InsereTag("bbb", 1);
  banco.InsereTag("bba", 2);
  banco.InsereTag("bbc", 3);
  banco.InsereTag("bbcb", 4);
  banco.InsereTag("bba", 5);
  banco.InsereTag("bbcb", 5);
  banco.InsereTag("bb", 6);
  
  PesquisaTag("bbb", banco);
  PesquisaTag("bba", banco);
  PesquisaTag("bbc", banco);
  PesquisaTag("bbcb", banco);
  PesquisaTag("bb", banco);
  PesquisaTag("b", banco);

  return 0;
}