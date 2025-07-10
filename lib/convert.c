#include <stdint.h>

void u8_to_str(uint8_t num, char* buffer) {
    char temp[4];
    int i = 0;

    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (num > 0) {
        temp[i++] = '0' + (num % 10);
        num /= 10;
    }

    for (int j = 0; j < i; j++) {
        buffer[j] = temp[i - j - 1];
    }

    buffer[i] = '\0';
}
