#include <stdio.h>
#include <string.h>
#define MAX 30000

int main(int argc, char* argv[]) {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("Usage : ./brainfuck -[h] code.b");
        return 0;
    }

    FILE *code = fopen(argv[argc - 1], "r");
    if (code == NULL) {
        printf("\nERROR: can't open brainfuck file");
        return 1;
    }

    unsigned char board[MAX] = {0};
    unsigned int stack[5] = {0};

    unsigned char *ptr = board;
    unsigned int *head = stack;

    char instruction = (char) fgetc(code);

    while (instruction != EOF) {
        switch (instruction) {
            case '+':
                (*ptr)++;
                break;
            case '-':
                (*ptr)--;
                break;
            case '>':
                if (ptr != &board[MAX]) {
                    ptr++;
                    break;
                }
                return 2;
            case '<':
                if (ptr != &board[0]) {
                    ptr--;
                    break;
                }
                return 2;
            case '.':
                printf("%c", *ptr);
                break;
            case ',':;
                char value;
                scanf("%c", &value);
                *ptr = value;
                break;
            case '[':
                if (*ptr) {
                    if (*head) head++;
                    *head = (int) ftell(code);
                } else {
                    int loops = 0;
                    while (instruction != ']' || loops) {
                        if (instruction == '[') loops++;
                        if (instruction == ']') loops--;
                        instruction = (char) fgetc(code);
                    }
                }
                break;
            case ']':
                if (*ptr) {
                    fseek(code, *head, SEEK_SET);
                } else {
                    head--;
                }
                break;
            default:
                if (instruction == '\n') break;
                printf("\nERROR: Unknown Instruction: %c | %d", instruction, (int) instruction);
                return 1;
        }
        instruction = (char) fgetc(code);
    }
    return 0;
}
