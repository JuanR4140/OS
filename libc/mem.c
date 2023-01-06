#include "mem.h"

void memory_copy(uint8_t *source, uint8_t *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memory_set(uint8_t *dest, uint8_t val, uint32_t len) {
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

// should be computed at linktime;
// but hardcoded for now
// (kernel starts at 0x10000 as defined in the Makefile)
uint32_t free_memory_address = 0x10000;
// implementation is just a pointer to some free
// memory which just keeps growing
uint32_t memory_allocate(uint32_t size, int align, uint32_t *physical_address){
  // Pages are aligned to 4K, 0x10000
  if(align == 1 && (free_memory_address & 0xFFFFF000)){
    free_memory_address &= 0xFFFFF000;
    free_memory_address += 0x1000;
  }
  // Save physical address
  if (physical_address) *physical_address = free_memory_address;
  uint32_t ret = free_memory_address;
  free_memory_address += size; // Incrementing pointer
  return ret;
}

void memory_free(){
  free_memory_address = 0x10000;
}

uint32_t memory_get(){
  free_memory_address &= 0xFFFFF000;
  return free_memory_address;
}