cmake_minimum_required(VERSION 2.6)

add_definitions("-m64 -O3 -Wall")


set(dynamics_sources
  dynamics-eom-54.c
  dynamics.c
  fixed-point-iter.c
)

add_executable(traj-54 compute-traj-54 ${dynamics_sources})
install_targets( /bin traj-54)


