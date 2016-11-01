#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Nrf24l01Common.h"


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

    GpioMock gpio(&set_cnt, &clear_cnt, &toggle_cnt, &state);
    TransportMock transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = { 0x25, 0x60 };

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
