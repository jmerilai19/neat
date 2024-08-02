cmake_minimum_required(VERSION 3.29)

set(This NEAT)
project(${This} LANGUAGES CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(Sources
    main.cpp
    genome.cpp
    connection.cpp
    node.cpp
    utils.cpp
    innovationtracker.cpp
    population.cpp
    species.cpp
)

add_executable(${This} ${Sources})
