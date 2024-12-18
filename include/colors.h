#include <stdio.h>

void red() { printf("\033[1;31m"); }
void green() { printf("\033[0;32m"); }
void yellow() { printf("\033[1;33m"); }
void reset_color() { printf("\033[0m"); }
