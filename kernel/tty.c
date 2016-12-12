//
// Created by simulation on 12/12/16.
//

#include <stdint.h>
#include <stddef.h>
#include <ioports.h>
#include "tty.h"
#include "version.h"

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
static size_t cur_row = 0;
static size_t cur_col = 0;

// terminal foreground and background color
static enum vga_color terminal_fgcolor = vga_color::COLOR_BLACK;
static enum vga_color terminal_bgcolor = vga_color::COLOR_WHITE;

// puts a character on terminal in a position
static void terminal_putchar_at(size_t row,size_t col, char c,enum vga_color fg, enum vga_color bg){
    VGA_MEMORY[row * VGA_WIDTH + col] = make_vga_entry(c,fg ,bg);
}


static void move_cursor(size_t row,size_t col){
    // TODO: implement cursor movement
}

static void terminal_putchar(char c, enum vga_color fg, enum vga_color bg){
    VGA_MEMORY[cur_col * VGA_WIDTH + cur_row] = make_vga_entry(c,fg ,bg);
    cur_row++;
    if (cur_col >= VGA_WIDTH){
        cur_row = 0;
        cur_col++;
    }
    move_cursor(cur_col,cur_row);
#if DEBUG
    BochsConsolePrintChar((uint8_t) c);
#endif
}

static void print_unsigned_int(unsigned int a){
    do {
        terminal_putchar((char) (a % 10 + '0'), terminal_fgcolor, terminal_bgcolor);
        a /= 10;
    } while (a != 0);
}

static void print_signed_int(signed int a){
    if (a >= 0)
        return print_unsigned_int((unsigned int) a);
    terminal_putchar('-',terminal_fgcolor,terminal_bgcolor);
    print_unsigned_int((unsigned int) (-a));
}

static void print_hex(unsigned int a){
    static char digits[] = {'0','1','2','3','4','5',
                            '6','7','8','9','A','B','C','D','F'};

    for (int i = 0;i < 8;i++){
        terminal_putchar(digits[a % 16],terminal_fgcolor,terminal_bgcolor);
        a /= 16;
    }
}

void printk(const char *format, ...) {
    // TODO: implementation for printk and logging
}
