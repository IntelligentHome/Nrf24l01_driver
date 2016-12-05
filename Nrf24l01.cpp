
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

    union RetriesSendData {
        struct Frame {
            uint8_t command;

            uint8_t ARC : 4,
                    ARD : 4;
        } frame;
        uint8_t raw_data[sizeof(Frame)];
    };

    const uint8_t kMaxDelay = 0x0F;
    const uint8_t kMaxRetries = 0x0F;

    if ((delay > kMaxDelay) ||
        (retries > kMaxRetries))
        return STATUS_OUT_OF_RANGE;

    RetriesSendData data = { 0 };
    data.frame.command = this->GetWriteAddress(REGISTER_SETUP_RETR);
    data.frame.ARC = retries;
    data.frame.ARD = delay;

    this->transport_->Send(data.raw_data, sizeof(RetriesSendData));

    return STATUS_OK;
}

Status Nrf24l01::SetAddress(nrf24_driver::Rx rx, const uint8_t address[], uint8_t size) {

    union Address5BytesSendData {
        struct Frame {
            uint8_t command;
            uint8_t address[5];
        } frame;
        uint8_t raw_data[sizeof(Frame)];
    };

    union Address1ByteSendData {
        struct Frame {
            uint8_t command;
            uint8_t address;
        } frame;
        uint8_t raw_data[sizeof(Frame)];
    };

    const uint8_t address_size = this->GetAddressSize(rx);
    uint8_t send_data[sizeof(Address5BytesSendData)] = { 0 };
    uint8_t send_data_size = 0;

    if(address_size != size)
        return STATUS_OUT_OF_RANGE;

    switch (rx) {
        case nrf24_driver::R0 :
        case nrf24_driver::R1 :
            {
                send_data_size = sizeof(Address5BytesSendData);
                Address5BytesSendData *data = (Address5BytesSendData *)send_data;

                data->frame.command = this->GetWriteAddress(rx);
                for (uint8_t i = 0; i < size; i++)
                    data->frame.address[i] = address[i];
            }
            break;

        case nrf24_driver::R2 :
        case nrf24_driver::R3 :
        case nrf24_driver::R4 :
        case nrf24_driver::R5 :
            {
                send_data_size = sizeof(Address1ByteSendData);
                Address1ByteSendData *data = (Address1ByteSendData *)send_data;

                data->frame.command = this->GetWriteAddress(rx);
                data->frame.address = address[0];
            }
            break;

        default :
            return STATUS_FAILURE;
    }

    this->transport_->Send(send_data, send_data_size);

    return STATUS_OK;
}

Status Nrf24l01::SetAddress(nrf24_driver::Tx tx, const uint8_t address[], uint8_t size) {

    union AddressSendData {
        struct Frame {
            uint8_t command;
            uint8_t address[5];
        } frame;
        uint8_t raw_data[sizeof(Frame)];
    };

    const uint8_t address_size = this->GetAddressSize(tx);
    AddressSendData send_data = { 0 };

    if (address_size != size)
        return STATUS_OUT_OF_RANGE;

    send_data.frame.command = this->GetWriteAddress(tx);
    for (uint8_t i = 0; i < size; i++)
        send_data.frame.address[i] = address[i];

    this->transport_->Send(send_data.raw_data, sizeof(send_data.raw_data));

    return STATUS_OK;
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

Status Nrf24l01::GetPayload(uint8_t payload[], const uint8_t size) {
    union GetPayloadData {
        struct Frame {
            uint8_t command;
            uint8_t payload[0x20];
        } frame;
        uint8_t raw_data[sizeof(Frame)];
    };

    GetPayloadData send_data = { 0 };
    GetPayloadData get_data = { 0 };

    if (size > 0x20)
        return STATUS_OUT_OF_RANGE;

    send_data.frame.command = R_RX_PAYLOAD;
    this->transport_->SendAndGet(send_data.raw_data, get_data.raw_data, sizeof(get_data.raw_data));

    for (int i = 0; i < size; i++)
        payload[i] = get_data.frame.payload[i];

    return STATUS_OK;
}

uint8_t Nrf24l01::GetWriteAddress(RegisterMap rm) {
    return static_cast<uint8_t>(rm) + REGISTER_WRITE_BASE_ADDRESS;
}

uint8_t Nrf24l01::GetWriteAddress(nrf24_driver::Rx rx) {

    switch (rx) {
        case nrf24_driver::R0 :
            return this->GetWriteAddress(REGISTER_RX_ADDR_P0);

        case nrf24_driver::R1 :
            return this->GetWriteAddress(REGISTER_RX_ADDR_P1);

        case nrf24_driver::R2 :
            return this->GetWriteAddress(REGISTER_RX_ADDR_P2);

        case nrf24_driver::R3 :
            return this->GetWriteAddress(REGISTER_RX_ADDR_P3);

        case nrf24_driver::R4 :
            return this->GetWriteAddress(REGISTER_RX_ADDR_P4);

        case nrf24_driver::R5 :
            return this->GetWriteAddress(REGISTER_RX_ADDR_P5);

        default :
            //TODO: Trigger reset ?
            return 0xFF;
    }
}

uint8_t Nrf24l01::GetWriteAddress(nrf24_driver::Tx tx) {

    switch (tx) {
        case nrf24_driver::T0 :
            return this->GetWriteAddress(REGISTER_TX_ADDR);

        default :
            //TODO: Trigger reset ?
            return 0xFF;
    }
}

uint8_t Nrf24l01::GetReadAddress(RegisterMap rm) {
    return static_cast<uint8_t>(rm) + REGISTER_READ_BASE_ADDRESS;
}

uint8_t Nrf24l01::GetReadAddress(nrf24_driver::Rx rx) {

    switch (rx) {
        case nrf24_driver::R0 :
            return this->GetReadAddress(REGISTER_RX_ADDR_P0);

        case nrf24_driver::R1 :
            return this->GetReadAddress(REGISTER_RX_ADDR_P1);

        case nrf24_driver::R2 :
            return this->GetReadAddress(REGISTER_RX_ADDR_P2);

        case nrf24_driver::R3 :
            return this->GetReadAddress(REGISTER_RX_ADDR_P3);

        case nrf24_driver::R4 :
            return this->GetReadAddress(REGISTER_RX_ADDR_P4);

        case nrf24_driver::R5 :
            return this->GetReadAddress(REGISTER_RX_ADDR_P5);

        default :
            //TODO: Trigger reset ?
            return 0xFF;
    }
}

uint8_t Nrf24l01::GetReadAddress(nrf24_driver::Tx tx) {

    switch (tx) {
        case nrf24_driver::T0 :
            return this->GetReadAddress(REGISTER_TX_ADDR);

        default :
            //TODO: Trigger reset ?
            return 0xFF;
    }
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

uint8_t Nrf24l01::GetAddressSize(nrf24_driver::Rx rx) {

    switch (rx) {
        case nrf24_driver::R0 :
        case nrf24_driver::R1 :
            return 5;

        case nrf24_driver::R2 :
        case nrf24_driver::R3 :
        case nrf24_driver::R4 :
        case nrf24_driver::R5 :
            return 1;

        default :
            return 0;
    }
}

uint8_t Nrf24l01::GetAddressSize(nrf24_driver::Tx tx) {

    switch (tx) {
        case nrf24_driver::T0 :
            return 5;

        default :
            return 0;
    }
}

} /*namespace nrf24l01_driver*/
