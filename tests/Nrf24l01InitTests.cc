#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Mocks.h"


namespace test_nrf24l01 {

/*
 On init nrf24l01 driver should:
    1. Set high logic level on gpio responsible for chip enable.
 */
TEST(Nrf24l01, Init) {

    uint16_t set_cnt = 0;
    uint16_t clear_cnt = 0;
    uint16_t toggle_cnt = 0;
    uint8_t state = 0;

    uint8_t sent_data[200];

    test_mocks::GpioMock gpio(&set_cnt, &clear_cnt, &toggle_cnt, &state);
    test_mocks::TransportMock transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x25, 0x60, // Set Channel
        0x20, 0x0D,// Set default config, Rx mode, Power Down, crc0-2byte, enable crc
        0x00, 0x00,
        0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &transport,
            &gpio);

    EXPECT_TRUE(1 == set_cnt);
    EXPECT_TRUE(0 == clear_cnt);
    EXPECT_TRUE(0 == toggle_cnt);

    for(int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << \
                "Got " << (int)sent_data[i] << " Expected " << (int)expected_transport[i] << std::endl;
}

} /*namespace test_nrf24l01*/
