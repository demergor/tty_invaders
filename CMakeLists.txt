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
)

add_executable(
  tty_invaders

  # src/main.cpp

  src/io/ctrls.cpp
  src/io/raw_term.cpp

  src/rendering/cell.cpp
  src/rendering/double_buffer.cpp
  src/rendering/rendering.cpp
  src/rendering/term_dims.cpp

  src/entities/bullets.cpp
  src/entities/defender.cpp
  src/entities/invaders.cpp
)

target_include_directories(
  tty_invaders
  PRIVATE
    include
)

target_compile_options(
  tty_invaders
  PRIVATE
    -g
    -fsanitize=address,undefined
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wshadow
    -Wold-style-cast
    -Werror=return-type
)

target_link_options(
  tty_invaders 
  PRIVATE
    -fsanitize=address,undefined
)

enable_testing()
add_executable(
  tty_invader_tests
)

target_link_libraries(
  tty_invader_tests
  PRIVATE
    tty_invaders
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tty_invader_tests)
