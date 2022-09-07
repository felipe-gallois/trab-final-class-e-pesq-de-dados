#include "banco-de-jogadores.h"
#include "banco-de-nomes.h"
#include "leitor-csv.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cctype>
#include <iomanip>

static const int kMaxImpressoes = 10;

/* Configurações do Banco de Dados */
struct BancoDeDados {
  BancoDeJogadores<20000> jogadores;
  BancoDeNomes nomes;
};

std::string GeraCaminhoJogadores(char*& diretorio) {
  std::string caminho(diretorio);
  caminho += ".\\players.csv";
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

void CarregaInformacoes(char*& diretorio_fonte, BancoDeDados& banco_de_dados) {
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
  }
}

void ImprimeJogador(InfoJogador& info) {
  std::cout << std::setw(8) << std::left << info.id
            << std::setw(50) << std::left << info.nome;
  std::string posicoes;
  for (auto& posicao : info.posicoes) {
    posicoes.append(posicao);
    posicoes.append(" ");
  }
  std::cout << std::setw(16) << std::left << posicoes
            << std::setw(8) << std::left
            << (float) info.pont_acumulada / (float) info.num_avaliacoes
            << std::setw(8) << std::left << info.num_avaliacoes
            << std::endl;
}

void ExecutaComandoPlayer(std::vector<std::string>& argumentos,
                          BancoDeDados& banco_de_dados) {
  std::vector<Id> id_jogadores =
      banco_de_dados.nomes.PesquisaPrefixo(argumentos[1]);
  if (id_jogadores.size() > kMaxImpressoes)  // Máximo de jogadores
    id_jogadores.erase(id_jogadores.begin() + kMaxImpressoes,
                       id_jogadores.end());
  InfoJogador info;
  for (auto& id : id_jogadores) {
    info = banco_de_dados.jogadores.PesquisaJogador(id);
    ImprimeJogador(info);    
  }
}

bool ExecutaComando(std::vector<std::string>& argumentos,
                    BancoDeDados& banco_de_dados) {
  if (argumentos[0] == "q") {
    return true;
  } else if (argumentos[0] == "player") {
    ExecutaComandoPlayer(argumentos, banco_de_dados);
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

  return 0;
}