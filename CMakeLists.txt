cmake_minimum_required(VERSION 3.16)
message(STATUS "CMake ${CMAKE_VERSION}")

project(project-winda VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_SHARED_LIBS OFF)

# spdlog dependency
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/spdlog")

# SDL dependency
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL")

# SDL TTF dependency (for text rendering)
set(SDL2TTF_VENDORED ON CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL_ttf")

# winda target
file(GLOB_RECURSE WINDA_SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM WINDA_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_library(winda-lib ${WINDA_SRC_FILES})
add_executable(winda "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

target_compile_features(winda PUBLIC cxx_std_17)
target_include_directories(winda-lib
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )
target_link_libraries(winda-lib
        PUBLIC
        spdlog::spdlog
        SDL2main
        SDL2-static
        SDL2_ttf
        )
target_link_libraries(winda
        PUBLIC
        winda-lib
        )

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Visual Studio
    target_compile_options(winda PRIVATE /W4 /WX)
    add_definitions(-D_AMD64_=1) # TODO possibly there is a better way to solve the "No Target Architecture" error
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC, MinGW etc.
    target_compile_options(winda PRIVATE -static-libstdc++ -Wall -Wextra -pedantic)
endif ()
