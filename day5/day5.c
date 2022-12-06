#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 128
#define NUM_STACKS 9

void swap_char(char &a, char &b);
void reverse_str(char * target);
void get_crates(char crates[NUM_STACKS][BUF_LEN], FILE * source);
void execute_instructions(char stacks[][BUF_LEN], char * instructions, bool mode);

int main(void) {
    FILE * data = fopen("input.txt", "r");
    
    // Stacks of crates are stored as nine rows
    char crates[NUM_STACKS][BUF_LEN] = {{'\0'}};
    get_crates(crates, data);
    
    // Advance buffer until we hit the movement instructions
    char buf[BUF_LEN] = {'\0'};
    while (buf[0] != 'm') fgets(buf, BUF_LEN, data);

    // Move the crates
    do { execute_instructions(crates, buf, 0); } while (fgets(buf, BUF_LEN, data) != NULL);

    printf("Top crates (Using Cratemover 9000): ");
    for (int i = 0; i < NUM_STACKS; i++) printf("%c", crates[i][strcspn(crates[i], " ") - 1]);
    printf("\n");

    // Reset file pointer and buffers
    rewind(data);
    for (int i = 0; i < BUF_LEN; i++) buf[i] = '\0';
    for (int i = 0; i < NUM_STACKS; i++) for (int j = 0; j < BUF_LEN; j++) crates[i][j] = '\0';
    get_crates(crates, data);

    // Advance buffer until we hit the movement instructions
    while (buf[0] != 'm') fgets(buf, BUF_LEN, data);

    do {
        execute_instructions(crates, buf, 1);
    } while (fgets(buf, BUF_LEN, data) != NULL);

    printf("Top crates (Using Cratemover 9001): ");
    for (int i = 0; i < NUM_STACKS; i++) printf("%c", crates[i][strcspn(crates[i], " ") - 1]);
    printf("\n");
    
    fclose(data);

    return 0;
}

void swap_char(char &a, char &b) {
    char temp = a;
    a = b;
    b = temp;
}

void reverse_str(char * target) {
    unsigned int len = strlen(target);
    for (unsigned int i = 0; i < len / 2; i++) swap_char(target[i], target[len - i - 1]);
}    

void get_crates(char crates[][BUF_LEN], FILE * source) {
    rewind(source);
    
    char buf[BUF_LEN] = {'\0'};
    unsigned int row = 0;
    unsigned int col = 0;
    
    while (fgets(buf, BUF_LEN, source) != NULL && buf[1] != '1') {
        for (unsigned int i = 1; i < strlen(buf); i += 4) {
            crates[row][col] = buf[i];
            row++;
        }

        row = 0;
        col++;
    }

    for (int i = 0; i < NUM_STACKS; i++) reverse_str(crates[i]);
    
    rewind(source);
}

// I detest this code
void execute_instructions(char stacks[NUM_STACKS][BUF_LEN], char * instructions, bool mode) {
    unsigned int numbers[3] = {0}; // Number of crates to move, source location, target destination
    unsigned int numbers_pos = 0;

    char * word = strtok(instructions, " ");
    
    // Parse instructions with strtok (horribly ugly)
    while (word != NULL) {
        int n = atoi(word);
        word = strtok(NULL, " ");

        if (n != 0) {
            numbers[numbers_pos] = n;
            numbers_pos++;
        }
    }

    // Execute instructions
    unsigned int moves = numbers[0];
    unsigned int source = numbers[1] - 1;
    unsigned int dest = numbers[2] - 1;

    if (mode == 0) {
        for (unsigned int i = 0; i < moves; i++) {
            swap_char(stacks[source][strcspn(stacks[source], " ") - 1],
            stacks[dest][strcspn(stacks[dest], " ")]);
        }
    }

    else if (mode == 1) {
        char temp[moves + 1] = {' '};
        temp[moves] = '\0';
        
        for (unsigned int i = 0; i < moves; i++) {
            swap_char(stacks[source][strcspn(stacks[source], " ") - 1], temp[strcspn(temp, " ")]);
        }

        for (unsigned int i = 0; i < moves; i++) {
            swap_char(temp[strcspn(temp, " ") - 1], stacks[dest][strcspn(stacks[dest], " ")]);
        }
    }
}
