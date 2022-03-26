cmake_minimum_required(VERSION 3.20)
project(kphpVk)

set(CMAKE_CXX_STANDARD 14)

add_executable(kphpVk source/main.cpp source/Lexer.cpp source/Lexer.h source/Token.cpp source/Token.h )
