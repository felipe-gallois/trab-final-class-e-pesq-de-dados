#include "banco-de-avaliacoes.h"

bool InfoAvaliacao::operator<(const InfoAvaliacao& operando) const {
  return (nota < operando.nota);
}