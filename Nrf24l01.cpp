
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
        struct Frame {
            uint8_t command;

            uint8_t channel     : 7, // Sets the frequency channel nRF24l01 operates on
                    Reserved    : 1;
        } frame;
        uint8_t raw_data[sizeof(Frame)];
    };

    const uint8_t channel_max = 127;

    if(channel_max < channel)
        return STATUS_OUT_OF_RANGE;

    RfSendData data = { 0 };
    data.frame.command = this->GetWriteAddress(REGISTER_RF_CH);
    data.frame.channel = channel;

    this->transport_->Send(data.raw_data, sizeof(RfSendData));

    return STATUS_OK ;
}

Status Nrf24l01::SetPayloadSize(uint8_t payload_size) {

    //TODO: Create define for this magic 0x20
    if (payload_size > 0x20)
        return STATUS_OUT_OF_RANGE;

    this->SetPayloadSize(nrf24_driver::R0, payload_size);
    this->SetPayloadSize(nrf24_driver::R1, payload_size);
    this->SetPayloadSize(nrf24_driver::R2, payload_size);
    this->SetPayloadSize(nrf24_driver::R3, payload_size);
    this->SetPayloadSize(nrf24_driver::R4, payload_size);
    this->SetPayloadSize(nrf24_driver::R5, payload_size);

    return STATUS_OK;
}

Status Nrf24l01::SetPayloadSize(nrf24_driver::Rx rx, uint8_t payload_size) {

    union PayloadSendData {
        struct Frame {
            uint8_t command;

            uint8_t rx_pw;
        } frame;
        uint8_t raw_data[sizeof(Frame)];
    };

    if (rx >= nrf24_driver::RxMax)
        return STATUS_OUT_OF_RANGE;

    //TODO: Create define for this magic 0x20
    if (payload_size > 0x20)
        return STATUS_OUT_OF_RANGE;

    PayloadSendData data = { 0 };
    data.frame.command = static_cast<uint8_t>(this->GetWriteAddress(REGISTER_RX_PW_P0) + this->GetPipeNumber(rx));
    data.frame.rx_pw = payload_size;

    this->transport_->Send(data.raw_data, sizeof(PayloadSendData));

    return STATUS_OK;
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

nrf24_driver::NrfStatusRegister Nrf24l01::GetStatus(void) {
    union StatusSendData {
        struct Frame {
            uint8_t command;
        } frame;
        uint8_t raw_data[sizeof(Frame)];;
    };

    StatusSendData send_data = { 0 };
    nrf24_driver::NrfStatusRegister status_reg = { 0 };

    send_data.frame.command = 0xFF;

    this->transport_->SendAndGet(send_data.raw_data, &status_reg.raw_data, sizeof(status_reg.raw_data));

    return status_reg;
}

uint8_t Nrf24l01::GetWriteAddress(RegisterMap rm) {
    return static_cast<uint8_t>(rm) + REGISTER_WRITE_BASE_ADDRESS;
}

uint8_t Nrf24l01::GetReadAddress(RegisterMap rm) {
    return static_cast<uint8_t>(rm) + REGISTER_READ_BASE_ADDRESS;
}

uint8_t Nrf24l01::GetPipeNumber(nrf24_driver::Rx rx) {
    if (nrf24_driver::R0 == rx)
        return 0;
    else if (nrf24_driver::R1 == rx)
        return 1;
    else if (nrf24_driver::R2 == rx)
        return 2;
    else if (nrf24_driver::R3 == rx)
        return 3;
    else if (nrf24_driver::R4 == rx)
        return 4;
    else if (nrf24_driver::R5 == rx)
        return 5;
    else
        return 0xFF;
}

} /*namespace nrf24l01_driver*/
