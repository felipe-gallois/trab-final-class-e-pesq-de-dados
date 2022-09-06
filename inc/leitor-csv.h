#ifndef LEITOR_CSV_H_
#define LEITOR_CSV_H_

#include <string>
#include <list>
#include <fstream>

class LeitorCSV {
  public:
    explicit LeitorCSV(const char* nome_do_arquivo);
    void LeLinha();
    void Copia(int coluna, std::string& destino);
    void CopiaLista(int coluna, std::list<std::string>& destino);
    bool FimDoArquivo();
  private:
    bool fim_do_arquivo;
    std::ifstream entrada;
    std::string linha;
    std::list<std::string> colunas;
    void SeparaColunas(std::string& linha, std::list<std::string>& destino);
};

#endif