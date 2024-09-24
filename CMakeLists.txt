cmake_minimum_required(VERSION 3.10)
project(paint-cg C)

set(CMAKE_C_STANDARD 11)

# Adicione os arquivos de origem
add_executable(paint-cg main.c objetos.c
        selecoes.c transformacoes.c)

# Inclua os diretórios necessários
include_directories("C:/MinGW/include")

# Adicione os diretórios de link
link_directories("C:/MinGW/lib")

# Link com as bibliotecas OpenGL e GLUT
target_link_libraries(paint-cg opengl32 glu32 freeglut)
