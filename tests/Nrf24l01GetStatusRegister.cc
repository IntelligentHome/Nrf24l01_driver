#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Nrf24l01Common.h"

namespace test_nrf24l01 {

TEST(Nrf24l01, GetStatusRegister) {

    uint8_t sent_data[200];
    uint8_t get_data[200];
    nrf24_driver::NrfStatusRegister status_reg = { 0 };
    nrf24_driver::NrfStatusRegister inject_status_reg = { 0 };

    const uint8_t expected_transport[] = {
        0xFF, 0x00, 0x00, 0x00 };

    GpioMock mock_gpio;
    TransportMock mock_transport(sent_data, sizeof(sent_data), get_data, sizeof(get_data));

    nrf24l01_driver::Nrf24l01 nrf(
            &mock_transport,
            &mock_gpio);

    memset(sent_data, 0, sizeof(sent_data));
    memset(get_data, 0, sizeof(get_data));
    mock_transport.sent_data_idx_ = 0;
    mock_transport.get_data_idx_ = 0;

    inject_status_reg.raw_data = 0;
    inject_status_reg.tx_full = 1;
    inject_status_reg.rx_pipe_no = 4;
    inject_status_reg.rx_data_ready = 1;

    get_data[0] = inject_status_reg.raw_data;

    status_reg = nrf.GetStatus();

    EXPECT_TRUE(inject_status_reg.raw_data == status_reg.raw_data);
    EXPECT_TRUE(1 == status_reg.tx_full);
    EXPECT_TRUE(4 == status_reg.rx_pipe_no);
    EXPECT_TRUE(1 == status_reg.rx_data_ready);
    EXPECT_TRUE(0 == status_reg.tx_data_ready);
    EXPECT_TRUE(0 == status_reg.max_rt);

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;

    memset(sent_data, 0, sizeof(sent_data));
    memset(get_data, 0, sizeof(get_data));
    mock_transport.sent_data_idx_ = 0;
    mock_transport.get_data_idx_ = 0;

    inject_status_reg.raw_data = 0;
    inject_status_reg.rx_data_ready = 1;
    inject_status_reg.tx_data_ready = 1;
    inject_status_reg.rx_pipe_no = 2;

    get_data[0] = inject_status_reg.raw_data;

    status_reg = nrf.GetStatus();

    EXPECT_TRUE(inject_status_reg.raw_data == status_reg.raw_data);
    EXPECT_TRUE(1 == status_reg.rx_data_ready);
    EXPECT_TRUE(1 == status_reg.tx_data_ready);
    EXPECT_TRUE(2 == status_reg.rx_pipe_no);

    for (int i = 0; i < sizeof(expected_transport); i++)
        EXPECT_TRUE(expected_transport[i] == sent_data[i]) << "Got " \
                << (int)sent_data[i] << " Expected " << (int)expected_transport[i] \
                << " at position: " << i << std::endl;
}

} /*namespace test_nrf24l01*/
