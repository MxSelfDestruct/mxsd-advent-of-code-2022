#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BUF_LEN 8192
#define SLICE_LEN 16

void get_substring(char * target, const char * source, unsigned int start, unsigned int end);
bool letters_unique(char * str);

int main(void) {
    FILE * data = fopen("input.txt", "r");

    char buf[BUF_LEN] = {'\0'};
    fgets(buf, BUF_LEN, data);

    char slice[SLICE_LEN] = {'\0'};

    // Get start-of-packet marker
    for (int i = 0; i < strlen(buf) - 3; i++) {
        get_substring(slice, buf, i, i + 3);

        if (letters_unique(slice) == true) {
            printf("Start-of-packet marker: %c", slice[strlen(slice) - 1]);
            printf(", after %u characters.\n", i + 4);
            break;
        }
    }

    // Get start-of-message marker
    for (int i = 0; i < strlen(buf) - 13; i++) {
        get_substring(slice, buf, i, i + 13);

        if (letters_unique(slice) == true) {
            printf("Start-of-message marker: %c", slice[strlen(slice) - 1]);
            printf(", after %u characters.\n", i + 14);
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
