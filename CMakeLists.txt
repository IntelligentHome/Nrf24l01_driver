
set(CMAKE_SYSTEM_NAME Generic)
cmake_minimum_required(VERSION 2.8)

project(Nrf24l01_driver)

set(MCU atmega8)
set(FCPU 8000000UL)

find_program(AVR_AR avr-ar)
find_program(AVR_RANLIB avr-ranlib)

set(SOURCES
    Nrf24l01.cpp
    )

include_directories(
    ../External/include/
    )

set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_AR ${AVR_AR})
set(CMAKE_RANLIB ${AVR_RANLIB})
set(CMAKE_CXX_FLAGS "-Wall -Os -mmcu=${MCU} -DF_CPU=${FCPU}")
set(FLASH_FLAGS "-R .eeprom -R .fuse -R .lock -R .signature")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
