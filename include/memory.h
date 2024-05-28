#ifndef MEMORY_H_
#define MEMORY_H_

#include <stddef.h>

void *memset(void *, int, size_t);
void *memcpy(void *__restrict, const void *__restrict, size_t);

#endif // MEMORY_H_