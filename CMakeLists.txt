cmake_minimum_required(VERSION 3.16)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "generate compile_commands.json")

# Verbose build output
# set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "enable verbose build")

project(Mandelbrot CXX)

# Define sources and executable
AUX_SOURCE_DIRECTORY(. PROJECT_SRC)
add_executable(${PROJECT_NAME} ${PROJECT_SRC})
target_compile_options(${PROJECT_NAME} PUBLIC -g -Wall -Wextra)
#target_compile_options(${PROJECT_NAME} PUBLIC -fanalyzer)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
else(OpenMP_CXX_FOUND)
  message("ERROR: OpenMP could not be found.")
endif(OpenMP_CXX_FOUND)

# Grafikbibliothek GTK2 suchen und zum Projekt hinzufuegen
include(FindGTK2)
if (GTK2_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GTK2_INCLUDE_DIRS})
    target_link_directories(${PROJECT_NAME} PRIVATE ${GTK2_LIBRARY_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK2_LIBRARIES})
endif (GTK2_FOUND)

