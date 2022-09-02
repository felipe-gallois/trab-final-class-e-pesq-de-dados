add_library(
  banco-de-jogadores
  banco-de-jogadores.cc
)

target_include_directories(
  banco-de-jogadores
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)