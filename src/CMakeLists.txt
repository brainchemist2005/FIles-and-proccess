add_library(core
  molecule.c
  molecule.h
  simulation.c
  simulation.h
  program.c
  program.h
  serialize.c
  serialize.h
)
target_link_libraries(core PUBLIC m)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(montecarlo montecarlo.c)
target_link_libraries(montecarlo PRIVATE core)

add_executable(autorestart autorestart.c)
