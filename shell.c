#include <p-clib/stdio.h>
#include <p-clib/stdlib.h>
#include <stdint.h>

/*Copyright 2018 Benji Dial
  Portland shell*/

void main(uint8_t *arg) {
  uint8_t buffer[1024];
  puts("Welcome to Portland Shell v0.2.0!");
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
      puts("Goodbye from Portland Shell v0.2.0!");
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
      uint16_t mask =
        ((buffer[11] >= 'a' ? 10 + buffer[11] - 'a' :
          buffer[11] >= 'A' ? 10 + buffer[11] - 'A' :
          buffer[11]  - '0') << 12) |
        ((buffer[12] >= 'a' ? 10 + buffer[12] - 'a' :
          buffer[12] >= 'A' ? 10 + buffer[12] - 'A' :
          buffer[12]  - '0') <<  8);
      asm volatile (
        "pushw %mask\n"
        "int $0x8a\n"
        "add $2, %sp"
      );
    } else
      system(buffer);
  }
}
