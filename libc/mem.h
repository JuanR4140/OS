#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stddef.h>

void memory_copy(uint8_t *source, uint8_t *dest, int nbytes);
void memory_set(uint8_t *dest, uint8_t val, uint32_t len);
uint32_t memory_allocate(size_t size, int align, uint32_t *physical_address);
void memory_free();
uint32_t memory_get();

#endif
