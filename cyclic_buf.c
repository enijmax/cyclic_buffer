#include <string.h>
#include <stdarg.h>
#include "cyclic_buf.h"

static uint8_t *s_buf_ptr = NULL;
static uint16_t s_buf_max_size = 0;
static uint16_t s_r_idx, s_remain_data_len;


static void LOG(const char *format, ...) {
  va_list arg_ptr;

  va_start(arg_ptr, format);
  vprintf(format, arg_ptr);
  va_end(arg_ptr);
}
/*
 * @brief: ex: 5 buf_size, r_idx = 0, remain_data_len = 3
 */
static uint16_t get_w_idx(void)
{
  if (s_remain_data_len == 0 || \
  s_buf_ptr == NULL)
    return 0;
  return (s_r_idx + s_remain_data_len)%s_buf_max_size;
}

static bool append_data(uint8_t *data, uint16_t data_len)
{
  uint16_t src_idx = 0;
  if (s_buf_ptr == NULL || \
      data == NULL || \
      data_len == 0 || \
      data_len > s_buf_max_size)
      return false;
  uint16_t w_idx = get_w_idx();
  // get the size after w_idx to the end of buffer
  uint16_t copied_len = s_buf_max_size - w_idx;
  memcpy(&s_buf_ptr[w_idx], &data[src_idx], copied_len);
  if (copied_len < data_len) {
    // still something left behind
    src_idx += copied_len;
    copied_len = data_len - copied_len;
    memcpy(&s_buf_ptr[0], &data[src_idx], copied_len);
  }
  s_remain_data_len = (s_remain_data_len+data_len);
  if (s_remain_data_len > s_buf_max_size) {
    s_r_idx += (s_remain_data_len%s_buf_max_size);
    s_remain_data_len = s_buf_max_size;
  }
  LOG("r_idx = %d, w_idx=%d, remain_data_len = %d\r\n", s_r_idx, w_idx, s_remain_data_len);
  return true;
}
/*
 * @brief: 
 * 
 */
bool init_cyclic_buf(uint8_t *buf_ptr, uint16_t buf_max_size)
{
  if (buf_ptr == NULL || buf_max_size == 0)
    return false;

  s_buf_ptr = buf_ptr;
  s_buf_max_size = buf_max_size;
  s_remain_data_len = 0;
  s_r_idx = 0;
  return true;
}

uint16_t add_to_buf(uint8_t *data, uint16_t data_len)
{
  if (!append_data(data, data_len))
  {
    return 0;
  }
  return 1;
}

uint8_t read_byte()
{
  return 0;
}
uint8_t *read_bytes(uint16_t len)
{
  return NULL;
}
uint16_t available_bytes()
{
  return 0;
}