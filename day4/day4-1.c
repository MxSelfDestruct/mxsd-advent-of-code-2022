#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 32

void str_split(char * target1, char * target2, char * source, char * split);
bool is_range_subset(int a_low, int a_high, int b_low, int b_high);

int main(void) {
    FILE * data = fopen("input.txt", "r");

    char buf[BUF_LEN] = {'\0'};
    unsigned int overlapping_ranges = 0;

    while(fgets(buf, BUF_LEN, data) != NULL) {
        buf[strcspn(buf, "\n")] = '\0'; // Send trailing newline to hell

        // Split at comma
        char s1[BUF_LEN / 2] = {'\0'};
        char s2[BUF_LEN / 2] = {'\0'};

        str_split(s1, s2, buf, ",");

        char s1_low[BUF_LEN / 4] = {'\0'};
        char s1_high[BUF_LEN / 4] = {'\0'};
        char s2_low[BUF_LEN / 4] = {'\0'};
        char s2_high[BUF_LEN / 4] = {'\0'};

        str_split(s1_low, s1_high, s1, "-");
        str_split(s2_low, s2_high, s2, "-");

        if (is_range_subset(atoi(s1_low), atoi(s1_high), atoi(s2_low), atoi(s2_high)) == true ||
            is_range_subset(atoi(s2_low), atoi(s2_high), atoi(s1_low), atoi(s1_high)) == true) {
                overlapping_ranges++;
            }
    }

    printf("Overlapping ranges: %u\n", overlapping_ranges);

    return 0;
}

void str_split(char * target1, char * target2, char * source, char * split) {
    unsigned int sourcelen = strlen(source);
    unsigned int split_index = strcspn(source, split);
    unsigned int after_split = split_index + strlen(split);

    for (int i = 0; i <= split_index; i++) {
        if (i < split_index) target1[i] = source[i];
        else target1[i] = '\0';
    }

    for (int i = after_split; i <= sourcelen; i++) {
        if (i < sourcelen) target2[i - after_split] = source[i];
        else target2[i - after_split] = '\0';
    }
}

bool is_range_subset(int a_low, int a_high, int b_low, int b_high) {
    return (b_low <= a_low && b_high >= a_high);
}
