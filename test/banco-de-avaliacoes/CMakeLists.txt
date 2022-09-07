add_executable(
  teste-banco-avaliacoes
  teste-banco-avaliacoes.cc
)

target_include_directories(
  teste-banco-avaliacoes
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)