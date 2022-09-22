add_executable(
  teste-funcionalidades
  teste-funcionalidades.cc
)

target_link_libraries(
  teste-funcionalidades
  banco-de-jogadores
)

target_include_directories(
  teste-funcionalidades
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)

add_executable(
  teste-de-estresse
  teste-de-estresse.cc
)

target_link_libraries(
  teste-de-estresse
  banco-de-jogadores
)

target_include_directories(
  teste-de-estresse
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)