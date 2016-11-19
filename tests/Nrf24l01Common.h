#pragma once

#include "IGpioDriver.h"
#include "ITransport.h"

namespace test_nrf24l01 {

class GpioMock : public gpio_driver::IGpio {

public:

    GpioMock(
            uint16_t *set_cnt,
            uint16_t *clear_cnt,
            uint16_t *toggle_cnt,
            uint8_t *state)
        :
            set_cnt_(set_cnt),
            clear_cnt_(clear_cnt),
            toggle_cnt_(toggle_cnt),
            state_(state)
    {}

    GpioMock() {
        set_cnt_    = &mock_set_cnt_;
        clear_cnt_  = &mock_clear_cnt_;
        toggle_cnt_ = &mock_toggle_cnt_;
        state_      = &mock_state_;
    }

    virtual void Set(void) { (*set_cnt_)++; }
    virtual void Clear(void) { (*clear_cnt_)++; }
    virtual void Toggle(void) { (*toggle_cnt_)++; }
    virtual uint8_t GetState(void) { return *state_; }

private:
    uint16_t    *set_cnt_;
    uint16_t    *clear_cnt_;
    uint16_t    *toggle_cnt_;
    uint8_t     *state_;

    uint16_t    mock_set_cnt_;
    uint16_t    mock_clear_cnt_;
    uint16_t    mock_toggle_cnt_;
    uint8_t     mock_state_;
};

class TransportMock : public transport::ITransport {

public:

    TransportMock(
            uint8_t     *sent_data,
            uint16_t    sent_data_size)
        :
            sent_data_(sent_data),
            sent_data_size_(sent_data_size),
            sent_data_idx_(0)
    {
        memset(sent_data_, 0, sent_data_size_);
    }

    virtual void Send(uint8_t send_buff[], uint16_t size) {

        for(uint16_t i = 0; i < size; i++) {
            if((i + sent_data_idx_) > sent_data_size_) {
                EXPECT_TRUE(0);
            }

            sent_data_[sent_data_idx_++] = send_buff[i];
        }
    }

    virtual void Get(uint8_t recv_buff[], uint16_t size) { }
    virtual void SendAndGet(uint8_t send_buff[], uint8_t recv_buff[], uint16_t size) {}

    uint8_t         *sent_data_;
    const uint16_t  sent_data_size_;
    uint16_t        sent_data_idx_;
};


} /* namespace test_nrf24l01*/

