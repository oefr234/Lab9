cmake_minimum_required(VERSION 3.28)
project(OOP_lab9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

add_executable(OOP_lab9 main.cpp
        controller/controller.cpp
        controller/controller.h
        domain/domain.cpp
        domain/domain.h
        domain/validare.cpp
        domain/validare.h
        repository/repository.cpp
        repository/repository.h
        shopping_cart/cart.cpp
        shopping_cart/cart.h
        teste/teste.cpp
        teste/teste.h
        ui/consola.cpp
        ui/consola.h
        undo.h
        NewRepo.cpp)
