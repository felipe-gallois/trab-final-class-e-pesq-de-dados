#ifndef BANCO_DE_JOGADORES_H
#define BANCO_DE_JOGADORES_H

#include <string>
#include <list>
#include <vector>

typedef int Id;
typedef std::string Nome;
typedef std::string Posicao;
typedef int PontuacaoAcumulada;
typedef int NumeroAvaliacoes;

struct InfoJogador {
  Nome nome;
  std::vector<Posicao> posicoes;
  PontuacaoAcumulada pont_acumulada;
  NumeroAvaliacoes num_avaliacoes;
};

class BancoDeJogadores {
  public:
    BancoDeJogadores();
    ~BancoDeJogadores();
    void InsereJogador(Id id, Nome nome, std::vector<Posicao> posicoes);
    InfoJogador PesquisaJogador(Id id);
  private:
    int tamanho_tabela;
    std::list<InfoJogador>* ponteiro_tabela;
};

#endif