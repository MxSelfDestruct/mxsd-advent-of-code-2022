#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 32

int main(void) {
    FILE * data = fopen("input.txt", "r");

    char buf[BUF_LEN] = {'\0'};

    while(fgets(buf, BUF_LEN, data) != NULL) {
        buf[strcspn(buf, "\n")] = '\0'; // Send trailing newline to hell

        // Do whatever
    }

    return 0;
}
