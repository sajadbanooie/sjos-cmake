//
// Created by simulation on 12/12/16.
//

#include <stdint.h>
#include <stddef.h>
#include "tty.h"

// creating entry for vga memory 0000[char][bg color][fg color]
static inline uint16_t make_vga_entry(char c, enum vga_color fg, enum vga_color bg)
{
    uint16_t c16 = (uint16_t) c;
    uint16_t color16 = fg | (bg << 4);
    return c16 | color16 << 8;
}

// terminal width and height
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

// vga memory is used to modify text mode screen
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

// position of the cursor and the place text should be printed on
static size_t cur_width = 0;
static size_t cur_height = 0;

// puts a character on terminal in a position
static void terminal_putchar(size_t row,size_t col, char c,enum vga_color fg, enum vga_color bg){
    VGA_MEMORY[row * VGA_WIDTH + col] = make_vga_entry(c,fg ,bg);
}

static void move_cursor(size_t row,size_t col){
    // TODO: implement cursor movement
}