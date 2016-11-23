#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Nrf24l01Common.h"

namespace test_nrf24l01 {

TEST(Nrf24l01, InvalidSizeOfTxAddressTest_TryToSetLessThan5Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0x30, 0x33, 0xFF, 0x32 };
        status = nrf.SetAddress(nrf24_driver::T0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x44, 0x20, 0x11 };
        status = nrf.SetAddress(nrf24_driver::T0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x99, 0x22 };
        status = nrf.SetAddress(nrf24_driver::T0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0xAE };
        status = nrf.SetAddress(nrf24_driver::T0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01, InvalidSizeOfTxAddressTest_TryToSetGreaterThan5Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0x30, 0x33, 0xFF, 0x32, 0x34, 0xEE };
        status = nrf.SetAddress(nrf24_driver::T0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x44, 0x20, 0x11, 0x45, 0x12, 0x33, 0xF1 };
        status = nrf.SetAddress(nrf24_driver::T0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x99, 0x22, 0x99, 0x88, 0x77, 0x37, 0x29, 0x56 };
        status = nrf.SetAddress(nrf24_driver::T0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0xAE, 0x87, 0x83, 0x28, 0x45, 0x89, 0x29, 0x62, 0x32 };
        status = nrf.SetAddress(nrf24_driver::T0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01, InvalidSizeOfR0AddressTest_TryToSetLessThan5Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0x30, 0x33, 0xFF, 0x32 };
        status = nrf.SetAddress(nrf24_driver::R0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x44, 0x20, 0x11 };
        status = nrf.SetAddress(nrf24_driver::R0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x99, 0x22 };
        status = nrf.SetAddress(nrf24_driver::R0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0xAE };
        status = nrf.SetAddress(nrf24_driver::R0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01, InvalidSizeOfR0AddressTest_TryToSetGreaterThan5Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0x30, 0x33, 0xFF, 0x32, 0x34, 0xF2 };
        status = nrf.SetAddress(nrf24_driver::R0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x44, 0x20, 0x11, 0x45, 0x12, 0x33, 0x12 };
        status = nrf.SetAddress(nrf24_driver::R0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x99, 0x22, 0x99, 0x88, 0x77, 0x37, 0x29, 0x56 };
        status = nrf.SetAddress(nrf24_driver::R0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0xAE, 0x87, 0x83, 0x28, 0x45, 0x89, 0x29, 0x62, 0x62 };
        status = nrf.SetAddress(nrf24_driver::R0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}


TEST(Nrf24l01, InvalidSizeOfR1AddressTest_TryToSetLessThan5Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0x30, 0x33, 0xFF, 0x32 };
        status = nrf.SetAddress(nrf24_driver::R1, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x44, 0x20, 0x11 };
        status = nrf.SetAddress(nrf24_driver::R1, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x99, 0x22 };
        status = nrf.SetAddress(nrf24_driver::R1, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0xAE };
        status = nrf.SetAddress(nrf24_driver::R1, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01, InvalidSizeOfR1AddressTest_TryToSetGreaterThan5Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0x30, 0x33, 0xFF, 0x32, 0x34, 0x67 };
        status = nrf.SetAddress(nrf24_driver::R1, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x44, 0x20, 0x11, 0x45, 0x12, 0x33, 0xDE };
        status = nrf.SetAddress(nrf24_driver::R1, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x99, 0x22, 0x99, 0x88, 0x77, 0x37, 0x29, 0x19 };
        status = nrf.SetAddress(nrf24_driver::R1, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0xAE, 0x87, 0x83, 0x28, 0x45, 0x89, 0x29, 0x62, 0x52 };
        status = nrf.SetAddress(nrf24_driver::R1, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}


TEST(Nrf24l01, InvalidSizeOfR2AddressTest_TryToSetLessThan1Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { };
        status = nrf.SetAddress(nrf24_driver::R2, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}


TEST(Nrf24l01, InvalidSizeOfR2AddressTest_TryToSetGreaterThan1Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0x30, 0x33 };
        status = nrf.SetAddress(nrf24_driver::R2, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x44, 0x20, 0x11 };
        status = nrf.SetAddress(nrf24_driver::R2, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x88, 0x77, 0x37, 0x29 };
        status = nrf.SetAddress(nrf24_driver::R2, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x28, 0x45, 0x89, 0x29, 0x62 };
        status = nrf.SetAddress(nrf24_driver::R2, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}



TEST(Nrf24l01, InvalidSizeOfR3AddressTest_TryToSetLessThan1Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { };
        status = nrf.SetAddress(nrf24_driver::R3, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01, InvalidSizeOfR3AddressTest_TryToSetGreaterThan1Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0x30, 0x33 };
        status = nrf.SetAddress(nrf24_driver::R3, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x44, 0x20, 0x11 };
        status = nrf.SetAddress(nrf24_driver::R3, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x88, 0x77, 0x37, 0x29 };
        status = nrf.SetAddress(nrf24_driver::R3, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x28, 0x45, 0x89, 0x29, 0x62 };
        status = nrf.SetAddress(nrf24_driver::R3, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}


TEST(Nrf24l01, InvalidSizeOfR4AddressTest_TryToSetLessThan1Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { };
        status = nrf.SetAddress(nrf24_driver::R4, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01, InvalidSizeOfR4AddressTest_TryToSetGreaterThan1Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0x30, 0x33 };
        status = nrf.SetAddress(nrf24_driver::R4, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x44, 0x20, 0x11 };
        status = nrf.SetAddress(nrf24_driver::R4, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x88, 0x77, 0x37, 0x29 };
        status = nrf.SetAddress(nrf24_driver::R4, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x28, 0x45, 0x89, 0x29, 0x62 };
        status = nrf.SetAddress(nrf24_driver::R4, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}


TEST(Nrf24l01, InvalidSizeOfR5AddressTest_TryToSetLessThan1Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { };
        status = nrf.SetAddress(nrf24_driver::R5, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01, InvalidSizeOfR5AddressTest_TryToSetGreaterThan1Bytes) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0x30, 0x33 };
        status = nrf.SetAddress(nrf24_driver::R5, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x44, 0x20, 0x11 };
        status = nrf.SetAddress(nrf24_driver::R5, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x88, 0x77, 0x37, 0x29 };
        status = nrf.SetAddress(nrf24_driver::R5, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    {
        const uint8_t pipe_address[] = { 0x28, 0x45, 0x89, 0x29, 0x62 };
        status = nrf.SetAddress(nrf24_driver::R5, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}


TEST(Nrf24l01, SetMultipleTxAddressTests) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x30, 0x30, 0x45, 0x99, 0xF2, 0xEE, // address for pipe T0
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0x30, 0x45, 0x99, 0xF2, 0xEE };
        status = nrf.SetAddress(nrf24_driver::T0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OK == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01, SetMultipleRxAddressTests) {

    uint8_t sent_data[200];

    Status status;
    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x2A, 0xED, 0xF3, 0xA9, 0x8C, 0x44, // address for pipe R0
        0x2B, 0x22, 0xE1, 0x93, 0xA1, 0x12, // address for pipe R1
        0x2C, 0x82,                         // address for pipe R2
        0x2D, 0xDA,                         // address for pipe R3
        0x2E, 0x49,                         // address for pipe R4
        0x2F, 0x99,                         // address for pipe R5
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    {
        const uint8_t pipe_address[] = { 0xED, 0xF3, 0xA9, 0x8C, 0x44 };
        status = nrf.SetAddress(nrf24_driver::R0, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OK == status);
    }

    {
        const uint8_t pipe_address[] = { 0x22, 0xE1, 0x93, 0xA1, 0x12 };
        status = nrf.SetAddress(nrf24_driver::R1, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OK == status);
    }

    {
        const uint8_t pipe_address[] = { 0x82 };
        status = nrf.SetAddress(nrf24_driver::R2, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OK == status);
    }

    {
        const uint8_t pipe_address[] = { 0xDA };
        status = nrf.SetAddress(nrf24_driver::R3, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OK == status);
    }

    {
        const uint8_t pipe_address[] = { 0x49 };
        status = nrf.SetAddress(nrf24_driver::R4, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OK == status);
    }

    {
        const uint8_t pipe_address[] = { 0x99 };
        status = nrf.SetAddress(nrf24_driver::R5, pipe_address, sizeof(pipe_address));
        EXPECT_TRUE(STATUS_OK == status);
    }

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expect " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}

} /*namespace test_nrf24l01*/
