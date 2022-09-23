#include "banco-de-jogadores.h"
#include "banco-de-nomes.h"
#include "leitor-csv.h"
#include "banco-de-avaliacoes.h"
#include "banco-de-posicoes.h"
#include "banco-de-tags.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cctype>
#include <iomanip>
#include <cstdlib>

static const int kMaxImpressoesPlayer = 10;
static const int kMaxImpressoesUser = 20;

static const char kArquivoJogadores[] = ".\\players.csv";
static const char kArquivoAvaliacoes[] = ".\\rating.csv";
static const char kArquivoTags[] = ".\\tags.csv";

/* Configurações do Banco de Dados */
struct BancoDeDados {
  BancoDeJogadores<20000> jogadores;
  BancoDeNomes nomes;
  BancoDeAvaliacoes<20000> avaliacoes;
  BancoDePosicoes posicoes;
  BancoDeTags tags;
};

std::string GeraCaminhoJogadores(char*& diretorio) {
  std::string caminho(diretorio);
  caminho += kArquivoJogadores;
  return caminho;
}

std::string GeraCaminhoAvaliacoes(char*& diretorio) {
  std::string caminho(diretorio);
  caminho += kArquivoAvaliacoes;
  return caminho;
}

std::string GeraCaminhoTags(char*& diretorio) {
  std::string caminho(diretorio);
  caminho += kArquivoTags;
  return caminho;
}

void SeparaArgumentos(char* comando_char,
                      std::vector<std::string>& argumentos) {
  std::string comando(comando_char);
  size_t posicao;
  argumentos.clear();
  while (!comando.empty()) {
    if (comando[0] == '\'') {
      posicao = comando.find('\'', 1);
      argumentos.push_back(comando.substr(1, posicao - 1));
      comando.erase(0, posicao + 2);  // Apaga também a vírgula
    } else if (comando[0] == '\"') {
      posicao = comando.find('\"', 1);
      argumentos.push_back(comando.substr(1, posicao - 1));
      comando.erase(0, posicao + 2);  // Apaga também a vírgula
    } else {
      posicao = comando.find(' ');
      if (posicao == std::string::npos) {
        argumentos.push_back(comando);
        comando.clear();
      } else {
        argumentos.push_back(comando.substr(0, posicao));
        comando.erase(0, posicao + 1);
      }
    }
  }
}

void CarregaJogadores(char*& diretorio_fonte, BancoDeDados& banco_de_dados) {
  LeitorCSV leitor_jogadores(GeraCaminhoJogadores(diretorio_fonte).c_str());

  /* Linha: [sofifa_id], [name], [player_positions] */
  std::string id;
  std::string nome;
  std::list<std::string> posicoes;
  while (!leitor_jogadores.FimDoArquivo()) {
    leitor_jogadores.LeLinha();
    leitor_jogadores.Copia(0, id);
    leitor_jogadores.Copia(1, nome);
    leitor_jogadores.CopiaLista(2, posicoes);
    banco_de_dados.jogadores.InsereJogador(std::stoi(id), nome, posicoes);
    for (auto& c : nome)
      c = tolower(c);
    banco_de_dados.nomes.InsereNome(nome, std::stoi(id));
    banco_de_dados.posicoes.AdicionaJogador(std::stoi(id), posicoes);
  }
}

void CarregaAvaliacoes(char*& diretorio_fonte, BancoDeDados& banco_de_dados) {
  LeitorCSV leitor_avaliacoes(GeraCaminhoAvaliacoes(diretorio_fonte).c_str());

  /* Linha: [user_id], [sofifa_id], [rating] */
  std::string id_usuario;
  std::string id_jogador;
  std::string avaliacao;
  while (!leitor_avaliacoes.FimDoArquivo()) {
    leitor_avaliacoes.LeLinha();
    leitor_avaliacoes.Copia(0, id_usuario);
    leitor_avaliacoes.Copia(1, id_jogador);
    leitor_avaliacoes.Copia(2, avaliacao);
    banco_de_dados.avaliacoes.InsereAvaliacao(std::stoi(id_usuario),
                                              std::stoi(id_jogador),
                                              std::stof(avaliacao));
    banco_de_dados.jogadores.AdicionaAvaliacao(std::stoi(id_jogador),
                                               std::stof(avaliacao));
  }
}

