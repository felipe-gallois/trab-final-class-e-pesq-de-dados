add_executable(
  teste-funcionalidades
  teste-funcionalidades.cc
)

target_include_directories(
  teste-funcionalidades
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)

add_executable(
  teste-de-estresse
  teste-de-estresse.cc
)

target_include_directories(
  teste-de-estresse
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)