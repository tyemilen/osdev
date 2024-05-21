#include "io/hal.h"

void io_write8(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a" (val), "Nd" (port));
}

unsigned char io_read8(unsigned short port) {
    unsigned char ret;

    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));

    return ret;
}

void io_write16(unsigned short port, unsigned char val) {
    __asm__ volatile ("outw %w0, %w1" : : "a" (val), "Nd" (port));
}

unsigned char io_read16(unsigned short port) {
    unsigned char ret;

    __asm__ volatile("inw %w1, %w0" : "=a"(ret) : "Nd"(port));

    return ret;
}

void io_write32(unsigned short port, u32 val) {
    __asm__ volatile("outl %0, %w1" : : "a" (val), "d" (port));
}