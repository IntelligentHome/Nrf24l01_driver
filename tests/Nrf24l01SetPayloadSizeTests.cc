#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Nrf24l01Common.h"

namespace test_nrf24l01 {

TEST(Nrf24l01, SetPaylaodSizeTo10) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = { 
        0x31, 0x10, // Payload for Rx0
        0x32, 0x10, // Payload for Rx1
        0x33, 0x10, // Paylaod for Rx2
        0x34, 0x10, // Payload for Rx3
        0x35, 0x10, // Payload for Rx4
        0x36, 0x10, // Payload for Rx5
        0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.SetPayloadSize(0x10);

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] << " at position: " << i << std::endl;
}

TEST(Nrf24l01, SetPayloadSizeForRx0) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x31, 0x10, // Payload for Rx0
        0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.SetPayloadSize(nrf24_driver::R0, 0x10);

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << std::hex << "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] << " at position: " << i << std::endl;
}

TEST(Nrf24l01, SetPayloadSizeForRx1) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x32, 0x10, // Payload for Rx1
        0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.SetPayloadSize(nrf24_driver::R1, 0x10);

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << std::hex << "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] << " at position: " << i << std::endl;
}

TEST(Nrf24l01, SetPayloadSizeForRx2) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x33, 0x10, // Payload for Rx2
        0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.SetPayloadSize(nrf24_driver::R2, 0x10);

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << std::hex << "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] << " at position: " << i << std::endl;
}

TEST(Nrf24l01, SetPayloadSizeForRx3) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x34, 0x10, // Payload for Rx3
        0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.SetPayloadSize(nrf24_driver::R3, 0x10);

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << std::hex << "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] << " at position: " << i << std::endl;
}

TEST(Nrf24l01, SetPayloadSizeForRx4) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x35, 0x10, // Payload for Rx4
        0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.SetPayloadSize(nrf24_driver::R4, 0x10);

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << std::hex << "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] << " at position: " << i << std::endl;
}

TEST(Nrf24l01, SetPayloadSizeForRx5) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x36, 0x10, // Payload for Rx5
        0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.SetPayloadSize(nrf24_driver::R5, 0x10);

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << std::hex << "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] << " at position: " << i << std::endl;
}

TEST(Nrf24l01, SetPaylaodSizeCoupleTimes) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = { 
        0x31, 0x10, // Payload for Rx0
        0x32, 0x10, // Payload for Rx1
        0x33, 0x10, // Paylaod for Rx2
        0x34, 0x10, // Payload for Rx3
        0x35, 0x10, // Payload for Rx4
        0x36, 0x10, // Payload for Rx5
        0x31, 0x20, // Payload for Rx0
        0x32, 0x20, // Payload for Rx1
        0x33, 0x20, // Payload for Rx2
        0x34, 0x20, // Paylaod for Rx3
        0x35, 0x20, // Payload for Rx4
        0x36, 0x20, // Payload for Rx5
        0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.SetPayloadSize(0x10);
    nrf.SetPayloadSize(0x20);

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << std::hex << "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] << " at position: " << i << std::endl;
}

TEST(Nrf24l01, NegativeTryToSetMoreThanMax) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = { 
        0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    for (int i = 0x21; i < 0xFF; i++)
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == nrf.SetPayloadSize(i));

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << std::hex <<  "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] << " at position: " << i << std::endl;
}

} /*namespace test_nrf24l01*/
