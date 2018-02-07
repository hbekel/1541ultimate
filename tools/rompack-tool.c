#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <getopt.h>

#include "miniz.h"
#include "util.h"

bool ends(const char* str, const char* end) {
  if(!str || !end) return false;
  return (strlen(str) >= strlen(end) &&
          !strcmp(str + strlen(str) - strlen(end), end));
}

void upcase(char* str) {
  if(!str) return;
  
  for(; str[0]; str++) {
    str[0] = toupper(str[0]);
  }
}

uint32_t get_uncompressed_size(char *name) {
  uint64_t compressed_size;
  uint64_t uncompressed_size = 0x100000;
  uint8_t *compressed = (uint8_t*) calloc(1, sizeof(uint8_t));

  if(!read_file(name, &compressed, &compressed_size)) return 0;

  uint8_t *uncompressed = (uint8_t*) calloc(uncompressed_size, sizeof(uint8_t));  
  mz_uncompress(uncompressed, &uncompressed_size, compressed, compressed_size);
  
  free(uncompressed);
  free(compressed);
  return uncompressed_size;
}

int main(int argc, char** argv) {
  DIR* dir;
  struct dirent* entry;
  struct stat st;
  
  uint32_t base;
  uint32_t address;
  uint32_t compressed_size;
  uint32_t uncompressed_size;

  bool make_includes = false;
  bool make_addresses = false;
  char* filename;
  char* basename;
  char* name;
  
  struct option options[] = {
    { "help",         no_argument,       0, 'h' },
    { "addresses",    required_argument, 0, 'a' },
    { "includes",     no_argument,       0, 'i' },
    { "outfile",      required_argument, 0, 'o' },    
    { 0, 0, 0, 0 },
  };
  int option, option_index;
  
  while(1) {
    option = getopt_long(argc, argv, "ha:io:", options, &option_index);

    if(option == -1)
      break;
    
    switch (option) {
      
    case 'h':
      puts("help!");
      goto done;
      break;      

    case 'a':
      base = strtol(optarg, NULL, 0);
      address = base;
      make_addresses = true;
      break;      

    case 'i':
      make_includes = true;
      break;            

    case 'o':
      filename = strdup(optarg);
      break;            
      
    case '?':
    case ':':
    default:
      goto error;
    }
  }
  
  argc -= optind;
  argv += optind;

  dir = opendir (".");
  if(dir) {

    FILE* out = fopen(filename, "w+");
    if(out == NULL) {
      perror("Couldn't open output file");
      goto error;
    }
    
    while((entry = readdir(dir))) {
      name = strdup(entry->d_name);

      stat(name, &st);
      compressed_size = st.st_size;
      
      if(ends(name, ".mz")) {

        if(make_addresses) {
        
          uncompressed_size = get_uncompressed_size(name);

          strstr(name, ".mz")[0] = 0;
        
          basename = strstr(name, "§");
          if(basename) {
            basename[0] = 0;
            basename+=2;          
          }
          if(ends(name, ".bin")) strstr(name, ".bin")[0] = 0;
          if(ends(basename, ".bin")) strstr(basename, ".bin")[0] = 0;
          
          upcase(name);
          upcase(basename);
          
          if(basename) {
            fprintf(out, "{ FLASH_ID_%s, \t0x00, 0x%06X, 0x%06X, 0x%06X, 0x%06X, FLASH_ID_%s },\n",
                   name, address, address, compressed_size, uncompressed_size, basename);
          }
          else {
            fprintf(out, "{ FLASH_ID_%s, \t0x00, 0x%06X, 0x%06X, 0x%06X, 0x%06X, 0 },\n",
                   name, address, address, compressed_size, uncompressed_size);
          }
          address += compressed_size;
        }
        else if(make_includes) {
          fprintf(out, ".incbin \"%s\"\n", name);
        }
      }
    }
    fclose(out);
    closedir(dir);
  }
  else {
    perror("Couldn't open the directory");
    goto error;
  }

 done:
  return EXIT_SUCCESS;
  
 error:
  return EXIT_FAILURE;
}
