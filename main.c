#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "instructionPointer.h"

/**
 * @return brainfuck code as a string and some interpretation parameters
 */
int main(int argc, char * argv[]) {
    char * text = NULL;
    FILE * output = NULL;

    time_t t = time(NULL);
    struct tm * tm = localtime(&t);
    char date[64];
    strftime(date, sizeof(date), "%c", tm);

    for (int i = 1; i < argc ; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            text = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-o") == 0) {
            output = fopen(argv[i + 1], "a");
            i++;
        } else if (strcmp(argv[i], "-h") == 0) {
            printf("Usage : ./brainfuck -[to] file.b\n\nArguments:\n\t-t (text): provides code as text directly to the interpreter\n\t-o (output): provides an output file to store the interpreter states");
            return 0;
        }
    }

    if (text == NULL) { // a file
        FILE * file = fopen(argv[argc - 1], "r");

        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);

        text = malloc(size * sizeof(char));

        for (int i = 0; i < size - 1; i++) {
            text[i] = fgetc(file);
        }
    }

    initBoard();
    initInstructionPointer(text);
    if (output != NULL) {
        fprintf(output, "### %s ###\n", date);
    }
    while (currentInstruction != NULL) {
        Instruction * instruction = currentInstruction;
        switch (instruction->opcode) {
            case ADD:
                increment();
                jump();
                break;
            case SUB:
                decrement();
                jump();
                break;
            case PUT:;
                char val;
                scanf("%c", &val);
                putChar(val);
                jump();
                break;
            case GET:
                printf("%c", getCell().value);
                jump();
                break;
            case PTR_ADD:
                nextCell();
                jump();
                break;
            case PTR_SUB:
                prevCell();
                jump();
                break;
            case BEGIN_LOOP:
                if (getCell().value == 0) {
                    if (peek() == instruction) {
                        pop();
                    }
                    jumpToEOL();
                } else {
                    if (peek() != instruction) { // push only if it's not mentioned
                        push();
                    }
                }
                jump();
                break;
            case END_LOOP:
                branch(peek());
                break;
            default:
                printf("\nunknown instruction: %c\n", instruction->opcode);
        }
        if (output != NULL) {
            show(output);
        }
    }
    if (output != NULL) {
        fprintf(output, "### ###\n");
    }

    cleanBoard();
    cleanInstructionPointer();
    return 0;
}

