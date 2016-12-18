//
// Created by sajad on 12/12/16.
//

#include <stdint.h>
#include <stddef.h>
#include <ioports.h>
#include <stdarg.h>
#include "tty.h"
#include "version.h"

// CRTC registers
#define CRTC_ADDRESS 0x3D4
#define CRTC_DATA 0x3D5

// creating entry for vga memory 0000[char][bg color][fg color]
static inline uint16_t make_vga_entry(char c, uint8_t fg, uint8_t bg)
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
static uint8_t terminal_fgcolor = COLOR_LIGHT_GREY;
static uint8_t terminal_bgcolor = COLOR_BLACK;

// puts a character on terminal in a position
static void terminal_putchar_at(size_t row,size_t col, char c,enum vga_color fg, enum vga_color bg){
    VGA_MEMORY[row * VGA_WIDTH + col] = make_vga_entry(c,fg ,bg);
}

// move the cursor
static void move_cursor(size_t row,size_t col){
    unsigned short position = (unsigned short) ((row * 80) + col);

    // cursor LOW port to vga INDEX register
    outportb(0x3D4, 0x0F);
    outportb(0x3D5, (unsigned char) (position & 0xFF));
    // cursor HIGH port to vga INDEX register
    outportb(0x3D4, 0x0E);
    outportb(0x3D5, (unsigned char) ((position >> 8) & 0xFF));
}

static void terminal_putchar(char c, uint8_t fg, uint8_t bg) {
    if (c == '\n') {
        // handling new line
        cur_col = 0;
        cur_row++;
    } else {
        VGA_MEMORY[cur_row * VGA_WIDTH + cur_col] = make_vga_entry(c, fg, bg);
        cur_col++;
    }
    if (cur_col >= VGA_WIDTH) {
        cur_col = 0;
        cur_row++;
    }
    move_cursor(cur_row, cur_col);
#if LOG_LEVEL == LOG_DEBUG
    BochsConsolePrintChar((uint8_t) c);
#endif
}

void print_unsigned_int(unsigned int a) {
    if (a / 10 != 0) {
        print_unsigned_int(a / 10);
    }
    terminal_putchar((char) (a % 10 + '0'), terminal_fgcolor, terminal_bgcolor);
}

static void print_signed_int(signed int a){
    if (a >= 0)
        return print_unsigned_int((unsigned int) a);
    terminal_putchar('-',terminal_fgcolor,terminal_bgcolor);
    print_unsigned_int((unsigned int) (-a));
}

static void print_hex(unsigned int a){
    static char digits[] = {'0', '1', '2', '3', '4', '5',
                            '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    for (int i = 7; i > -1; i--) {
        terminal_putchar(digits[(a & (0xF << i * 4)) >> i * 4], terminal_fgcolor, terminal_bgcolor);
    }
}

void printk(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != 0) {
        if (*format == '%') {
            switch (*(++format)) {
                case 'd':
                    print_signed_int(va_arg(args, int));
                    break;
                case 'u':
                    print_signed_int(va_arg(args, unsigned int));
                    break;
                case 'x':
                    print_hex(va_arg(args, unsigned int));
                    break;
                case 's':
                    printk(va_arg(args, const char *));
                    break;
                default:
                    break;
            }
            format++;
        }
        terminal_putchar(*(format++), terminal_fgcolor, terminal_bgcolor);
    }
}

void klog(const char *tag, uint8_t level, const char *format, ...) {
    if (level < LOG_LEVEL)
        return;
    uint8_t pt_color = terminal_fgcolor;

    switch (level) {
        case LOG_ERROR:
            terminal_fgcolor = COLOR_RED;
            break;
        case LOG_WARN:
            terminal_fgcolor = COLOR_LIGHT_RED;
            break;
        case LOG_INFO:
            terminal_fgcolor = COLOR_LIGHT_GREEN;
            break;
        case LOG_DEBUG:
            terminal_fgcolor = COLOR_LIGHT_GREY;
            break;
        default:
            break;
    }

    printk("[%s]: ", tag);

    terminal_fgcolor = pt_color;

    va_list args;
    va_start(args, format);

    while (*format != 0) {
        if (*format == '%') {
            switch (*(++format)) {
                case 'd':
                    print_signed_int(va_arg(args, int));
                    break;
                case 'u':
                    print_signed_int(va_arg(args, unsigned int));
                    break;
                case 'x':
                    print_hex(va_arg(args, unsigned int));
                    break;
                default:
                    break;
            }
            format++;
        }
        terminal_putchar(*(format++), terminal_fgcolor, terminal_bgcolor);
    }
    terminal_putchar('\n', terminal_fgcolor, terminal_bgcolor);
}

