# Brainfuck Interpreter
Here is another brainfuck interpreter, but with a specificity. Data structure has been thought to be hyper-readable at the expense of performance, for the board (double linked list) as the instruction pointer (simple linked list) and the stack (simple linked list) ; all works with a custom structure.
This is enables people to understand better the way brainfuck works.

## Needs for build
- Linux
- Cmake

## Build
For building the interpretor follow the commands :
```
git clone https://github.com/HashDG/brainfuck-interpreter.git
cd brainfuck-interpretor
mkdir build | cd build
cmake ..
cmake --build .
```
For tests I put a Hello World program in brainfuck, for starting the interpretor do `./brainfuck helloword.b`.

## Execution
If you want to keep logs of every states of the interpreter, use the output parameter `./brainfuck -o output.txt helloworld.b`.
If you want to put directly text for execution, use the text parameter `./brainfuck -t ++.`.
- Note : you can use the output parameter either with an input file and the text parameter

