#include <p-clib/stdio.h>
#include <p-clib/stdlib.h>
#include <stdint.h>

/*Portland Shell
  Copyright 2018 Benji Dial
  Under MIT License*/

void main(void) {
  asm volatile (
    "int $0x4c;clear screen"
  );
  uint8_t buffer[1024];
  puts("Welcome to Portland Shell v0.2-dev!");
  while (1) {
    putchar('>');
    putchar(' ');
    if (gets(buffer)[0] == '$' &&
             buffer [1] == 'e' &&
             buffer [2] == 'x' &&
             buffer [3] == 'i' &&
             buffer [4] == 't' &&
             buffer [5] == '$' &&
             buffer [6] == '\0') {
      puts("Goodbye from Portland Shell v0.2-dev!");
      return;
    }
    if (buffer[ 0] == '$' &&
        buffer[ 1] == 's' &&
        buffer[ 2] == 'e' &&
        buffer[ 3] == 't' &&
        buffer[ 4] == ' ' &&
        buffer[ 5] == 'c' &&
        buffer[ 6] == 'o' &&
        buffer[ 7] == 'l' &&
        buffer[ 8] == 'o' &&
        buffer[ 9] == 'r' &&
        buffer[10] == ' ' &&
        buffer[13] == '$' &&
        buffer[14] == '\0') {
      uint8_t color =
        ((buffer[11] >= 'a' ? 10 + buffer[11] - 'a' :
          buffer[11] >= 'A' ? 10 + buffer[11] - 'A' :
          buffer[11]  - '0') << 4) |
         (buffer[12] >= 'a' ? 10 + buffer[12] - 'a' :
          buffer[12] >= 'A' ? 10 + buffer[12] - 'A' :
          buffer[12]  - '0');
      asm volatile (
        "int $0x4d;set color\n"
        : : "al" (color)
      );
    } else
      system(buffer);
  }
}
