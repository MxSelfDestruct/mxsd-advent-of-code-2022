#include <stdio.h>
#include <string.h>

#define BUF_LEN 64

unsigned int get_priority(char item);
void get_common_chars(char * target, char * source1, char * source2, char * source3);

int main(void) {
    FILE * data = fopen("day3.txt", "r");

    char buf1[BUF_LEN] = {'\0'};
    char buf2[BUF_LEN] = {'\0'};
    char buf3[BUF_LEN] = {'\0'};
    unsigned int priority_sum = 0;

    while(fgets(buf1, BUF_LEN, data) != NULL &&
          fgets(buf2, BUF_LEN, data) != NULL &&
          fgets(buf3, BUF_LEN, data) != NULL) {
        buf1[strcspn(buf1, "\n")] = '\0';
        buf2[strcspn(buf2, "\n")] = '\0';
        buf3[strcspn(buf3, "\n")] = '\0';

        char common[BUF_LEN] = {'\0'};
        get_common_chars(common, buf1, buf2, buf3);

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

void get_common_chars(char * target, char * source1, char * source2, char * source3) {
    unsigned int freq1[128] = {0};
    unsigned int freq2[128] = {0};
    unsigned int freq3[128] = {0};

    for (int i = 0; i < strlen(source1); i++) freq1[(unsigned int)source1[i]]++;
    for (int i = 0; i < strlen(source2); i++) freq2[(unsigned int)source2[i]]++;
    for (int i = 0; i < strlen(source3); i++) freq3[(unsigned int)source3[i]]++;

    unsigned int target_index = 0;

    for (int i = 0; i < 128; i++) {
        if (freq1[i] > 0 && freq2[i] > 0 && freq3[i] > 0) {
            target[target_index] = i;
            target_index++;
        }
    }

    for (int i = target_index; i < strlen(target); i++) target[i] = '\0';
}
