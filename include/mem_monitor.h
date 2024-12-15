#include <stdio.h>
#include <string.h>

#define MAX_MEM 128

void mem_monitoring(char mems[][256]) {
  char buffer[256];
  int mem_count = 0;

  FILE *file = fopen("/proc/meminfo", "r");
  if (file == NULL) {
    printf("Error: Faild to open /proc/meminfo!");
  }

  while (fgets(buffer, sizeof(buffer), file)) {
    if (strncmp(buffer, "Mem", 3) == 0) {
      strncpy(mems[mem_count], buffer, 256);
      mem_count++;
    }
  }

  fclose(file);
}
