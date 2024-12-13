#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CPUS 128

void cpu_monitoring(char cpus[][256], char *intr) {
  char buffer[256];
  int cpu_count = 0;

  FILE *file = fopen("/proc/stat", "r");
  if (file == NULL) {
    perror("Error: Faild to open /proc/stat!");
  }

  while (fgets(buffer, sizeof(buffer), file)) {
    if (strncmp(buffer, "cpu", 3) == 0) {
      strncpy(cpus[cpu_count], buffer, 256);
      cpu_count++;
    }
    if (strncmp(buffer, "intr ", 5) == 0) {
      strncpy(intr, buffer, 256);
    }
  }

  fclose(file);
}
