#include <stdio.h>
#include <string.h>

#define MAX_MEM 128

void mem_monitoring(char mems[][256], char chached[256], char swap[][256]) {
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

    if (strncmp(buffer, "Cach ", 4) == 0) {
      strncpy(chached, buffer, 256);
    }

    if (strncmp(buffer, "Swap ", 4) == 0) {
      strncpy(swap[mem_count], buffer, 256);
      mem_count++;
    }
  }

  fclose(file);
}

void parse_meme_stats(const char *mems_line, unsigned long long *mems_status) {
  sscanf(mems_line, "%*s %llu", mems_status);
}

void parse_cached_stats(const char *cached_line,
                        unsigned long long *cached_status) {
  sscanf(cached_line, "%*s %llu", cached_status);
}

void parse_swap_stats(const char *swap_line, unsigned long long *swap_status) {
  sscanf(swap_line, "%*s %llu", swap_status);
}

void calculate_cpu_usage(unsigned long long mems_status) {}
