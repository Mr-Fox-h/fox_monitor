#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INTERFACES 128

void net_monitoring(char interfaces[][256]) {
  char buffer[256];
  int interface_count = 0;

  FILE *file = fopen("/proc/net/dev", "r");
  if (file == NULL) {
    perror("Error: Failed to open /proc/net/dev!");
    return;
  }

  // Skip the first two lines (header)
  fgets(buffer, sizeof(buffer), file);
  fgets(buffer, sizeof(buffer), file);

  while (fgets(buffer, sizeof(buffer), file)) {
    strncpy(interfaces[interface_count], buffer, 256);
    interface_count++;
  }

  fclose(file);
}

void parse_net_stats(const char *interface_line, char *interface_name,
                     unsigned long long *rx_bytes,
                     unsigned long long *tx_bytes) {
  sscanf(interface_line,
         "%s %*d %*d %*d %*d %*d %*d %*d %llu %*d %*d %*d %*d %*d %*d %llu",
         interface_name, rx_bytes, tx_bytes);
}

double calculate_net_usage(unsigned long long rx_bytes1,
                           unsigned long long tx_bytes1,
                           unsigned long long rx_bytes2,
                           unsigned long long tx_bytes2, double interval) {
  unsigned long long rx_diff = rx_bytes2 - rx_bytes1;
  unsigned long long tx_diff = tx_bytes2 - tx_bytes1;
  unsigned long long total_diff = rx_diff + tx_diff;

  return (total_diff * 8.0) / (interval * 1024 * 1024); // Convert to Mbps
}
