#!/bin/bash

BUILD=0
TEST=0
CLEAN=0

EXIT_CODE=0

BUILD_DIR=bin
TEST_DIR=bin_tests

function build_Nrf24l01_driver {
    local retval=0

    mkdir -p $BUILD_DIR
    cd $BUILD_DIR
    cmake ..
    make
    retval=$?
    cd ..

    return $retval
}

function run_tests {
    local retval=0

    mkdir -p $TEST_DIR
    cd $TEST_DIR
    cmake ../tests
    make
    ./Nrf24l01_driver_unit_tests
    retval=$?
    rm Nrf24l01_driver_unit_tests
    cd ..

    return $retval
}

function clean {
    if [ -e $BUILD_DIR ]; then
        rm -r $BUILD_DIR
    fi

    if [ -e $TEST_DIR ]; then
        rm -r $TEST_DIR
    fi
}

while getopts ":btc" opt; do
    case $opt in
        b)
            BUILD=1 ;;
        t)
            TEST=1 ;;
        c)
            CLEAN=1 ;;
        \?)
            echo "Invalid option: -$OPTARG" >$2
            exit 1 ;;
    esac
done

if [ 1 == $BUILD ]; then
    build_Nrf24l01_driver
    if [ $? != 0 ]; then
        $EXIT_CODE=1
    fi
fi

if [ 1 == $TEST ]; then
    run_tests
    if [ $? != 0 ]; then
        $EXIT_CODE=1
    fi
fi

if [ 1 == $CLEAN ]; then
    clean
    if [ $? != 0 ]; then
        $EXIT_CODE=1
    fi
fi

exit $EXIT_CODE

