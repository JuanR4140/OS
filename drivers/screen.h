#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
/*#define WHITE_ON_BLACK 0x0f*/

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void clear_screen();
void x_of_doom();
void fill(int code);
void color_test();
// int print_char(char c, int col, int row, char attr);
void kprint_at(char *message, int col, int row);
void kprint(char *message);
void kprint_backspace();

#endif