# Brainfuck Interpreter
This version of the interpreter is made to be minimalist. It can be lightened but I wanted to keep some docs command and error tracking.

## Needs for build
- Linux
- Cmake

## Build
For building the interpretor follow the commands :
```
git clone https://github.com/HashDG/brainfuck-interpreter.git
cd brainfuck-interpreter
mkdir build | cd build
cmake ..
cmake --build .
```
For tests I put a Hello World program in brainfuck, for starting the interpretor do `./brainfuck helloword.b`.

## Execution
For more informations use the `--help` argument.

