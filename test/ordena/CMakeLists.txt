add_executable(
  teste-ordena
  teste-ordena.cc
)

target_include_directories(
  teste-ordena
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)