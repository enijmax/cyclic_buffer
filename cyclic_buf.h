#ifndef __CYCLIC_BUF_H__
#define __CYCLIC_BUF_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool init_cyclic_buf(uint8_t *buf_ptr, uint16_t buf_max_size);
uint16_t add_to_buf(uint8_t *data, uint16_t data_len);
uint8_t read_byte();
uint8_t *read_bytes(uint16_t len);
uint16_t available_bytes(); 

#endif