#include "gtest/gtest.h"
#include "Nrf24l01.h"
#include "Nrf24l01Common.h"

uint8_t g_set_counter = 0;
uint8_t g_clear_counter = 0;
uint8_t g_toggle_counter = 0;

class GpioMockInit : public test_nrf24l01::GpioMock {

public:

    GpioMockInit() {
        g_set_counter = 0;
        g_clear_counter = 0;
        g_toggle_counter = 0;
    }

    virtual void Set(void) { g_set_counter++; }
    virtual void Clear(void) { g_clear_counter++; }
    virtual void Toggle(void) { g_toggle_counter++; }
};

/*
 On init nrf24l01 driver should:
    1. Set high logic level on gpio responsible for chip enable.
 */
TEST(Nrf24l01, Init) {

    GpioMockInit gpio;
    test_nrf24l01::TransportMock transport;

    nrf24l01_driver::Nrf24l01 nrf(
            &transport,
            &gpio);

    EXPECT_TRUE(1 == g_set_counter);
    EXPECT_TRUE(0 == g_clear_counter);
    EXPECT_TRUE(0 == g_toggle_counter);
}
