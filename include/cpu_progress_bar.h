#include <stdio.h>

void red() { printf("\033[1;31m"); }

void green() { printf("\033[0;32m"); }

void yellow() { printf("\033[1;33m"); }

void reset_color() { printf("\033[0m"); }

void print_progress_bar(double percentage) {
  int bar_width = 50;
  int filled_length = (int)(percentage / 100.0 * bar_width);

  printf("");
  for (int i = 0; i < filled_length; i++) {
    if (i <= 15) {
      green();
      printf("󰹞");
    } else if (i >= 15 && i <= 30) {
      yellow();
      printf("󰹞");
    } else {
      red();
      printf("󰹞");
    }
  }
  for (int i = filled_length; i < bar_width; i++) {
    printf(" ");
  }
  reset_color();
  printf(" %.2f%%\n", percentage);
}
