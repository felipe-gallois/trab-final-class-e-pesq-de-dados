#include "banco-de-tags.h"

BancoDeTags::BancoDeTags() {
  base = nullptr;
}

BancoDeTags::~BancoDeTags() {
  delete base;
}

void BancoDeTags::InsereTag(Tag tag, Id id) {
  Letra** iterador = &base;
  int posicao = 0;
  for (auto& c : tag) {
    /* Se desloca lateralmente pela árvore até encontrar caractere ou nullptr */
    while (*iterador != nullptr && (*iterador)->caractere != c) {
      if ((*iterador)->caractere > c) {
        iterador = &((*iterador)->esquerda);
      } else {
        iterador = &((*iterador)->direita);
      }
    }
    /* Caso tenha encontrado nullptr... */
    if (*iterador == nullptr) {
      InsereRestante(tag, posicao, id, iterador);
      return;
    /* Caso tenha encontrado caractere... */
    } else {
      if (posicao < tag.size() - 1)
        iterador = &((*iterador)->proxima);
      posicao++;
    }
  }
  (*iterador)->lista_ids.push_back(id);
}

std::list<Id> BancoDeTags::PesquisaTag(Tag tag) {
  Letra* iterador = base;
  int posicao = 0;
  for (auto& c : tag) {
    /* Se desloca lateralmente pela árvore até encontrar caractere ou nullptr */
    while (iterador != nullptr && iterador->caractere != c) {
      if (iterador->caractere > c) {
        iterador = iterador->esquerda;
      } else {
        iterador = iterador->direita;
      }
    }
    /* Caso tenha encontrado nullptr... */
    if (iterador == nullptr)
      break;
    /* Caso tenha encontrado caractere... */
    if (posicao == tag.size() - 1)
      return iterador->lista_ids;
    iterador = iterador->proxima;
    posicao++;
  }
  return {};
}

void BancoDeTags::InsereRestante(Tag& tag, int posicao, int& id,
                                  BancoDeTags::Letra** destino) {
  for (posicao; posicao < tag.size(); posicao++) {
    *destino = new Letra;
    (*destino)->caractere = tag[posicao];

    if (posicao == tag.size() - 1)
      (*destino)->lista_ids.push_back(id);

    (*destino)->proxima = nullptr;
    (*destino)->esquerda = nullptr;
    (*destino)->direita = nullptr;
    destino = &((*destino)->proxima);
  }
}

BancoDeTags::Letra::~Letra() {
  delete proxima;
  delete esquerda;
  delete direita;
}