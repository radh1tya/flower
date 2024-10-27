CMAKE_MINIMUM_REQUIRED(VERSION 3.30)
PROJECT(flower)
ADD_EXECUTABLE(flower
  src/main.c
  src/file.c
  src/memory.c
  src/lexer.c
)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
INCLUDE_DIRECTORIES(include)
