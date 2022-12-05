#include <stdio.h>

#define BUF_LEN 8

unsigned int eval_rochambeau_v1(char xyz, char abc);
unsigned int eval_rochambeau_v2(char xyz, char abc);

int main(void) {
    FILE * data = fopen("input.txt", "r");

    unsigned int score1 = 0;
    unsigned int score2 = 0;
    char buf[BUF_LEN] = {'\0'};

    while (fgets(buf, BUF_LEN, data) != NULL) {
        score1 += eval_rochambeau_v1(buf[2], buf[0]);
        score2 += eval_rochambeau_v2(buf[2], buf[0]);
    }

    printf("Final score with method 1: %u\n", score1);
    printf("Final score with method 2: %u\n", score1);

    fclose(data);

    return 0;
}

unsigned int eval_rochambeau_v1(char xyz, char abc) {
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

unsigned int eval_rochambeau_v2(char xyz, char abc) {
    // Lose
    if (xyz == 'X' && abc == 'A') return eval_rochambeau_v1('Z', 'A');
    if (xyz == 'X' && abc == 'B') return eval_rochambeau_v1('X', 'B');
    if (xyz == 'X' && abc == 'C') return eval_rochambeau_v1('Y', 'C');

    // Draw
    if (xyz == 'Y' && abc == 'A') return eval_rochambeau_v1('X', 'A');
    if (xyz == 'Y' && abc == 'B') return eval_rochambeau_v1('Y', 'B');
    if (xyz == 'Y' && abc == 'C') return eval_rochambeau_v1('Z', 'C');
    
    // Win
    if (xyz == 'Z' && abc == 'A') return eval_rochambeau_v1('Y', 'A');
    if (xyz == 'Z' && abc == 'B') return eval_rochambeau_v1('Z', 'B');
    if (xyz == 'Z' && abc == 'C') return eval_rochambeau_v1('X', 'C');

    return 0;
}
