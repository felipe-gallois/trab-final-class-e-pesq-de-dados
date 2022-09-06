add_executable(
  teste-leitor
  teste-funcionalidades.cc
)

target_link_libraries(
  teste-leitor
  leitor-csv
)

target_include_directories(
  teste-leitor
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)

file(COPY arquivo-teste.csv DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")