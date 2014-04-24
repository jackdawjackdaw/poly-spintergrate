cmake_minimum_required(VERSION 2.6)

add_definitions("-m64 -O3 -Wall")

set(dynamics_sources
  dynamics-eom-54.c
  dynamics.c
  fixed-point-iter.c
  eom-fns.c
  ham-fns.c
  ham-all.c
)

set(config_sources
  find-config.c
  config-fns.c
)  

add_library(dynEomFull SHARED dynamics-eom-all)
install_targets(/lib dynEomFull)


add_executable(traj-54 compute-traj ${dynamics_sources} ${config_sources})
SET_TARGET_PROPERTIES(traj-54 PROPERTIES COMPILE_FLAGS -DSIMPLEMODE)
target_link_libraries(traj-54 dynEomFull)
add_dependencies(traj-54 dynEomFull)
install_targets( /bin traj-54)

add_executable(traj-full compute-traj ${dynamics_sources} ${config_sources})
target_link_libraries(traj-full dynEomFull)
add_dependencies(traj-full dynEomFull)
install_targets( /bin traj-full)

add_executable(test-config test-config ${config_sources} ${dynamics_sources})
target_link_libraries(test-config dynEomFull)
add_dependencies(test-config dynEomFull)
install_targets(/bin test-config)

add_executable(test-eom test-eom-all ${dynamics_sources} ${config_sources})
target_link_libraries(test-eom dynEomFull)
add_dependencies(test-eom dynEomFull)
install_targets(/bin test-eom)


