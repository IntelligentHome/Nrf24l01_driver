#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Nrf24l01Common.h"

namespace test_nrf24l01 {

TEST(Nrf24l01_SetPaylaod, SetMaxSizePayload) {

    uint8_t sent_data[200];
    const uint8_t sent_expected[] = {
        0xA0,
        'E', 'x', 'a', 'm', 'p', 'l', 'e', ' ',
        'O', 'f', ' ', 'm', 'e', 's', 's', 'a',
        'g', 'e', '1', '2', '3', '4', '5', '6',
    };

    const uint8_t payload[] = {
        'E', 'x', 'a', 'm', 'p', 'l', 'e', ' ',
        'O', 'f', ' ', 'm', 'e', 's', 's', 'a',
        'g', 'e', '1', '2', '3', '4', '5', '6',
    };

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    nrf.SetPayload(payload, sizeof(payload));

    for (int i = 0; i < sizeof(sent_expected); i++)
        EXPECT_TRUE(sent_expected[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expected " << (int)sent_expected[i] \
                << " at position: " << i << std::endl;
}

TEST(Nrf24l01_SetPaylaod, SetMoreThanMaxSizeOfPayload) {

    uint8_t sent_data[200];
    Status status;
    const uint8_t payload[] = {
        'E', 'x', 'a', 'm', 'p', 'l', 'e', ' ',
        'O', 'f', ' ', 'm', 'e', 's', 's', 'a',
        'g', 'e', '1', '2', '3', '4', '5', '6',
        '4', '4', '2', '1', '2', '9', '0', '8',
        0xFF,
    };

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data));

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    status = nrf.SetPayload(payload, sizeof(payload));

    EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
}

} /*namespace test_nrf24l01*/
