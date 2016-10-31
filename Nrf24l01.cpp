
#include "Nrf24l01.h"

namespace nrf24l01_driver {

Nrf24l01::Nrf24l01(
        transport::ITransport *transport,
        gpio_driver::IGpio *chip_enable)
    :
        transport_(transport),
        chip_enable_(chip_enable)
{
    // by default nrf24l01 will be disabled.
    // setting logic '1'.
    chip_enable_->Set();
}

Status Nrf24l01::SetDefaults(void) {

    return STATUS_FAILURE;
}

Status Nrf24l01::SetRfChannel(uint8_t channel) {

    return STATUS_FAILURE;
}

Status Nrf24l01::SetPayloadSize(uint8_t payload_size) {

    return STATUS_FAILURE;
}

Status Nrf24l01::SetRetries(uint8_t delay, uint8_t retries) {

    return STATUS_FAILURE;
}

Status Nrf24l01::SetRxAddress(nrf24_driver::Rx rx, uint8_t address[], uint8_t size) {

    return STATUS_FAILURE;
}

Status Nrf24l01::SetTxAddress(nrf24_driver::Tx tx, uint8_t address[], uint8_t size) {

    return STATUS_FAILURE;
}

} /*namespace nrf24l01_driver*/
