cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Nrf24l01_driver_tests)

enable_language(C CXX)

set(GOOGLETEST_ROOT ../../External/googletest/googletest CACHE STRING "Google Test source root")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
    ../
    ../../External/include
    )

set(GOOGLETEST_SOURCES
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
    )

foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GOOGLETEST_SOURCES})

add_executable(
    Nrf24l01_driver_unit_tests
    main.cc
    Nrf24l01InitTests.cc
    Nrf24l01SetRfChannelTests.cc
    Nrf24l01SetPayloadSizeTests.cc
    Nrf24l01GetStatusRegister.cc
    Nrf24l01SetRetries.cc
    Nrf24l01SetAddressTests.cc
    Nrf24l01GetPayloadTests.cc
    Nrf24l01SetPayloadTests.cc
    Nrf24l01SetAutoAckTests.cc
    ../Nrf24l01.cpp
    )

add_dependencies(Nrf24l01_driver_unit_tests googletest)

target_link_libraries(
    Nrf24l01_driver_unit_tests
    googletest
    pthread
    )

