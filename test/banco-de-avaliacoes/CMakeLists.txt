add_executable(
  teste-banco-avaliacoes
  teste-banco-avaliacoes.cc
)

target_link_libraries(
  teste-banco-avaliacoes
  banco-de-avaliacoes
)

target_include_directories(
  teste-banco-avaliacoes
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)