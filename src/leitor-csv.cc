#include "leitor-csv.h"

#include <string>
#include <ios>
#include <iostream>
#include <list>

LeitorCSV::LeitorCSV(const char* nome_do_arquivo) {
  entrada.open(nome_do_arquivo);
  if (!entrada.is_open())
    throw std::ios_base::failure("Nao foi possivel abrir o arquivo fonte");
  LeLinha();  // Lê cabeçalhos automaticamente
}

void LeitorCSV::LeLinha() {
  std::getline(entrada, linha);
  colunas.clear();
  SeparaColunas(linha, colunas);
  fim_do_arquivo = entrada.eof();
}

void LeitorCSV::Copia(int coluna, std::string& destino) {
  if (colunas.size() > coluna && coluna >= 0) {
    auto iterador = colunas.begin();
    std::advance(iterador, coluna);
    destino = *iterador;
    return;
  } else {
    throw std::out_of_range("Tentou acessar posicao fora dos limites");
  }
}

void LeitorCSV::CopiaLista(int coluna, std::list<std::string>& destino) {
  Copia(coluna, linha);
  destino.clear();
  SeparaColunas(linha, destino);
}

bool LeitorCSV::FimDoArquivo() {
  return fim_do_arquivo;
}

void LeitorCSV::SeparaColunas(std::string& linha, std::list<std::string>& destino) {
  size_t posicao = 0;
  while (linha.size() != 0) {
    if (linha[0] == '\"') {
      posicao = linha.find("\"", 1);
      destino.push_back(linha.substr(1, posicao - 1));
      linha.erase(0, posicao + 2);  // Apaga também a vírgula
    } else {
      posicao = linha.find(",");
      destino.push_back(linha.substr(0, posicao));
      if (posicao == std::string::npos) {
        linha.clear();
      } else {
        if (linha[posicao + 1] == ' ') {
          linha.erase(0, posicao + 2);
        } else {
          linha.erase(0, posicao + 1);
        }
      }
    }
  }
}