#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Nrf24l01Common.h"

namespace test_nrf24l01 {

TEST(Nrf24l01_SetAutoAck, SetMultipleValidAutoAck) {

    uint8_t sent_data[200];
    Status status;

    const uint8_t sent_expected[] = {
        0x21, 0x0F,
        0x21, 0x3F,
        0x21, 0x29,
        0x00, 0x00,
        0x00, 0x00,
    };

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    status = nrf.SetAutoAck(0x0F);
    EXPECT_TRUE(STATUS_OK == status);

    status = nrf.SetAutoAck(0x3F);
    EXPECT_TRUE(STATUS_OK == status);

    status = nrf.SetAutoAck(0x29);
    EXPECT_TRUE(STATUS_OK == status);

    for (int i = 0; i < sizeof(sent_expected); i++)
        EXPECT_TRUE(sent_expected[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expected " << (int)sent_expected[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01_SetAutoAck, SetInvalidAutoAck) {

    uint8_t sent_data[200];
    Status status;

    const uint8_t sent_expected[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    status = nrf.SetAutoAck(0xFF);
    EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);

    status = nrf.SetAutoAck(0x40);
    EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);

    status = nrf.SetAutoAck(0xA3);
    EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);

    for (int i = 0; i < sizeof(sent_expected); i++)
        EXPECT_TRUE(sent_expected[i] == sent_data[i]) << "Got " \
                <<(int)sent_data[i] << " Expected " << (int)sent_expected[i] \
                << " at position: " << i << std::endl;
}

} /* namespace test_nrf24l01 */
