#include <stdio.h>
#define MAX 30000
int main(int argc, char* argv[]) {
	unsigned char board[MAX] = {0}, *ptr = board;
    unsigned int stack[10] = {0}, *head = stack;
    char instruction;
    FILE *code;
    if (argv[1] == "-h" || argv[1] == "--help" || argc == 1) { printf("Usage : ./brainfuck -[h] code.b"); return 0; }
    if ( (code = fopen(argv[argc - 1], "r")) == NULL) return 1;
    while ( (instruction = (char) fgetc(code)) != EOF && (&board[0] <= ptr && ptr <= &board[MAX])) {
        switch (instruction) {
            case '+': (*ptr)++; break;
            case '-': (*ptr)--; break;
            case '>': ptr++; break;
            case '<': ptr--; break; 
            case '.': putchar(*ptr); break;
            case ',': *ptr=getchar(); break;
            case '[':
                if (*ptr) {
                    *head = ( (*head) ? head++ : head ), *head = (int) ftell(code);
                } else {
                    int loops = 0;
                    while ( (instruction = (char) fgetc(code)) != ']' || loops ) (instruction == '[') ? loops++ : ( (instruction == ']') ? loops-- : 0);
                }
                break;
            case ']': (*ptr) ? (void) fseek(code, *head, SEEK_SET) : (void) head--; break;
        }
    }
    return 0;
}
