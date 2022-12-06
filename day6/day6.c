#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void get_substring(char * target, const char * source, unsigned int start, unsigned int end);
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

void get_substring(char * target, const char * source, unsigned int start, unsigned int end) {
    for (unsigned int i = start; i <= end; i++) target[i - start] = source[i];
}

bool letters_unique(const char * str) {
    unsigned int freq[128] = {0};
    for (unsigned int i = 0; i < strlen(str); i++) freq[str[i]]++;
    for (unsigned int i = 0; i < 128; i++) if (freq[i] > 1) return false;

    return true;
}

unsigned int get_start_marker(const char * str, unsigned int unique_chars_needed) {
    char slice[unique_chars_needed + 1];
    for (unsigned int i = 0; i <= unique_chars_needed; i++) slice[i] = '\0';

    for (int i = 0; i < strlen(str) - unique_chars_needed; i++) {
        get_substring(slice, str, i, i + unique_chars_needed - 1);
        
        if (letters_unique(slice) == true) return i + unique_chars_needed;
    }
}
