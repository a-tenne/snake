cmake_minimum_required(VERSION 4.0)
project(Snake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Need to set those before fetching and building SDL3
set(SDL_TEST OFF)
set(SDL_TEST_LIBRARY OFF)
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(BUILD_SHARED_LIBS OFF)
set(SDLTTF_SAMPLES OFF)


include(FetchContent)
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.18
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
  SDL3_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG release-3.2.2
)
FetchContent_MakeAvailable(SDL3_ttf)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_compile_options(-Wall -Werr -pedantic -fsanitize=address,undefined)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_ttf_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3-static SDL3_ttf-static)
