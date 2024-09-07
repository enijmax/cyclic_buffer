#ifndef __CYCLIC_BUF_H__
#define __CYCLIC_BUF_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool init_cyclic_buf(uint8_t *buf_ptr, const uint16_t buf_max_size);
bool add_to_buf(uint8_t *data, const uint16_t data_len);
uint8_t read_byte();
uint8_t *read_bytes(const uint16_t len);
uint16_t available_bytes(); 
bool check_cyclic(const uint16_t r_idx, const uint16_t available_len);

#endif