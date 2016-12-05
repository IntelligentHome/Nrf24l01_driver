#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Nrf24l01Common.h"

namespace test_nrf24l01 {

TEST(Nrf24l01, GetPaylaod) {

    uint8_t sent_data[200];
    uint8_t get_data[200];

    const uint8_t sent_expected[] = {
        0x61, // Read Rx payload
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    const uint8_t get_expected[] = {
        0xFF, // Status byte, sent as first byte
        'E', 'X', 'A', 'M', 'P', 'L', 'E', ' ',
        'O', 'F', ' ', 'M', 'e', 's', 's', 'a',
        'g', 'e', '1', '2', '3', '4', '5', '6',
    };

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data), get_data, sizeof(get_data));

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    memset(get_data, 0, sizeof(get_data));
    mock_transport.sent_data_idx_ = 0;
    mock_transport.get_data_idx_ = 0;

    for (int i = 0; i < sizeof(get_expected); i++)
        get_data[i] = get_expected[i];

    nrf.GetPayload(get_data, 0x20);

    for (int i = 0; i < sizeof(sent_expected); i++)
        EXPECT_TRUE(sent_expected[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expected " << (int)sent_expected[i] \
                << " at position: " << i << std::endl;

    for (int i = 0; i < sizeof(get_expected) - 1; i++)
        EXPECT_TRUE(get_expected[i + 1] == get_data[i]) << "Got " \
                << (int)get_data[i] << " Expected " << (int)get_expected[i] \
                << " at position: " << i << std::endl;
}

} /*namespace test_nrf24l01*/
