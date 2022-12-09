#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 32

int main(void) {
    FILE * data = fopen("input.txt", "r");
    char buf[BUF_LEN] = {'\0'};

    // Get number of lines in file and max line length
    int lines = 1;
    int length = 1;

    for (int i = 0; fgets(buf, BUF_LEN, data) != NULL; i++) {
        buf[strcspn(buf, "\n")] = '\0'; // Send trailing newline to hell
        int l = strlen(buf) + 1;
        if (l > length) length = l;
        lines++;
    }

    rewind(data);

    // Allocate a 2D array to store the file in
    char * instructions[lines];
    for (int i = 0; i < lines; i++) instructions[i] = malloc(length * sizeof(char));

    for (int i = 0; fgets(buf, BUF_LEN, data) != NULL; i++) {
        buf[strcspn(buf, "\n")] = '\0'; // Send trailing newline to hell
        strcpy(instructions[i], buf);
    }

    fclose(data);

    return 0;
}
