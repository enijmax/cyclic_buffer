#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cyclic_buf.h"

/*
 * cyclic buffer specification
 * * max store bytes = s_buf_max_size
 * * w_idx should be the next write position
 * * r_idx should be the next read position
 * r_idx and w_idx are in the same position, it means either no data available, or the max data available
 * s_remain_data_len indicate how many data stored in the buffer, it should be smaller then s_buf_max_size
 */

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
  if (s_remain_data_len == 0 && \
  s_buf_ptr == NULL)
    return 0;
  return (s_r_idx + s_remain_data_len)%s_buf_max_size;
}

/*
 * @brief: 
 * 
 */
bool init_cyclic_buf(uint8_t *buf_ptr, const uint16_t buf_max_size)
{
  if (buf_ptr == NULL || buf_max_size == 0)
    return false;

  s_buf_ptr = buf_ptr;
  s_buf_max_size = buf_max_size;
  s_remain_data_len = 0;
  s_r_idx = 0;
  return true;
}

bool add_to_buf(uint8_t *data, const uint16_t data_len)
{
  uint16_t src_idx = 0;
  if (s_buf_ptr == NULL || \
      data == NULL || \
      data_len == 0)
      return false;
  uint16_t w_idx = get_w_idx();
  uint16_t copied_len = 0, uncopied_len = data_len;
  while ((w_idx + uncopied_len) > s_buf_max_size) {
    // get the size after w_idx to the end of buffer
    copied_len = s_buf_max_size - w_idx;
    memcpy(&s_buf_ptr[w_idx], &data[src_idx], copied_len * sizeof(uint8_t));
    if (w_idx < s_r_idx) {
      // --w---r----
      // w/r--------
      s_r_idx = 0;
    }
    w_idx = 0;
    src_idx += copied_len;
    uncopied_len -= copied_len;
  }
  // remain data is smaller then max_buf size
  memcpy(&s_buf_ptr[w_idx], &data[src_idx], uncopied_len * sizeof(uint8_t));
  w_idx += uncopied_len;
  // calc r_idx new position if new added data overwrite old data
  s_remain_data_len = ((s_remain_data_len + data_len) > s_buf_max_size)?s_buf_max_size:(s_remain_data_len + data_len);

  if ((w_idx - uncopied_len) <= s_r_idx &&
      w_idx > s_r_idx &&
      s_remain_data_len == s_buf_max_size) {
    // w---r----- or 
    // w/r------- to
    // ------w/r-
    s_r_idx = w_idx;
  }

  LOG("r_idx = %d, w_idx=%d, remain_data_len = %d\r\n", s_r_idx, w_idx, s_remain_data_len);
  return true;
}

uint8_t read_byte()
{
  if (s_remain_data_len == 0) {
    return 0;
  }
  uint8_t tmp_r_idx = s_r_idx;
  s_remain_data_len -= 1;
  s_r_idx = (s_r_idx + 1)%s_buf_max_size;
  return s_buf_ptr[tmp_r_idx];
}

uint8_t *read_bytes(const uint16_t len)
{
  if (len > s_remain_data_len)
    return NULL;
  uint8_t *ret = (uint8_t *)malloc(sizeof(uint8_t) * len);
  uint16_t cpy_len = 0, uncpy_len = len;
  if (s_r_idx + uncpy_len > s_buf_max_size) {
    // copy to the end of buffer first
    cpy_len = s_buf_max_size - s_r_idx;
    memcpy(ret, &s_buf_ptr[s_r_idx], cpy_len * sizeof(uint8_t));
    s_r_idx = 0;
    s_remain_data_len -= cpy_len;
    uncpy_len -= cpy_len;
  }
  memcpy(&ret[cpy_len], &s_buf_ptr[s_r_idx], s_remain_data_len * sizeof(uint8_t));
  s_r_idx += s_remain_data_len;
  return ret;
}

uint16_t available_bytes()
{
  return s_remain_data_len;
}

bool check_cyclic(const uint16_t r_idx, const uint16_t available_len)
{
  if (r_idx != s_r_idx)
  {
    printf("expect r_id is %d, but it is %d\r\n", r_idx, s_r_idx);
    return false;
  }

  if (available_len != s_remain_data_len) {
    printf("expect remained data length is %d, but it is %d\r\n", available_len, s_remain_data_len);
    return false;
  }
  return true;
}