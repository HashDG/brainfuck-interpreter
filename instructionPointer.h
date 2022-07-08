//
// Created by hashdg on 01/07/22.
//

#ifndef BRAINFUCK_INSTRUCTIONPOINTER_H
#define BRAINFUCK_INSTRUCTIONPOINTER_H

/**
 * @enum OPCODE
 * @brief stock all the opcodes
 */
typedef enum OPCODE OPCODE;
/**
 * @struct InstructionPointer
 * @brief this structure manage instructions
 * @var InstructionPointer::size
 * stocks size of the linked list
 * @var InstructionPointer::first
 * pointer to the first instruction
 */
typedef struct InstructionPointer InstructionPointer;
/**
 * @struct Instruction
 * @brief this structure defines instructions
 * @var Instruction::opcode
 * stocks the opcode of the instruction
 * @var Instruction::next
 * pointer to the next instruction
 */
typedef struct Instruction Instruction;
/**
 * @struct Stack
 * @brief this structure manage stacks
 * @var Stack::size
 * stocks size of the stack
 * @var Instruction::head
 * pointer to the first out member
 */
typedef struct Stack Stack;
/**
 * @struct StackElement
 * @brief this structure manage stacks members
 * @var StackElement::instruction
 * stocks the instruction associated with the stack element
 * @var StackElement::next
 * pointer to the next stack element
 */
typedef struct StackElement StackElement;


enum OPCODE {
    ADD = '+',
    SUB = '-',
    PTR_ADD = '>',
    PTR_SUB = '<',
    PUT = ',',
    GET = '.',
    BEGIN_LOOP = '[',
    END_LOOP = ']'
};

/**
 * @brief the current instruction
 */
extern Instruction * currentInstruction;

struct Instruction {
    OPCODE opcode;
    Instruction * next;
};
struct InstructionPointer {
    int size;
    Instruction * first;
};
struct StackElement {
    Instruction * instruction;
    StackElement * next;
};
struct Stack {
    int size;
    StackElement * head;
};

void initInstructionPointer(char[]);
void jump();
void jumpToEOL();
void branch(Instruction *);
void push();
void pop();
Instruction * peek();
void cleanInstructionPointer();

#endif //BRAINFUCK_INSTRUCTIONPOINTER_H
