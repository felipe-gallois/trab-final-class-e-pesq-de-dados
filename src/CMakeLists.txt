add_library(
  banco-de-nomes
  banco-de-nomes.cc
)

target_include_directories(
  banco-de-nomes
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)

add_library(
  leitor-csv
  leitor-csv.cc
)

target_include_directories(
  leitor-csv
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)

add_library(
  banco-de-posicoes
  banco-de-posicoes.cc
)

target_include_directories(
  banco-de-posicoes
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)

add_library(
  banco-de-avaliacoes
  banco-de-avaliacoes.cc
)

target_include_directories(
  banco-de-avaliacoes
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)

add_library(
  banco-de-jogadores
  banco-de-jogadores.cc
)

target_include_directories(
  banco-de-jogadores
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)

add_executable(
  trab
  programa.cc
)

target_link_libraries(
  trab
  banco-de-nomes
  banco-de-posicoes
  banco-de-avaliacoes
  banco-de-jogadores
  leitor-csv
)

target_include_directories(
  trab
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)