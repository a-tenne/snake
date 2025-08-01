cmake_minimum_required(VERSION 3.12)
project(Snake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Need to set those before fetching and building SDL3
set(SDL_TEST OFF)
set(SDL_TEST_LIBRARY OFF)
set(BUILD_SHARED_LIBS OFF)
set(SDLTTF_SAMPLES OFF)

if(MSVC)
  add_compile_options(/MTd)
endif()

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

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -pedantic -fsanitize=address,undefined)
  target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -pedantic)
endif()
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3-static SDL3_ttf-static)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

option(BUILD_TESTING "Build unit tests" ON)

if(BUILD_TESTING)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
  )
  FetchContent_MakeAvailable(googletest)
  enable_testing()

  file(GLOB_RECURSE TEST_SOURCES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
  list(APPEND TEST_SOURCES ${SOURCES})
  list(REMOVE_ITEM TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)
  add_executable(Tests ${TEST_SOURCES})
  if (MSVC)
    target_compile_options(Tests PRIVATE /W4 /WX)
  else()
    target_compile_options(Tests PRIVATE -Wall -Werror -pedantic -fsanitize=address,undefined)
    target_link_options(Tests PRIVATE -fsanitize=address,undefined)
  endif()
  target_include_directories(Tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
  target_link_libraries(Tests PRIVATE SDL3-static SDL3_ttf-static gtest)
  add_custom_command(TARGET Tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets $<TARGET_FILE_DIR:Tests>/assets
  )
  include(GoogleTest)
  gtest_discover_tests(Tests)
endif()
