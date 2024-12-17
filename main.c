#include "include/cpu_monitor.h"
#include "include/cpu_progress_bar.h"
#include "include/mem_monitor.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // CPU Monitoring Data
  char cpus[MAX_CPUS][256] = {{0}};
  unsigned long long user1[MAX_CPUS], nice1[MAX_CPUS], system1[MAX_CPUS],
      idle1[MAX_CPUS], iowait1[MAX_CPUS], irq1[MAX_CPUS], softirq1[MAX_CPUS],
      steal1[MAX_CPUS], guest1[MAX_CPUS], guest_nice1[MAX_CPUS];
  unsigned long long user2[MAX_CPUS], nice2[MAX_CPUS], system2[MAX_CPUS],
      idle2[MAX_CPUS], iowait2[MAX_CPUS], irq2[MAX_CPUS], softirq2[MAX_CPUS],
      steal2[MAX_CPUS], guest2[MAX_CPUS], guest_nice2[MAX_CPUS];

  // Mem Monitoring Data
  char mems[MAX_MEM][256];
  char cached[256];
  char swap_cached[256];
  unsigned long long mems_status[MAX_MEM], cached_status[MAX_MEM];

  while (true) {
    // CPU Monitoring Loop
    cpu_monitoring(cpus);
    for (int i = 0; i < MAX_CPUS && cpus[i][0] != '\0'; i++) {
      parse_cpu_stats(cpus[i], &user1[i], &nice1[i], &system1[i], &idle1[i],
                      &iowait1[i], &irq1[i], &softirq1[i], &steal1[i],
                      &guest1[i], &guest_nice1[i]);
    }

    usleep(500000);
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
      if (i != 0) {
        printf("CPU%d:\t", i - 1);
        print_progress_bar(usage);
      } else {
        printf("CPUs:\t");
        print_progress_bar(usage);
      }

      // Mem Monitoring Loop
      mem_monitoring(mems, cached, swap_cached);
      for (int i = 0; i < MAX_MEM && mems[i][0] != '\0'; i++) {
        parse_meme_stats(mems[i], &mems_status[i]);
      }

      parse_cached_stats(cached, cached_status);
    }
  }
  return EXIT_SUCCESS;
}
