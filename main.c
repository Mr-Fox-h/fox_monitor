#include "include/cpu_monitor.h"
#include "include/mem_monitor.h"
#include "include/net_monitor.h"
#include "include/progress_bar.h"
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

  // Memory Monitoring Data
  char mems[MAX_MEM][256];
  char cached[256];
  char swap[MAX_MEM][256];
  unsigned long long mems_status[MAX_MEM], cached_status[MAX_MEM],
      swap_status[MAX_MEM];
  unsigned long long mem_total = 0;
  unsigned long long mem_free = 0;
  unsigned long long mem_available = 0;
  float cached_value = 0;
  unsigned long long swap_total = 0;
  unsigned long long swap_free = 0;
  unsigned long long swap_cached = 0;

  // Network Monitoring
  char interfaces[MAX_INTERFACES][256];
  char interface_name1[MAX_INTERFACES][256];
  char interface_name2[MAX_INTERFACES][256];
  unsigned long long rx_bytes1[MAX_INTERFACES], tx_bytes1[MAX_INTERFACES];
  unsigned long long rx_bytes2[MAX_INTERFACES], tx_bytes2[MAX_INTERFACES];
  double interval = 1.0; // Interval in seconds

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

    // Calculate CPU Usage Percentages
    system("clear");
    for (int i = 0; i < MAX_CPUS && cpus[i][0] != '\0'; i++) {
      double usage = calculate_cpu_usage(
          user1[i], nice1[i], system1[i], idle1[i], iowait1[i], irq1[i],
          softirq1[i], steal1[i], guest1[i], guest_nice1[i], user2[i], nice2[i],
          system2[i], idle2[i], iowait2[i], irq2[i], softirq2[i], steal2[i],
          guest2[i], guest_nice2[i]);
      if (i != 0) {
        printf("CPU%d:\t", i - 1);
        status_progress_bar(usage, true);
      } else {
        printf("CPUs:\t");
        status_progress_bar(usage, true);
      }
    }

    // Mem Monitoring Loop
    mem_monitoring(mems, cached, swap);
    for (int i = 0; i < MAX_MEM && mems[i][0] != '\0'; i++) {
      parse_meme_stats(mems[i], &mems_status[i]);
      mem_total = mems_status[0];
      mem_free = mems_status[1];
      mem_available = mems_status[2];
    }

    for (int i = 0; i < MAX_MEM && swap[i][0] != '\0'; i++) {
      parse_swap_stats(swap[i], &swap_status[i]);
      swap_cached = swap_status[0];
      swap_total = swap_status[1];
      swap_free = swap_status[2];
    }

    parse_cached_stats(cached, cached_status);
    cached_value = (double)(*cached_status / 1024.0) / 1024.0;

    // Calculate memory usage percentages
    double mem_usage = calculate_mem_usage(mem_total, mem_free, mem_available);
    double mem_available_usage =
        calculate_mem_available_usage(mem_total, mem_available);
    double swap_usage = 100.0 * (double)(swap_total - swap_free) / swap_total;
    printf(
        ""
        ""
        ""
        ""
        "\n");
    printf("Memory: %lld KB\n", mem_total);
    printf("Used:\t");
    status_progress_bar(mem_usage, true);
    printf("Avai:\t");
    status_progress_bar(mem_available_usage, true);
    printf("Cached:\t");
    status_progress_bar(cached_value, false);
    printf(
        ""
        ""
        ""
        ""
        "\n");
    printf("Swap: %lld KB\n", swap_total);
    printf("Used:\t");
    status_progress_bar(swap_usage, true);

    // Mem Monitoring Loop
    net_monitoring(interfaces);
    for (int i = 0; i < MAX_INTERFACES && interfaces[i][0] != '\0'; i++) {
      parse_net_stats(interfaces[i], interface_name1[i], &rx_bytes1[i],
                      &tx_bytes1[i]);
    }

    net_monitoring(interfaces);
    for (int i = 0; i < MAX_INTERFACES && interfaces[i][0] != '\0'; i++) {
      parse_net_stats(interfaces[i], interface_name2[i], &rx_bytes2[i],
                      &tx_bytes2[i]);
    }
    // Calculate Network Usage Percentages
    for (int i = 0; i < MAX_INTERFACES && interfaces[i][0] != '\0'; i++) {
      double usage = calculate_net_usage(rx_bytes1[i], tx_bytes1[i],
                                         rx_bytes2[i], tx_bytes2[i], interval);
      printf("Interface: %s\n", interface_name2[i]);
      printf("Network Usage: %.2f Mbps\n", usage);
    }
  }
  return EXIT_SUCCESS;
}
