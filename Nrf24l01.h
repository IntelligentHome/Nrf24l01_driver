#pragma once

#include "INrf24.h"
#include "IGpioDriver.h"
#include "ITransport.h"

namespace nrf24l01_driver {

class Nrf24l01 : public nrf24_driver::INrf24 {

public:

    Nrf24l01(
            transport::ITransport *transport,
            gpio_driver::IGpio *chip_enable);

    virtual Status SetDefaults(void);
    virtual Status SetRfChannel(uint8_t channel);
    virtual Status SetPayloadSize(uint8_t payload_size);
    virtual Status SetRetries(uint8_t delay, uint8_t retries);
    virtual Status SetRxAddress(nrf24_driver::Rx rx, uint8_t address[], uint8_t size);
    virtual Status SetTxAddress(nrf24_driver::Tx tx, uint8_t address[], uint8_t size);

private:
    transport::ITransport *transport_;
    gpio_driver::IGpio *chip_enable_;
};

} /*namespace nrf24l01_driver*/
