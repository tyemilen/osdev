#include "memory.h"

void *memset(void *ptr, int value, size_t num) {
	unsigned char *ptr_byte = (unsigned char *)ptr;

	for (size_t i = 0; i < num; ptr_byte[i] = (unsigned char)value, i++);

	return ptr;
};

void *memcpy(void *restrict dstptr, const void *restrict srcptr, size_t size) {
	unsigned char *dst = (unsigned char *)dstptr;
	const unsigned char *src = (const unsigned char *)srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}