#include "banco-de-jogadores.h"

bool InfoJogador::operator<(const InfoJogador& operando) const {
  return (pont_acumulada / (float) num_avaliacoes < operando.pont_acumulada / (float) operando.num_avaliacoes);
}