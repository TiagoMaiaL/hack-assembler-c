#include <stdio.h>

#define WORD_SIZE 16
#define A_VAL_SIZE 15

int main()
{
    // The first type of instruction we need to decode will be an A-instruction:
    // Example: @000000000000001
    char s[WORD_SIZE] = "@000000000000000";

    if (s[0] == '/' && s[1] == '/') {
        // comment
    } else if (s[0] == '@') {
        // a-instruction
        printf("A instruction: \n");
        
        char val[A_VAL_SIZE];

        for (int i = 1; i < WORD_SIZE; i++) {
            // TODO: Write a func to copy one array to the other using specific ranges.
            val[i] = s[i];
        }
        printf("A-instruction value: %s\n", val);
    } else if (s[0] == '(') {
        // symbol
    } else {
        // c-instruction
    }

    return 0;
}
