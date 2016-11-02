#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Nrf24l01Common.h"

namespace test_nrf24l01 {

TEST(Nrf24l01SetRfChannelTests, SetRfChannelTo0x60) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = { 0x25, 0x60, 0x00, 0x00 };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.SetRfChannel(0x60);

    for(int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << "Expected " << (int)expected_transport[i] << std::endl;
}

TEST(Nrf24l01SetRfChannelTests, SetRfChannelCoupleTimes) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = { 0x25, 0x46, 0x25, 0x33, 0x00, 0x00 };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.SetRfChannel(0x46);
    nrf.SetRfChannel(0x33);

    for(int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << "Expected " << (int)expected_transport[i] << std::endl;
}

TEST(Nrf24l01SetRfChannelTests, NegativeTryToSetMoreThanMax) {

    uint8_t sent_data[200];

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = { 0x00, 0x00 };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    for (int i = 128; i < 255; i++)
        EXPECT_TRUE(STATUS_OUT_OF_RANGE == nrf.SetRfChannel(i));

    for(int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << "Expected " << (int)expected_transport[i] << std::endl;
}



} /*namespace test_nrf2401*/