void CarregaTags(char*& diretorio_fonte, BancoDeDados& banco_de_dados) {
  LeitorCSV leitor_tags(GeraCaminhoTags(diretorio_fonte).c_str());

  /* Linha: [user_id], [sofifa_id], [tag] */
  std::string id_jogador;
  std::string tag;
  while (!leitor_tags.FimDoArquivo()) {
    leitor_tags.LeLinha();
    leitor_tags.Copia(1, id_jogador);
    leitor_tags.Copia(2, tag);

    if (!tag.empty()) {
      banco_de_dados.tags.InsereTag(tag, std::stoi(id_jogador));
      banco_de_dados.jogadores.AdicionaTag(std::stoi(id_jogador), tag);
    }
  }
}

void CarregaInformacoes(char*& diretorio_fonte, BancoDeDados& banco_de_dados) {
  CarregaJogadores(diretorio_fonte, banco_de_dados);
  CarregaAvaliacoes(diretorio_fonte, banco_de_dados);
  CarregaTags(diretorio_fonte, banco_de_dados);
}

void ImprimeCabecalhoJogador() {
  std::cout << std::setw(8) << std::left << "Id"
            << std::setw(46) << std::left << "Nome"
            << std::setw(13) << std::left << "Posicoes"
            << std::setw(8) << std::left << "Rating"
            << std::setw(10) << std::left << "Num. Aval."
            << std::endl;
}

void ImprimeJogador(InfoJogador& info) {
  std::cout << std::setw(8) << std::left << info.id
            << std::setw(46) << std::left << info.nome;
  std::string posicoes;
  for (auto& posicao : info.posicoes) {
    posicoes.append(posicao);
    posicoes.append(" ");
  }
  std::cout << std::setw(13) << std::left << posicoes
            << std::setw(8) << std::left << std::setprecision(2) << std::fixed
            << info.pont_acumulada / (float) info.num_avaliacoes
            << std::setw(10) << std::left << info.num_avaliacoes
            << std::endl;
}

void ImprimeCabecalhoAvaliacao() {
  std::cout << std::setw(8) << std::left << "Id"
            << std::setw(46) << std::left << "Nome"
            << std::setw(8) << std::left << "Rating"
            << std::setw(12) << std::left << "Num. Aval."
            << std::setw(9) << std::left << "Avaliacao"
            << std::endl;
}

void ImprimeAvaliacao(InfoJogador& info_jogador,
                      InfoAvaliacao& info_avaliacao) {
  std::cout << std::setw(8) << std::left << info_jogador.id
            << std::setw(46) << std::left << info_jogador.nome
            << std::setw(8) << std::left << std::setprecision(2) << std::fixed
            << info_jogador.pont_acumulada /
               (float) info_jogador.num_avaliacoes
            << std::setw(12) << std::left << info_jogador.num_avaliacoes
            << std::setw(9) << std::left << std::setprecision(2) << std::fixed
            << info_avaliacao.nota
            << std::endl;
}

bool EncontrouTag(Tag& tag, std::list<Tag>& lista_tags) {
  for (auto& t : lista_tags) {
    if (t == tag)
      return true;
  }
  return false;
}

void ExecutaComandoPlayer(std::vector<std::string>& argumentos,
                          BancoDeDados& banco_de_dados) {
  ImprimeCabecalhoJogador();
  std::vector<Id> id_jogadores =
      banco_de_dados.nomes.PesquisaPrefixo(argumentos[1]);
  if (id_jogadores.size() > kMaxImpressoesPlayer)  // Máximo de jogadores
    id_jogadores.erase(id_jogadores.begin() + kMaxImpressoesPlayer,
                       id_jogadores.end());
  InfoJogador info;
  for (auto& id : id_jogadores) {
    info = banco_de_dados.jogadores.PesquisaJogador(id);
    ImprimeJogador(info);    
  }
}

