#include "ordena.h"

#include <cstdlib>
#include <iostream>
#include <time.h>

int main() {
  srand(time(NULL));

  std::list<int> lista;
  for (int i = 0; i < 20; i++) {
    lista.push_back(rand() % 100);
    std::cout << lista.back() << " ";
  }
  std::cout << std::endl;

  OrdenaLista(lista);

  for (auto& i : lista) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}