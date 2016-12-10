#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Mocks.h"

namespace test_nrf24l01 {

TEST(Nrf24l01SetRetries, TryToSetGraterThenMax) {

    uint8_t sent_data[200];
    Status status;

    test_mocks::GpioMock mock_gpio;
    test_mocks::TransportMock mock_transport(sent_data, sizeof(sent_data));

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    status = nrf.SetRetries(0, 16);
    EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);

    status = nrf.SetRetries(16, 0);
    EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);

    status = nrf.SetRetries(16, 16);
    EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);

    status = nrf.SetRetries(40, 88);
    EXPECT_TRUE(STATUS_OUT_OF_RANGE == status);
}

TEST(Nrf24l01SetRetries, SetRetriesAndDelay) {

    uint8_t sent_data[200];
    Status status;

    test_mocks::GpioMock mock_gpio;
    test_mocks::TransportMock mock_transport(sent_data, sizeof(sent_data));

    const uint8_t expected_transport[] = {
        0x24, 0x00,
        0x24, 0xAA,
        0x24, 0x58,
        0x24, 0xFF,
        0x00, 0x00,
    };

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    mock_transport.sent_data_idx_ = 0;

    status = nrf.SetRetries(0, 0);
    EXPECT_TRUE(STATUS_OK == status);

    status = nrf.SetRetries(10, 10);
    EXPECT_TRUE(STATUS_OK == status);

    status = nrf.SetRetries(5, 8);
    EXPECT_TRUE(STATUS_OK == status);

    status = nrf.SetRetries(15, 15);
    EXPECT_TRUE(STATUS_OK == status);

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << std::hex << "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}

} /*namespace test_nrf24l01*/
