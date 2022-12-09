#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 128

bool tree_visible(char * * forest, int x, int y);
int tree_score(char * * forest, int x, int y);
int visible_trees(char * * forest, int lines, int length);
int highest_score(char * * forest, int lines, int length);

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
    char * forest[length];
    for (int i = 0; i < lines; i++) forest[i] = malloc(length * sizeof(char));

    for (int i = 0; fgets(buf, BUF_LEN, data) != NULL; i++) {
        buf[strcspn(buf, "\n")] = '\0'; // Send trailing newline to hell
        strcpy(forest[i], buf);
    }

    fclose(data);

    printf("Visible trees: %u\n", visible_trees(forest, lines, length));
    printf("Highest visibility score: %u\n", highest_score(forest, lines, length));

    return 0;
}

bool tree_visible(char * * forest, int x, int y) {
    // Check if tree on edge
    if (x == 0 || forest[y][x + 1] == '\0' || y == 0 || forest[y + 1][x] == '\0') return true;

    char tree = forest[y][x];
    bool vis_n = true;
    bool vis_s = true;
    bool vis_w = true;
    bool vis_e = true;

    // Check if visible from north
    for (int i = 0; i < y; i++) {
        if (forest[i][x] >= tree) {
            vis_n = false;
            break;
        }
    }

    // Check if visible from south
    for (int i = y + 1; forest[i][x] != '\0'; i++) {
        if (forest[i][x] >= tree) {
            vis_s = false;
            break;
        }
    }

    // Check if visible from west
    for (int i = 0; i < x; i++) {
        if (forest[y][i] >= tree) {
            vis_w = false;
            break;
        }
    }

    // Check if visible from east
    for (int i = x + 1; forest[y][i] != '\0'; i++) {
        if (forest[y][i] >= tree) {
            vis_e = false;
            break;
        }
    }

    return (vis_n || vis_s || vis_w || vis_e);
}

int tree_score(char * * forest, int x, int y) {
    char tree = forest[y][x];

    int vis_n = 0;
    int vis_s = 0;
    int vis_w = 0;
    int vis_e = 0;

    // Count visible trees to north
    for (int i = y - 1; i >= 0; i--) {
        vis_n++;
        if (forest[i][x] >= tree) break;
    }

    // Count visible trees to south
    for (int i = y + 1; forest[i][x] != '\0'; i++) {
        vis_s++;
        if (forest[i][x] >= tree) break;
    }

    // Count visible trees to west
    for (int i = x - 1; i >= 0; i--) {
        vis_w++;
        if (forest[y][i] >= tree) break;
    }

    // Count visible trees to east
    for (int i = x + 1; forest[y][i] != '\0'; i++) {
        vis_e++;
        if (forest[y][i] >= tree) break;
    }

    return vis_n * vis_s * vis_e * vis_w;
}

int visible_trees(char * * forest, int lines, int length) {
    int visible_trees = 0;

    for (int i = 0; i < lines - 1; i++) {
        for (int j = 0; j < length - 1; j++) visible_trees += tree_visible(forest, j, i);
    }

    return visible_trees;
}

int highest_score(char * * forest, int lines, int length) {
    int highest_score = 0;

    for (int i = 0; i < lines - 1; i++) {
        for (int j = 0; j < length - 1; j++) {
            int score = tree_score(forest, j, i);
            if (score > highest_score) highest_score = score;
        }
    }

    return highest_score;
}
