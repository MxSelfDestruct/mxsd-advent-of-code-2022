#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 32
#define DIR_SIZE_CUTOFF 100000

void str_split(char * target1, char * target2, char * source, char * split);
void print_dir_names(char * * data, unsigned int lines);

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
    char * output[lines];
    for (int i = 0; i < lines; i++) output[i] = malloc(length * sizeof(char));

    for (int i = 0; fgets(buf, BUF_LEN, data) != NULL; i++) {
        buf[strcspn(buf, "\n")] = '\0'; // Send trailing newline to hell
        strcpy(output[i], buf);
    }

    fclose(data);

    print_dir_names(output, lines);

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

void print_dir_names(char * * data, unsigned int lines) {
    for (unsigned int i = 0; i < lines; i++) {
        char prefix[BUF_LEN];
        char suffix[BUF_LEN];
        str_split(prefix, suffix, data[i], " ");

        if (strcmp(prefix, "dir") == 0) printf("%s\n", suffix);
    }
}