cmake_minimum_required(VERSION 3.29)
project(paint_cg C)

set(CMAKE_C_STANDARD 11)

add_library(paint_cg STATIC library.c)
