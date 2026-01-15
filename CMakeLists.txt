cmake_minimum_required(VERSION 4.1)
project(bouncingBalls)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

add_executable(bouncingBalls src/main.cpp
        include/ball.h
        include/ballsEngine.h)

target_link_libraries(bouncingBalls PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)
