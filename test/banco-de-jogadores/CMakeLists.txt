add_executable(
  teste-funcionalidades
  teste-funcionalidades.cc
)

target_link_libraries(
  teste-funcionalidades
  banco-de-jogadores
)

add_executable(
  teste-de-estresse
  teste-de-estresse.cc
)

target_link_libraries(
  teste-de-estresse
  banco-de-jogadores
)