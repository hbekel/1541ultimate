#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "miniz.h"
#include "util.h"

int main(int argc, char **argv) {
  argc--; argv++;

  if(argc != 1) {
    fprintf(stderr, "Usage: miniz <infile> > <outfile>\n");
    return EXIT_FAILURE;
  }

  uint64_t size;
  uint8_t* input = (uint8_t*) calloc(1, sizeof(uint8_t));
  
  if(!read_file(argv[0], &input, &size)) goto error;

  uint64_t output_size = mz_compressBound(size);
  uint8_t* output = (uint8_t*) calloc(output_size, sizeof(uint8_t));

  mz_compress2(output, &output_size, input, size, 9);

  fwrite(output, sizeof(uint8_t), output_size, stdout);
  
  free(input);
  free(output);
     
  return EXIT_SUCCESS;

 error:
  fprintf(stderr, "error: %s\n", strerror(errno));
  return EXIT_FAILURE;
}
