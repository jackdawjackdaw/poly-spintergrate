cmake_minimum_required (VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
project (spintergrate)

## clobber default install path so that bins end up in project-root/bin
set(CMAKE_INSTALL_PREFIX ..)


## don't need any libs right now

add_subdirectory(src)
