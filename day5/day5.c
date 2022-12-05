#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 128

void strip_excess_whitespace(char * target, char * source);
void get_crates(char * target, char * source);

int main(void) {
    FILE * data = fopen("input.txt", "r");

    char buf[BUF_LEN] = {'\0'};

    char stacks [9][BUF_LEN];

    while(fgets(buf, BUF_LEN, data) != NULL && buf[0] == ' ' || buf[0] == '[') {
        buf[strcspn(buf, "\n")] = '\0'; // Send trailing newline to hell

        char crates[BUF_LEN] = {'\0'};
        get_crates(crates, buf);

        printf("%s\n", crates);
    }

    return 0;
}

void get_crates(char * target, char * source) {
    unsigned int target_pos = 0;

    for (unsigned int i = 1; i < strlen(source); i += 4) {
        target[target_pos] = source[i];
        target_pos++;
    }
}
