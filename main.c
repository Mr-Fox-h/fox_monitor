#include "include/cpu_monitor.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // CPU Monitoring
  char cpus[MAX_CPUS][256];
  char intr[256];

  while (true) {
    cpu_monitoring(cpus, intr);
    for (int i = 0; i < MAX_CPUS && cpus[i][0] != '\0'; i++) {
      printf("%s", cpus[i]);
    }
    printf("Intr: %s\n", intr);
    usleep(100000);
    system("clear");
  }
  return EXIT_SUCCESS;
}
