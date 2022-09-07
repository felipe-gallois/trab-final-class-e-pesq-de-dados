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

add_executable(
  trab
  programa.cc
)

target_link_libraries(
  trab
  banco-de-nomes
  leitor-csv
)

target_include_directories(
  trab
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)