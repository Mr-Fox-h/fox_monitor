#include <stdio.h>

void print_progress_bar(double percentage) {
  int bar_width = 50;
  int filled_length = (int)(percentage / 100.0 * bar_width);

  printf("");
  for (int i = 0; i < filled_length; i++) {
    printf("󰹞");
  }
  for (int i = filled_length; i < bar_width; i++) {
    printf(" ");
  }
  printf(" %.2f%%\n", percentage);
}