void ExecutaComandoUser(std::vector<std::string>& argumentos,
                          BancoDeDados& banco_de_dados) {
  ImprimeCabecalhoAvaliacao();
  InfoUsuario usuario =
      banco_de_dados.avaliacoes.PesquisaUsuario(std::stoi(argumentos[1]));
  auto iterador = usuario.avaliacoes.rbegin();
  InfoJogador jogador;
  InfoAvaliacao avaliacao;
  for (int contador = 0; contador < kMaxImpressoesUser; contador++) {
    if (iterador != usuario.avaliacoes.rend()) {
      jogador = banco_de_dados.jogadores.PesquisaJogador(iterador->id_jogador);
      avaliacao = *iterador;
      ImprimeAvaliacao(jogador, avaliacao);
      iterador++;
    } else {
      return;
    }
  }
}

void ExecutaComandoTags(std::vector<std::string>& argumentos,
                          BancoDeDados& banco_de_dados) {
  if (argumentos.size() < 2)
    throw std::invalid_argument("Argumentos insuficientes");
  std::list<Id> lista_jogadores =
      banco_de_dados.tags.PesquisaTag(argumentos[1]);
  lista_jogadores.sort();
  lista_jogadores.unique();
  std::list<Id> lista_auxiliar = lista_jogadores;
  for (auto& jogador : lista_jogadores) {
    for (int i = 2; i < argumentos.size(); i++) {
      if (!banco_de_dados.jogadores.EncontrouTag(jogador, argumentos[i])) {
        lista_auxiliar.remove(jogador);
        break;
      }
    }
  }
  ImprimeCabecalhoJogador();
  InfoJogador info_jogador;
  for (auto& jogador : lista_auxiliar) {
    info_jogador = banco_de_dados.jogadores.PesquisaJogador(jogador);
    ImprimeJogador(info_jogador);
  }
}

void ExecutaComandoTopN(std::vector<std::string>& argumentos,
                          BancoDeDados& banco_de_dados) {
  int numero_jogadores = std::stoi(argumentos[0].substr(3));
  if (numero_jogadores < 1)
    throw std::invalid_argument("O comando topn recebeu numero invalido de \
                                jogadores");
  JogadoresDaPosicao id_jogadores =
      banco_de_dados.posicoes.PesquisaPosicao(argumentos[1]);
  InfoJogador jogador;
  std::list<InfoJogador> lista_jogadores;
  for (auto& i : id_jogadores.lista_de_jogadores) {
    jogador = banco_de_dados.jogadores.PesquisaJogador(i);
    if (jogador.num_avaliacoes >= 1000)
      lista_jogadores.push_back(jogador);
  }
  lista_jogadores.sort();
  ImprimeCabecalhoJogador();
  auto iterador = lista_jogadores.rbegin();
  for (int i = 0; i < numero_jogadores; i++) {
    if (iterador != lista_jogadores.rend()) {
      ImprimeJogador(*iterador);
      iterador++;
    } else {
      return;
    }
  }
}

bool ExecutaComando(std::vector<std::string>& argumentos,
                    BancoDeDados& banco_de_dados) {
  if (argumentos[0] == "q") {
    return true;
  } else if (argumentos[0] == "player") {
    ExecutaComandoPlayer(argumentos, banco_de_dados);
  } else if (argumentos[0] == "user") {
    ExecutaComandoUser(argumentos, banco_de_dados);
  } else if (argumentos[0] == "tags") {
    ExecutaComandoTags(argumentos, banco_de_dados);  
  } else if (argumentos[0].compare(0, 3, "top") == 0) {
    ExecutaComandoTopN(argumentos, banco_de_dados);
  } else {
    std::cout << "Comando nao reconhecido. Por favor, tente novamente."
              << std::endl;
  }
  return false;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Uso: trab <diretorio-com-entradas>" << std::endl;
    exit(EXIT_FAILURE);
  }

  BancoDeDados banco_de_dados;

  std::cout << "Carregando..." << std::endl;

  CarregaInformacoes(argv[1], banco_de_dados);

  /* Entra em modo console */
  bool fim = false;
  char comando[256];
  std::vector<std::string> argumentos;
  argumentos.reserve(1);  // Evita acessar posicao proibida
  while (!fim) {
    std::cout << "$ ";
    std::cin.getline(comando, 256);
    try {
      SeparaArgumentos(comando, argumentos);
      fim = ExecutaComando(argumentos, banco_de_dados);
    } catch(...) {
      std::cout << "Comando invalido." << std::endl;
    }
  }

  _Exit(EXIT_SUCCESS);
}