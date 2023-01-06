#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"
#include <stdint.h>
int WHITE_ON_BLACK = 0x0f;

int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

void kprint_at(char *message, int col, int row){
  // print_char(message[0], 0, 1, 0);
  // print_char('Z', 0, 3, 0);
  int offset;
  if(col >= 0 && row >= 0) offset = get_offset(col, row);
  else{
    offset = get_cursor_offset();
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }

  int i = 0;
  while(message[i] != 0){
    offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }
}

void kprint(char *message){
  kprint_at(message, -1, -1);
}

void kprint_backspace() {
  int offset = get_cursor_offset()-2;
  int row = get_offset_row(offset);
  int col = get_offset_col(offset);
  print_char(0x08, col, row, WHITE_ON_BLACK);
}

int print_char(char c, int col, int row, char attr){
  uint8_t *screen = (uint8_t*) VIDEO_ADDRESS;

  if(!attr) attr = WHITE_ON_BLACK;

  if((col > MAX_COLS || row > MAX_ROWS)){
    x_of_doom();
    return -1;
  }
  
  int offset;

  if(col >= 0 && row >= 0) offset = get_offset(col, row);
  else offset = get_cursor_offset();

  if(c == '\n'){
    row = get_offset_row(offset);
    offset = get_offset(0, row+1);
  }else if(c == 0x08){ // Backspace
    screen += offset;
    *screen = ' ';
    /*screen += 1;
    *screen = attr;
    offset += 2;*/
  }else{
    screen += offset;
    *screen = c;
    screen += 1;
    *screen = attr;
    offset += 2;
  }

  if(offset >= MAX_ROWS * MAX_COLS * 2){
    int i;
    for(i = 1; i < MAX_ROWS; i++){
      memory_copy((uint8_t*)(get_offset(0, i) + VIDEO_ADDRESS), (uint8_t*)(get_offset(0, i-1) + VIDEO_ADDRESS), MAX_COLS * 2);
    }

      char *last_line = (char*) (get_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS);
      for(i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

      offset -= 2 * MAX_COLS;
  }
  
  set_cursor_offset(offset);
  return offset;
}

int get_cursor_offset(){
  port_byte_out(REG_SCREEN_CTRL, 14);
  int offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);
  return offset * 2;
}

void set_cursor_offset(int offset){
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (char)((unsigned) offset >> 8)); // These used to be unsigned char
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (char)((unsigned) offset & 0xff));
}

int get_offset(int col, int row){
  return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset){
  return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset){
  return (offset - (get_offset_row(offset)*2*MAX_COLS))/2;
}

void clear_screen(){
  int screen_size = MAX_COLS * MAX_ROWS;
  uint8_t *screen = (uint8_t*) VIDEO_ADDRESS;
  
  for(int i = 0; i < screen_size; i++){
    screen += i * 2;
    *screen = ' ';
    screen += 1;
    *screen = WHITE_ON_BLACK;
    screen = (uint8_t*) 0xb8000;
  }
  set_cursor_offset(0);
}

void fill(int code){
  WHITE_ON_BLACK = code;
  char* vidmem = (char *) 0xb8000;
  for(int i = 0; i < 2000; i++){
    *vidmem = ' ';
    vidmem++;
    *vidmem = code;
    vidmem++;
  }
}

void color_test(){
  char* vidmem = (char *) 0xb8000;
  int attr = 0;
  for(int i = 0; i < 2000; i++){
    *vidmem = ' ';
    vidmem++;
    *vidmem = attr;
    vidmem++;
    attr++;
    if(attr == 255) attr = 0;
  }
}

void x_of_doom(){
  char* vidmem = (char *) 0xb8000;
  for(int i = 0; i < 2000; i++){
    *vidmem = 'X';
    vidmem++;
    // 0x04 red on black
    // 0x1f white on blue
    *vidmem = 0x1f;
    vidmem++;
  }
}
