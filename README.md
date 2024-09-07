# Cyclic Buffer Implementation

# APIs
* init_cyclic_buf - Initialize a cyclic buffer, need to be done before usign
* add_to_buf - Add data into buffer
* read_byte - Read a single byte from buffer
* read_bytes - Read an array of bytes from buffer, need to free the memory by your own
* available_bytes - return the number of bytes available in the buffer
* check_cyclic - for debugging & verification usage