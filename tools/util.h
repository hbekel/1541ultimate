#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

bool read_file(const char* filename, uint8_t **data, uint64_t* size);
bool write_file(const char* filename, uint8_t *data, uint64_t size);

#endif // UTIL_H
