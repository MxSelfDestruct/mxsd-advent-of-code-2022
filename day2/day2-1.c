#include <stdio.h>

const unsigned int BUF_LEN = 8;

unsigned int eval_rochambeau(char xyz, char abc);

int main(void) {
    FILE * data = fopen("day2.txt", "r");

    unsigned int score = 0;
    char buf[BUF_LEN];

    while (fgets(buf, BUF_LEN, data) != NULL) {
        score += eval_rochambeau(buf[2], buf[0]);
    }

    printf("Final score: %u\n", score);

    fclose(data);

    return 0;
}

unsigned int eval_rochambeau(char xyz, char abc) {
    unsigned int score = 0;
    
    if (xyz == 'X') {
        score = 1;
        
        if (abc == 'C') { score += 6; } // Win
        if (abc == 'A') { score += 3; } // Draw
        if (abc == 'B') { score += 0; } // Loss
    }

    if (xyz == 'Y') {
        score = 2;
        
        if (abc == 'A') { score += 6; }
        if (abc == 'B') { score += 3; }
        if (abc == 'C') { score += 0; }
    }

    if (xyz == 'Z') {
        score = 3;
        
        if (abc == 'B') { score += 6; }
        if (abc == 'C') { score += 3; }
        if (abc == 'A') { score += 0; }
    }

    return score;
}
