#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../cpu/ports.h"
#include <stdint.h>

void kernel_main() {
  isr_install();
  irq_install();
  kprint("Type HELP for some commands\n> ");
}

void user_input(char *input){
  if(strcmp(input, "HELP") == 0){
    kprint("[anything] = echoes text that was typed\n\n");
    kprint("CLEAR = clears screen\n\n");
    kprint("MEM = get memory usage\n");
    kprint("MALLOC = *allocates* memory\n");
    kprint("FREE = *frees* memory\n\n");
    kprint("COLOR TEST = tests display colors\n");
    kprint("FILL BLACK = fills terminal with black\n");
    kprint("FILL RED = fills terminal with red\n");
    kprint("FILL GREEN = fills terminal with green\n");
    kprint("FILL BLUE = fills terminal with blue\n\n");
    kprint("EXIT = suspends CPU execution\n");
  }else if(strcmp(input, "CLEAR") == 0){
    clear_screen();
  }else if(strcmp(input, "MEM") == 0){
    uint32_t memory = memory_get();
    char memory_string[16] = "";
    hex_to_ascii(memory, memory_string);
    kprint("Memory usage: ");
    kprint(memory_string);
    kprint("\n");
  }else if(strcmp(input, "MALLOC") == 0){
    uint32_t physical_address;
    // implementation is just a pointer to some
    // free memory which just keeps growing.
    uint32_t memory = memory_allocate(1000, 1, &physical_address);
    char memory_string[16] = "";
    hex_to_ascii(memory, memory_string);
    char physical_string[16] = "";
    hex_to_ascii(physical_address, physical_string);
    kprint("Memory: ");
    kprint(memory_string);
    kprint(", physical address: ");
    kprint(physical_string);
    kprint("\n");
  }else if(strcmp(input, "FREE") == 0){
    kprint("Freeing memory..\n");
    memory_free();
    kprint("Memory freed.\n");
  }else if(strcmp(input, "COLOR TEST") == 0){
    color_test();
    kprint_at("COLOR TEST", 35, 0);
  }else if(strcmp(input, "FILL BLACK") == 0){
    fill(0x0f);
    kprint_at("BLACK", 0, 1);
  }else if(strcmp(input, "FILL BLUE") == 0){
    fill(0x1f);
    kprint_at("COLOR TEST\nBLUE", 35, 0);
  }else if(strcmp(input, "FILL GREEN") == 0){
    fill(0x2f);
    kprint_at("COLOR TEST\nGREEN", 35, 0);
  }else if(strcmp(input, "FILL RED") == 0){
    fill(0x4f);
    kprint_at("COLOR TEST\nRED", 35, 0);
  }else if(strcmp(input, "EXIT") == 0){
    clear_screen();
    kprint_at("Shutting down..\n", 35, 0);
    // kprint_at("CPU suspended....\n", 35, 0);
    port_word_out(0xB004, 0x2000); // <-- BOCHS-SPECIFIC. DOES NOT WORK ON REAL HARDWARE.
    // asm volatile("hlt");
    // asm volatile("jmp $0xAAAA,$0x0000");
  }else{
    kprint(input);
  }
  kprint("\n> ");
}