#include "file_reader.h"
#include <stdio.h>

int get_high_score() {
    int a;
    FILE *score = fopen(FILE_PATH, "r+");
    if (score == NULL)
        return 0;
    fscanf(score,"%d", &a);
    fclose(score);
    return a;
}

void set_high_score(int score) {
    FILE *score_file = fopen(FILE_PATH, "w+");
    fprintf(score_file,"%d", score);
    fclose(score_file);
}