#include "cyclic_buf.h"

#define RX_BUF_LEN  128
uint8_t rx_buf[RX_BUF_LEN] = {0};
uint16_t w_idx = 0, r_idx = 0;

// return reset of data length
static uint16_t add_data(uint16_t len)
{
  // move w_idx
  w_idx += len;
  if (w_idx >= RX_BUF_LEN) {

  }
}

uint16_t add_to_buf(uint8_t *data, uint16_t data_len)
{

}

uint8_t read_byte()
{

}
uint8_t *read_bytes(uint16_t len)
{

}
uint16_t available_bytes()
{

}