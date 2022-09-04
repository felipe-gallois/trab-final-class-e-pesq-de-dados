#include "banco-de-nomes.h"

#include <stdexcept>

BancoDeNomes::BancoDeNomes() {
  base = nullptr;
}

BancoDeNomes::~BancoDeNomes() {
  delete base;
}

void BancoDeNomes::InsereNome(std::string nome, Id id) {
  Letra** iterador = &base;
  int posicao = 0;
  for (auto& c : nome) {
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
      InsereRestante(nome, posicao, id, iterador);
      return;
    /* Caso tenha encontrado caractere... */
    } else {
      iterador = &((*iterador)->proxima);
      posicao++;
    }
  }
}

Id BancoDeNomes::PesquisaNome(std::string nome) {
  Letra* iterador = base;
  Id resultado;
  for (auto& c : nome) {
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
      throw std::invalid_argument("Nao foi possivel encontrar nome no banco de \
                                   nomes");
    /* Caso tenha encontrado caractere... */
    resultado = iterador->id;
    iterador = iterador->proxima;
  }
  return resultado;
}

void BancoDeNomes::InsereRestante(std::string& nome, int posicao, int& id,
                                  BancoDeNomes::Letra** destino) {
  for (posicao; posicao < nome.size(); posicao++) {
    *destino = new Letra;
    (*destino)->caractere = nome[posicao];
    (*destino)->id = (posicao == nome.size() - 1) ? id : 0;
    (*destino)->proxima = nullptr;
    (*destino)->esquerda = nullptr;
    (*destino)->direita = nullptr;
    destino = &((*destino)->proxima);
  }
}

BancoDeNomes::Letra::~Letra() {
  delete proxima;
  delete esquerda;
  delete direita;
}