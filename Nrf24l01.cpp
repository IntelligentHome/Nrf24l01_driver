
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
    this->SetDefaults();
}

Status Nrf24l01::SetDefaults(void) {

    this->SetRfChannel(0x60);
    return STATUS_FAILURE;
}

Status Nrf24l01::SetRfChannel(uint8_t channel) {

    union RfSendData {
        struct Frame{
            uint8_t command;

            uint8_t channel		: 7, // Sets the frequency channel nRF24l01 operates on
                    Reserved	: 1;
        } frame;
        uint8_t raw_data[sizeof(Frame)];
    };

    const uint8_t write_address = 0x25;
    const uint8_t channel_max = 127;

    if(channel_max < channel)
        return STATUS_FAILURE;

    RfSendData data = { .frame = { .command = write_address, .channel = channel } };

    this->transport_->Send(data.raw_data, sizeof(RfSendData));

    return STATUS_OK ;
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
