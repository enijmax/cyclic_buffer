#include "cyclic_buf.h"

#define MAX_BUF 10

void dump_data(uint8_t *data, uint16_t size)
{
  for (int i =0;i <size;i++) {
    printf("%02X ", data[i]);
  }
  printf("\r\n");
}

int main(void)
{
  uint8_t my_cyclic_buf[MAX_BUF] ={0};
  uint8_t test_data[5] = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E};
  uint8_t test_data_eight[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  printf("Test Cyclic buffer\r\n");
  if (!init_cyclic_buf(my_cyclic_buf, MAX_BUF)) {
    printf("init buf failed\r\n");
    return 0;
  }
  
  add_to_buf(test_data_eight, 8);
  dump_data(my_cyclic_buf, MAX_BUF);
  add_to_buf(test_data, 5);
  dump_data(my_cyclic_buf, MAX_BUF);
  add_to_buf(test_data_eight, 8);
  dump_data(my_cyclic_buf, MAX_BUF);
  return 1;
}