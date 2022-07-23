cmake_minimum_required(VERSION 3.10)

project(DecaGamesServer)

set(CMAKE_CXX_STANDARD 17)

configure_file(bin/equip.xml ${CMAKE_BINARY_DIR}/bin/equip.xml COPYONLY)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(lib)

