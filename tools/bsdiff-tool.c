#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "bsdiff.h"
#include "util.h"

int main(int argc, char** argv) {
  argc--; argv++;

  if(argc != 2) {
    fprintf(stderr, "Usage: bsdiff <original> <patched>\n");
    return EXIT_FAILURE;
  }

  uint64_t original_size;
  uint8_t* original_data = (uint8_t*) calloc(1, sizeof(uint8_t));
  if(!read_file(argv[0], &original_data, &original_size)) goto error;

  uint64_t patched_size;
  uint8_t* patched_data = (uint8_t*) calloc(1, sizeof(uint8_t));
  if(!read_file(argv[1], &patched_data, &patched_size)) goto error;

  uint64_t max_patch_size = bsdiff_patchsize_max(original_size, patched_size);

  void* patch = calloc(max_patch_size, sizeof(uint8_t));

  uint64_t patch_size = bsdiff(original_data, original_size,
			       patched_data, patched_size,
			       patch, max_patch_size);

  fwrite(patch, sizeof(uint8_t), patch_size, stdout);

  free(original_data);
  free(patched_data);
  free(patch);

  return EXIT_SUCCESS;

  error:
    fprintf(stderr, "error: %s\n", strerror(errno));
    return EXIT_FAILURE;
}
