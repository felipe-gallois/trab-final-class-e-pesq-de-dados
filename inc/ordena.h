#ifndef ORDENA_H_
#define ORDENA_H_

#include <list>
#include <vector>

template <typename Tipo>
inline void TrocaElementos(Tipo& primeiro, Tipo& segundo) {
  Tipo auxiliar;
  auxiliar = segundo;
  segundo = primeiro;
  primeiro = auxiliar;
}

template <typename Tipo>
void ParticionaSubvetor(std::vector<Tipo>& vetor, int inicio, int fim) {
  int media = (inicio + fim) / 2;
  if (vetor[media] < vetor[inicio])
    TrocaElementos(vetor[media], vetor[inicio]);
  if (vetor[fim] < vetor[media]) {
    TrocaElementos(vetor[fim], vetor[media]);
    if (vetor[media] < vetor[inicio])
      TrocaElementos(vetor[media], vetor[inicio]);
  }
  TrocaElementos(vetor[inicio], vetor[media]);
}

template <typename Tipo>
int OrdenaSubvetor(std::vector<Tipo>& vetor, int inicio, int fim) {
  int marcador = inicio;
  for (int pos = inicio + 1; pos <= fim; ++pos) {
    if (vetor[pos] < vetor[inicio]) {
      if (pos != marcador + 1)
        TrocaElementos(vetor[marcador + 1], vetor[pos]);
      marcador++;
    }
  }
  TrocaElementos(vetor[inicio], vetor[marcador]);
  return marcador;
}

template <typename Tipo>
void OrdenaParcial(std::vector<Tipo>& vetor, int inicio, int fim) {
  int posicao_particionador;
  if (fim - inicio < 1 || fim > vetor.size() - 1) {
    return;
  } else if (fim - inicio == 1) {
    if (vetor[fim] < vetor[inicio]) {
      TrocaElementos(vetor[inicio], vetor[fim]);
    }
    return;
  } else {
    ParticionaSubvetor(vetor, inicio, fim);
    posicao_particionador = OrdenaSubvetor(vetor, inicio, fim);
  }
  OrdenaParcial(vetor, inicio, posicao_particionador - 1);
  OrdenaParcial(vetor, posicao_particionador + 1, fim);
}

template <typename Tipo>
void OrdenaLista(std::list<Tipo>& lista) {
  std::vector<Tipo> vetor;
  for (auto& i : lista)
    vetor.push_back(i);
  OrdenaParcial(vetor, 0, vetor.size() - 1);
  auto it = lista.begin();
  for (auto& i : vetor) {
    *it = i;
    it++;
  }
}

#endif