#ifndef BANCO_DE_AVALIACOES_H_
#define BANCO_DE_AVALIACOES_H_

#include "banco-de-jogadores.h"
#include "typedefs.h"

#include <list>
#include <array>
#include <stdexcept>

struct InfoAvaliacao {
  Id id_jogador;
  Avaliacao nota;
  bool operator<(const InfoAvaliacao&) const;
};

struct InfoUsuario {
  IdUsuario id_usuario;
  std::list<InfoAvaliacao> avaliacoes;
};

template <int tamanho>
class BancoDeAvaliacoes {
  public:
    explicit BancoDeAvaliacoes();
    void InsereAvaliacao(IdUsuario id_usuario, Id id_jogador, Avaliacao nota);
    InfoUsuario PesquisaUsuario(IdUsuario id_usuario);
  private:
    std::array<std::list<InfoUsuario>, tamanho> tabela;
    int CalculaHash(IdUsuario id_usuario);
};

template <int tamanho>
BancoDeAvaliacoes<tamanho>::BancoDeAvaliacoes() {
  if (tamanho < 1)
    throw std::invalid_argument("Tentou inicializar tabela com valor \
                                invalido");
  tabela.fill(std::list<InfoUsuario>());
}

template <int tamanho>
void BancoDeAvaliacoes<tamanho>
    ::InsereAvaliacao(IdUsuario id_usuario, Id id_jogador, Avaliacao nota) {
  std::list<InfoUsuario>& lista_usuarios = tabela[CalculaHash(id_usuario)];
  for (auto& i : lista_usuarios) {
    if (i.id_usuario == id_usuario) {
      i.avaliacoes.push_back({id_jogador, nota});
      return;
    }
  }
  lista_usuarios.push_back({id_usuario,
                            std::list<InfoAvaliacao>(1, {id_jogador, nota})});
}

template <int tamanho>
InfoUsuario BancoDeAvaliacoes<tamanho>
    ::PesquisaUsuario(IdUsuario id_usuario) {
  std::list<InfoUsuario>& lista_usuarios = tabela[CalculaHash(id_usuario)];
  for (auto& i : lista_usuarios) {
    if (i.id_usuario == id_usuario) {
      i.avaliacoes.sort();
      return i;
    }
  }
  return {0, {}};
}

template <int tamanho>
int BancoDeAvaliacoes<tamanho>::CalculaHash(IdUsuario id_usuario) {
  return id_usuario % tamanho; 
}

bool InfoAvaliacao::operator<(const InfoAvaliacao& operando) const {
  return (nota < operando.nota);
}

#endif