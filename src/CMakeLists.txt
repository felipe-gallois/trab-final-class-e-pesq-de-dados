add_library(
  banco-de-jogadores
  banco-de-jogadores.cc
)

target_include_directories(
  banco-de-jogadores
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)

add_library(
  banco-de-nomes
  banco-de-nomes.cc
)

target_include_directories(
  banco-de-nomes
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)