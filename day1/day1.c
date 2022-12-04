#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 16
#define MAX_TOTALS 512

unsigned int popHighestInt(unsigned int arr[], unsigned int len);

int main(void) {
    FILE * data = fopen("day1.txt", "r");

    char buf[BUF_LEN];
    unsigned int total = 0;
    unsigned int totals[MAX_TOTALS];
    unsigned int totals_arr_index = 0;

    // Initialise totals[]
    for (unsigned int i = 0; i < MAX_TOTALS; i++) { totals[i] = 0; }

    while (fgets(buf, BUF_LEN, data) != NULL) {
        if (strcmp("\n", buf) == 0) {
            totals[totals_arr_index] = total;
            totals_arr_index++;
            total = 0;
        }

        else { total += atoi(buf); }
    }

    unsigned int high1 = popHighestInt(totals, MAX_TOTALS);
    unsigned int high2 = popHighestInt(totals, MAX_TOTALS);
    unsigned int high3 = popHighestInt(totals, MAX_TOTALS);

    printf("Highest calorie totals:\n");

    printf("1:\t%8u\n", high1);
    printf("2:\t%8u\n", high2);
    printf("3:\t%8u\n", high3);

    printf("Total:\t%8u\n", high1 + high2 + high3);

    fclose(data);

    return 0;
}

unsigned int popHighestInt(unsigned int arr[], unsigned int len) {
    unsigned int highest = 0;
    unsigned int highestIndex = 0;
    
    for (unsigned int i = 0; i < len; i++) {
        if (arr[i] > highest) {
            highest = arr[i];
            highestIndex = i;
        }
    }

    arr[highestIndex] = 0;
    return highest;
}
