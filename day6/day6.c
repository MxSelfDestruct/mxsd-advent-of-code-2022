#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BUF_LEN 8192
#define SLICE_LEN 16
#define PACKET_MARKER_LEN 4
#define MESSAGE_MARKER_LEN 14

void get_substring(char * target, const char * source, unsigned int start, unsigned int end);
bool letters_unique(char * str);

int main(void) {
    FILE * data = fopen("input.txt", "r");

    char buf[BUF_LEN] = {'\0'};
    fgets(buf, BUF_LEN, data);

    char slice[SLICE_LEN] = {'\0'};

    // Get start-of-packet marker
    for (int i = 0; i < strlen(buf) - PACKET_MARKER_LEN; i++) {
        get_substring(slice, buf, i, i + PACKET_MARKER_LEN - 1);

        if (letters_unique(slice) == true) {
            printf("Start-of-packet marker: %c", slice[strlen(slice) - 1]);
            printf(", after %u characters.\n", i + PACKET_MARKER_LEN);
            break;
        }
    }

    // Get start-of-message marker
    for (int i = 0; i < strlen(buf) - MESSAGE_MARKER_LEN; i++) {
        get_substring(slice, buf, i, i + MESSAGE_MARKER_LEN - 1);

        if (letters_unique(slice) == true) {
            printf("Start-of-message marker: %c", slice[strlen(slice) - 1]);
            printf(", after %u characters.\n", i + MESSAGE_MARKER_LEN);
            break;
        }
    }

    return 0;
}

void get_substring(char * target, const char * source, unsigned int start, unsigned int end) {
    for (unsigned int i = start; i <= end; i++) target[i - start] = source[i];
}

bool letters_unique(char * str) {
    unsigned int freq[128] = {0};
    for (unsigned int i = 0; i < strlen(str); i++) freq[str[i]]++;
    for (unsigned int i = 0; i < 128; i++) if (freq[i] > 1) return false;

    return true;
}
