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

std::vector<Id> BancoDeNomes::PesquisaPrefixo(std::string nome) {
  Letra* iterador = base;
  std::vector<Id> coletor;
  int posicao = 0;
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
    if (posicao == nome.size() - 1 && iterador->id != 0)
      coletor.push_back(iterador->id);  // Coleta caso prefixo = nome completo
    iterador = iterador->proxima;
    posicao++;
  }
  ColetaNomes(iterador, coletor);
  return coletor;
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

void BancoDeNomes::ColetaNomes(Letra* iterador, std::vector<Id>& coletor) {
  if (iterador != nullptr) {
    if (iterador->id != 0)
      coletor.push_back(iterador->id);
    ColetaNomes(iterador->proxima, coletor);
    ColetaNomes(iterador->esquerda, coletor);
    ColetaNomes(iterador->direita, coletor);
  }
}

BancoDeNomes::Letra::~Letra() {
  delete proxima;
  delete esquerda;
  delete direita;
}