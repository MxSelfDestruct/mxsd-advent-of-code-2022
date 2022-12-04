#include <stdio.h>
#include <string.h>

#define BUF_LEN 64

unsigned int get_priority(char item);
void copy_str_span(char * target, char * source, unsigned int start, unsigned int end);
void get_common_chars(char * target, char * source1, char * source2);

int main(void) {
    FILE * data = fopen("day3.txt", "r");

    char buf[BUF_LEN] = {'\0'};
    unsigned int priority_sum = 0;

    while(fgets(buf, BUF_LEN, data) != NULL) {
        buf[strcspn(buf, "\n")] = '\0'; // Send trailing newline to hell
        unsigned int len = strlen(buf);

        // Split string into halves and find the letters they have in common
        char bag1[BUF_LEN] = {'\0'};
        char bag2[BUF_LEN] = {'\0'};
        char common[BUF_LEN] = {'\0'};

        copy_str_span(bag1, buf, 0, len / 2 - 1);
        copy_str_span(bag2, buf, len / 2, len);
        get_common_chars(common, bag1, bag2);

        for (int i = 0; i < strlen(common); i++) priority_sum += get_priority(common[i]);
    }

    printf("%u\n", priority_sum);

    fclose(data);

    return 0;
}

unsigned int get_priority(char item) {
    if (item >= 'a' && item <= 'z') return item - 'a' + 1;
    if (item >= 'A' && item <= 'Z') return item - 'A' + 27;

    return 0;
}

void copy_str_span(char * target, char * source, unsigned int start, unsigned int end) {
    for (int i = 0; i <= end; i++) {
        target[i] = source[i + start];

        if (i == end) {
            if (target[i] != '\0') target[i + 1] = '\0';
        }
    }
}

void get_common_chars(char * target, char * source1, char * source2) {
    unsigned int freq1[128] = {0};
    unsigned int freq2[128] = {0};

    for (int i = 0; i < strlen(source1); i++) freq1[(unsigned int)source1[i]]++;
    for (int i = 0; i < strlen(source2); i++) freq2[(unsigned int)source2[i]]++;

    unsigned int target_index = 0;

    for (int i = 0; i < 128; i++) {
        if (freq1[i] > 0 && freq2[i] > 0) {
            target[target_index] = i;
            target_index++;
        }
    }

    for (int i = target_index; i < strlen(target); i++) target[i] = '\0';
}
