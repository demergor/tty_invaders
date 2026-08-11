cmake_minimum_required(VERSION 3.20)

project(
  tty_invaders
  VERSION 0.1
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

set(COMPILE_OPTIONS
  -g
  -Wall
  -Wextra
  -Wpedantic
  -Wconversion
  -Wsign-conversion
  -Wshadow
  -Wold-style-cast
  -Werror=return-type
)

set(SANITIZER_OPTIONS
  -fsanitize=address,undefined
)

add_library(
  tty_invaders_lib
  src/entities/templates/ships.cpp
  src/gameplay/collision_buffer.cpp
  src/io/raw_term.cpp
  src/rendering/term_dims.cpp
)

target_include_directories(
  tty_invaders_lib
  PUBLIC
    include
)

target_compile_options(
  tty_invaders_lib
  PRIVATE
    ${COMPILE_OPTIONS}
    ${SANITIZER_OPTIONS}
)

target_link_options(
  tty_invaders_lib
  PRIVATE
    ${SANITIZER_OPTIONS}
)

add_executable(
  tty_invaders
  src/main.cpp
)

target_link_libraries(
  tty_invaders
  PRIVATE
    tty_invaders_lib
)

target_compile_options(
  tty_invaders
  PRIVATE
    ${COMPILE_OPTIONS}
    ${SANITIZER_OPTIONS}
)

target_link_options(
  tty_invaders
  PRIVATE
    ${SANITIZER_OPTIONS}
)

enable_testing()

add_executable(
  tty_invaders_tests
  tests/test_main.cpp
  tests/gameplay/collision_buffer_tests.cpp
)

target_link_libraries(
  tty_invaders_tests
  PRIVATE
    tty_invaders_lib
    GTest::gtest_main
)

target_compile_options(
  tty_invaders_tests
  PRIVATE
    ${COMPILE_OPTIONS}
    ${SANITIZER_OPTIONS}
)

target_link_options(
  tty_invaders_tests
  PRIVATE
    ${SANITIZER_OPTIONS}
)

include(GoogleTest)

gtest_discover_tests(tty_invaders_tests)
