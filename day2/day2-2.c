#include <stdio.h>

#define BUF_LEN 8

unsigned int eval_rochambeau(char xyz, char abc);
unsigned int eval_rochambeau_2(char xyz, char abc);

int main(void) {
    FILE * data = fopen("input.txt", "r");

    unsigned int score = 0;
    char buf[BUF_LEN] = {'\0'};

    while (fgets(buf, BUF_LEN, data) != NULL) {
        score += eval_rochambeau_2(buf[2], buf[0]);
    }

    printf("Final score: %u\n", score);

    fclose(data);

    return 0;
}

unsigned int eval_rochambeau(char xyz, char abc) {
    unsigned int score = xyz - 'X' + 1;
    
    if (xyz == 'X' && abc == 'C') score += 6; // Win
    if (xyz == 'X' && abc == 'A') score += 3; // Draw
    if (xyz == 'X' && abc == 'B') score += 0; // Loss

    if (xyz == 'Y' && abc == 'A') score += 6;
    if (xyz == 'Y' && abc == 'B') score += 3;
    if (xyz == 'Y' && abc == 'C') score += 0;

    if (xyz == 'Z' && abc == 'B') score += 6;
    if (xyz == 'Z' && abc == 'C') score += 3;
    if (xyz == 'Z' && abc == 'A') score += 0;

    return score;
}

unsigned int eval_rochambeau_2(char xyz, char abc) {
    // Lose
    if (xyz == 'X' && abc == 'A') return eval_rochambeau('Z', 'A');
    if (xyz == 'X' && abc == 'B') return eval_rochambeau('X', 'B');
    if (xyz == 'X' && abc == 'C') return eval_rochambeau('Y', 'C');

    // Draw
    if (xyz == 'Y' && abc == 'A') return eval_rochambeau('X', 'A');
    if (xyz == 'Y' && abc == 'B') return eval_rochambeau('Y', 'B');
    if (xyz == 'Y' && abc == 'C') return eval_rochambeau('Z', 'C');
    
    // Win
    if (xyz == 'Z' && abc == 'A') return eval_rochambeau('Y', 'A');
    if (xyz == 'Z' && abc == 'B') return eval_rochambeau('Z', 'B');
    if (xyz == 'Z' && abc == 'C') return eval_rochambeau('X', 'C');

    return 0;
}
