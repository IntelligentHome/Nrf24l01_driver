
set(CMAKE_SYSTEM_NAME Generic)
cmake_minimum_required(VERSION 2.8)

project(Nrf24l01_driver)

include (../External/PlatformDependency.cmake)

set(SOURCES
    Nrf24l01.cpp
    )

include_directories(
    ../External/include/
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
