#include "include/cpu_monitor.h"
#include "include/cpu_progress_bar.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // CPU Monitoring
  char cpus[MAX_CPUS][256] = {{0}};
  unsigned long long user1[MAX_CPUS], nice1[MAX_CPUS], system1[MAX_CPUS],
      idle1[MAX_CPUS], iowait1[MAX_CPUS], irq1[MAX_CPUS], softirq1[MAX_CPUS],
      steal1[MAX_CPUS], guest1[MAX_CPUS], guest_nice1[MAX_CPUS];
  unsigned long long user2[MAX_CPUS], nice2[MAX_CPUS], system2[MAX_CPUS],
      idle2[MAX_CPUS], iowait2[MAX_CPUS], irq2[MAX_CPUS], softirq2[MAX_CPUS],
      steal2[MAX_CPUS], guest2[MAX_CPUS], guest_nice2[MAX_CPUS];

  while (true) {
    cpu_monitoring(cpus);
    for (int i = 0; i < MAX_CPUS && cpus[i][0] != '\0'; i++) {
      parse_cpu_stats(cpus[i], &user1[i], &nice1[i], &system1[i], &idle1[i],
                      &iowait1[i], &irq1[i], &softirq1[i], &steal1[i],
                      &guest1[i], &guest_nice1[i]);
    }

    sleep(1);
    cpu_monitoring(cpus);
    for (int i = 0; i < MAX_CPUS && cpus[i][0] != '\0'; i++) {
      parse_cpu_stats(cpus[i], &user2[i], &nice2[i], &system2[i], &idle2[i],
                      &iowait2[i], &irq2[i], &softirq2[i], &steal2[i],
                      &guest2[i], &guest_nice2[i]);
    }

    system("clear");
    for (int i = 0; i < MAX_CPUS && cpus[i][0] != '\0'; i++) {
      double usage = calculate_cpu_usage(
          user1[i], nice1[i], system1[i], idle1[i], iowait1[i], irq1[i],
          softirq1[i], steal1[i], guest1[i], guest_nice1[i], user2[i], nice2[i],
          system2[i], idle2[i], iowait2[i], irq2[i], softirq2[i], steal2[i],
          guest2[i], guest_nice2[i]);
      printf("CPU%d:\t", i);
      print_progress_bar(usage);
    }
  }
  return EXIT_SUCCESS;
}
