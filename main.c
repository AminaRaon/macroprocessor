#include "macro.h"

int main() {

    FILE *receives = fopen("Z:\\prog\\laba4\\receives.txt", "r");
    FILE *answer = fopen("Z:\\prog\\laba4\\answer.txt", "w");

    if (!receives || !answer) return -1;

    macro_processor(receives, answer);

    fclose(answer);
    fclose(receives);

    return 0;
}