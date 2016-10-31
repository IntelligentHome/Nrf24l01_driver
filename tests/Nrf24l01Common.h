#pragma once

#include "IGpioDriver.h"
#include "ITransport.h"

namespace test_nrf24l01 {

class GpioMock : public gpio_driver::IGpio {

public:

    virtual void Set(void) { /*do nothing*/ }
    virtual void Clear(void) { /*do nothing*/ }
    virtual void Toggle(void) { /*do nothing*/ }
    virtual uint8_t GetState(void) { return 0; }
};

class TransportMock : public transport::ITransport {

public:

    virtual void Send(uint8_t send_buff[], uint16_t size) { /*do nothing*/ }
    virtual void Get(uint8_t recv_buff[], uint16_t size) { /*do nothing*/ }
    virtual void SendAndGet(uint8_t send_buff[], uint8_t recv_buff[], uint16_t size) { /*do nothing*/ }
};

} /* namespace test_nrf24l01*/

