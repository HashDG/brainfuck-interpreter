//
// Created by hashdg on 01/07/22.
//
#include <stdio.h>
#include <stdlib.h>
#include "instructionPointer.h"

Instruction * currentInstruction;
InstructionPointer * instructionPointer;
Stack * stack;

/**
 * @brief determine if the char put in parameter is a Brainfuck opcode
 * @param in
 * @return
 */
int isOpcode(char in) {
    switch (in) {
        case ADD:
        case SUB:
        case PTR_ADD:
        case PTR_SUB:
        case PUT:
        case GET:
        case BEGIN_LOOP:
        case END_LOOP:
            return 1;
        default:
            return 0;
    }
}

/**
 * @brief useful to ensure the integrity of the instruction pointer
 */
void readPtr() {
    Instruction * instruction = instructionPointer->first;
    int size = 0;
    while (size < instructionPointer->size) {
        printf("%c", instruction->opcode);
        instruction = instruction->next;
        size++;
    }
    printf("\n");
}

/**
 * @brief initialize the stack and the instruction pointer and fill the pointer
 * @param instructions to execute
 */
void initInstructionPointer(char instructions[]) {
    if (!instructions[0]) return; // return if empty

    instructionPointer = malloc(sizeof(*instructionPointer));
    stack = malloc(sizeof(*stack));
    stack->size = 0;
    stack->head = NULL;

    Instruction * first = NULL;
    Instruction * previous = NULL;

    int i = 0;
    for (; instructions[i] != '\0'; i++) {
        if (isOpcode(instructions[i])) {
            Instruction *instruction = malloc(sizeof(*instruction));
            instruction->opcode = instructions[i];
            instruction->next = NULL;

            if (first == NULL && previous == NULL) { // si c'est le premier
                first = instruction;
                instructionPointer->first = first;
            } else {
                previous->next = instruction;
            }
            previous = instruction;
        }
    }
    instructionPointer->size = i;
    currentInstruction = instructionPointer->first;
}

/**
 * @brief jump to the next instruction
 */
void jump() {
    currentInstruction = currentInstruction->next;
}

/**
 * @brief jump to the end of the loop (EOL) it has to avoid nested loops
 */
void jumpToEOL() {
    int skips = 0;
    jump();
    while (currentInstruction->opcode != END_LOOP || skips > 0) {
        if (currentInstruction->opcode == BEGIN_LOOP) {
            skips++;
        } else if (currentInstruction->opcode == END_LOOP) {
            if (skips > 0) {
                skips--;
            }
        }
        jump();
    }
}

/**
 * @brief go back to a past instruction
 * @param instruction to branch to
 */
void branch(Instruction * instruction) { // branch if end of loop to the beginning
    currentInstruction = instruction;
}

/**
 * @brief push the current instruction in the stack
 */
void push() {
    StackElement * element = malloc(sizeof(*element));
    element->instruction = currentInstruction;

    if (stack->head == NULL) {
        element->next = NULL;
    } else {
        element->next = stack->head;
    }
    stack->head = element;
    stack->size++;
}

/**
 * @brief remove the last pushed instruction from the stack
 */
void pop() {
    StackElement * element = stack->head;
    stack->head = element->next;
    stack->size--;

    free(element);
}

/**
 * @brief get the last pushed instruction without removing it
 * @return
 */
Instruction * peek() {
    if (stack->head == NULL) {
        return NULL;
    }
    return stack->head->instruction;
}

/**
 * @brief empty the instruction pointer and stack
 */
void cleanInstructionPointer() {
    while(stack->size != 0) {
        pop();
    }

    Instruction * instr = instructionPointer->first;
    while(instr->next != NULL) {
        Instruction * toFree = instr;
        instr = instr->next;
        free(toFree);
        instructionPointer->size--;
    }

    free(instr);
    free(instructionPointer);
    free(stack);
}


