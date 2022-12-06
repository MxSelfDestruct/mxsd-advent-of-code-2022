#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void strslice(char * target, const char * source, unsigned int start, unsigned int end);
bool letters_unique(const char * str);
unsigned int get_start_marker(const char * str, unsigned int unique_chars_needed);

int main(void) {
    FILE * data = fopen("input.txt", "r");

    char buf[8192] = {'\0'};
    fgets(buf, 8192, data);

    printf("Start-of-packet marker detected after %u characters.\n", get_start_marker(buf, 4));
    printf("Start-of-message marker detected after %u characters.\n", get_start_marker(buf, 14));

    return 0;
}

void strslice(char * target, const char * source, unsigned int start, unsigned int end) {
    for (unsigned int i = start; i <= end + 1; i++) {
        if (i <= end) target[i - start] = source[i];
        else target[i - start] = '\0';
    }
}

bool letters_unique(const char * str) {
    unsigned int freq[128] = {0};
    for (unsigned int i = 0; i < strlen(str); i++) {
        freq[str[i]]++;
        if (freq[str[i]] > 1) return false;
    }

    return true;
}

unsigned int get_start_marker(const char * str, unsigned int unique_chars_needed) {
    char slice[unique_chars_needed + 1];

    for (int i = 0; i < strlen(str) - unique_chars_needed; i++) {
        strslice(slice, str, i, i + unique_chars_needed - 1);
        if (letters_unique(slice) == true) return i + unique_chars_needed;
    }
}
