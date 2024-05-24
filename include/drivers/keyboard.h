#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#define KEY_ENTER 0x1c
#define KEY_BACKSPACE 0xe
#define KEY_SPACE 0x39

unsigned char keyboard_get_key();
char keyboard_key2ascii(unsigned char code);

#endif // KEYBOARD_H_