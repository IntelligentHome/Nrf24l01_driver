#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Nrf24l01Common.h"

namespace test_nrf24l01 {

TEST(Nrf24l01_StartListening, StartListening) {

    uint8_t sent_data[200];
    uint8_t get_data[200];
    uint16_t set_cnt = 0;
    uint16_t clear_cnt = 0;
    uint16_t toggle_cnt = 0;
    uint8_t state = 0;

    const uint8_t sent_expected[] = {
        0x00, 0x00, // Get Config
        0x20, 0x0F, // Power Up
        0x00, 0x00,
    };

    const uint8_t get_expected[] = {
        0xFF, 0x0D, // Get Config (Power Down)
        0x00, 0x00,
    };

    GpioMock mock_gpio(&set_cnt, &clear_cnt, &toggle_cnt, &state);
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

    set_cnt = 0;
    clear_cnt = 0;
    toggle_cnt = 0;

    nrf.StartListening();

    EXPECT_TRUE(1 == set_cnt);
    EXPECT_TRUE(0 == clear_cnt);
    EXPECT_TRUE(0 == toggle_cnt);

    for (int i = 0; i < sizeof(sent_expected); i++)
        EXPECT_TRUE(sent_expected[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expected " << (int)sent_expected[i] \
                << " at position: " << i << std::endl;

    for (int i = 0; i < sizeof(get_expected); i++)
        EXPECT_TRUE(get_expected[i] == get_data[i]) << "Got " \
                << (int)get_data[i] << " Expected " << (int)get_expected[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01_StopListening, StopListening) {

    uint8_t sent_data[200];
    uint8_t get_data[200];
    uint16_t set_cnt = 0;
    uint16_t clear_cnt = 0;
    uint16_t toggle_cnt = 0;
    uint8_t state = 0;

    const uint8_t sent_expected[] = {
        0x00, 0x00, // Get Config
        0x20, 0x0D, // Power Down
        0x00, 0x00,
    };

    const uint8_t get_expected[] = {
        0xFF, 0x0F, // Get Config (Power Up)
        0x00, 0x00,
    };

    GpioMock mock_gpio(&set_cnt, &clear_cnt, &toggle_cnt, &state);
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

    set_cnt = 0;
    clear_cnt = 0;
    toggle_cnt = 0;

    nrf.StopListening();

    EXPECT_TRUE(0 == set_cnt);
    EXPECT_TRUE(1 == clear_cnt);
    EXPECT_TRUE(0 == toggle_cnt);

    for (int i = 0; i < sizeof(sent_expected); i++)
        EXPECT_TRUE(sent_expected[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expected " << (int)sent_expected[i] \
                << " at position: " << i << std::endl;

    for (int i = 0; i < sizeof(get_expected); i++)
        EXPECT_TRUE(get_expected[i] == get_data[i]) << "Got " \
                << (int)get_data[i] << " Expected " << (int)get_expected[i] \
                << " at position: " << i << std::endl;
}

} /*namespace test_nrf24l01*/
