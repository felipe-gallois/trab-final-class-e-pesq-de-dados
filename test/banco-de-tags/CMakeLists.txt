add_executable(
  teste-banco-tags
  teste-banco-tags.cc
)

target_link_libraries(
  teste-banco-tags
  banco-de-tags
)

target_include_directories(
  teste-banco-tags
  PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)