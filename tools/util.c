#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>

#include "util.h"

bool read_file(const char* filename, uint8_t **data, uint64_t* size) {
  FILE* file;

  struct stat st;
  stat(filename, &st);
  (*size) = st.st_size;
  
  if((file = fopen(filename, "rb")) == NULL) return false;
  (*data) = (uint8_t*) realloc((*data), (*size));
  fread((*data), sizeof(uint8_t), (*size), file);
  fclose(file);

  return true;
}

bool write_file(const char* filename, uint8_t *data, uint64_t size) {
  FILE* file;

  if((file = fopen(filename, "wb")) == NULL) return false;
  fwrite(data, sizeof(uint8_t), size, file);
  fclose(file);
  return true;
}
  
