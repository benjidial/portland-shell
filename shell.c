#include <stdint.h>
#include <p-clib.h>

/*Portland Shell
  Copyright 2018 Benji Dial
  Under MIT License*/

uint32_t main(void) {
  clear();
  uint8_t buffer[1024];
  print_bytes("Welcome to Portland Shell v0.2.0-pre!\n");
  while (1) {
    print_byte('>');
    print_byte(' ');
    kbd_line(KBD_BLOCK, buffer, 1023);
    if (buffer[0] == '$' &&
        buffer[1] == 'e' &&
        buffer[2] == 'x' &&
        buffer[3] == 'i' &&
        buffer[4] == 't' &&
        buffer[5] == '$' &&
        buffer[6] == '\0') {
      print_bytes("Goodbye from Portland Shell v0.2.0-pre!\n");
      return 0;
    } if (buffer[ 0] == '$' &&
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
      set_color(color);
    } else {
      uint32_t ret;
      switch (file_exec(buffer, &ret)) {
      case 0x00:
        if (ret) {
          print_bytes("Warning: ");
          print_bytes(buffer);
          print_bytes(" returned with exit code 0x");
          for (uint32_t mask = 0xf0000000; mask; mask >>= 4) {
            uint8_t nibble = (ret & mask) / mask;
            print_byte(nibble + (nibble < 10 ? '0' : 'a' - 10));
          }
          print_bytes(", not 0.\n");
        }
        continue;
      case 0x02:
        print_bytes("Error: not enough memory to run file\n");
        continue;
      case 0x03:
        print_bytes("Error: file does not exist\n");
        continue;
      }
      print_bytes("An unknown error occurred trying to run that file\n");
    }
  }
}
