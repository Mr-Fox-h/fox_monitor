#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CPUS 128

void cpu_monitoring(char cpus[][256]) {
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
  }

  fclose(file);
}

void parse_cpu_stats(const char *cpu_line, unsigned long long *user,
                     unsigned long long *nice, unsigned long long *system,
                     unsigned long long *idle, unsigned long long *iowait,
                     unsigned long long *irq, unsigned long long *softirq,
                     unsigned long long *steal, unsigned long long *guest,
                     unsigned long long *guest_nice) {
  sscanf(cpu_line, "%*s %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
         user, nice, system, idle, iowait, irq, softirq, steal, guest,
         guest_nice);
}

double calculate_cpu_usage(unsigned long long user1, unsigned long long nice1,
                           unsigned long long system1, unsigned long long idle1,
                           unsigned long long iowait1, unsigned long long irq1,
                           unsigned long long softirq1,
                           unsigned long long steal1, unsigned long long guest1,
                           unsigned long long guest_nice1,
                           unsigned long long user2, unsigned long long nice2,
                           unsigned long long system2, unsigned long long idle2,
                           unsigned long long iowait2, unsigned long long irq2,
                           unsigned long long softirq2,
                           unsigned long long steal2, unsigned long long guest2,
                           unsigned long long guest_nice2) {
  unsigned long long total1 = user1 + nice1 + system1 + idle1 + iowait1 + irq1 +
                              softirq1 + steal1 + guest1 + guest_nice1;
  unsigned long long total2 = user2 + nice2 + system2 + idle2 + iowait2 + irq2 +
                              softirq2 + steal2 + guest2 + guest_nice2;
  unsigned long long idle_diff = idle2 - idle1;
  unsigned long long total_diff = total2 - total1;

  if (total_diff == 0)
    return 0.0;

  return 100.0 * (1.0 - (double)idle_diff / total_diff);
}
