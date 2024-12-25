#include "colors.h"
#include <stdbool.h>
#include <stdio.h>

void status_progress_bar(double percentage, bool per) {
  int bar_width = 50;
  int filled_length = (int)(percentage / 100.0 * bar_width);

  printf("");
  for (int i = 0; i < filled_length; i++) {
    if (i <= 15) {
      green();
    } else if (i >= 15 && i <= 30) {
      yellow();
    } else {
      red();
    }
    printf("󰹞");
  }
  for (int i = filled_length; i < bar_width; i++) {
    printf(" ");
  }
  reset_color();
  printf(" ");
  if (percentage <= 40.00)
    green();
  else if (percentage <= 60.00 && percentage >= 40.00)
    yellow();
  else
    red();

  if (per)
    printf("%.2f%%\n", percentage);
  else
    printf("%.2f GB\n", percentage);
  reset_color();
}
