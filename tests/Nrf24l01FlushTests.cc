#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Nrf24l01Common.h"

namespace test_nrf24l01 {

TEST(Nrf24l01_FlushRx, FlushRx) {

    uint8_t sent_data[200];

    const uint8_t sent_expected[] = {
        0xE2, 0x00, 0x00, 0x00,
    };

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.FlushRx();

    for (int i = 0; i < sizeof(sent_expected); i++)
        EXPECT_TRUE(sent_expected[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expected " << (int)sent_expected[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01_FlushTx, FlushTx) {

    uint8_t sent_data[200];

    const uint8_t sent_expected[] = {
        0xE1, 0x00, 0x00, 0x00,
    };

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.FlushTx();

    for (int i = 0; i < sizeof(sent_expected); i++)
        EXPECT_TRUE(sent_expected[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expected " << (int)sent_expected[i] \
                << " at position: " << i << std::endl;
}

} /*namespace test_nrf24l01*/
