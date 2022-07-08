//
// Created by hashdg on 30/06/22.
//

#ifndef BRAINFUCK_BOARD_H
#define BRAINFUCK_BOARD_H
/**
 * @struct Cell
 * @brief this structure defines the board's cell
 * @var Cell::value
 * current value stocked in cell
 * @var Cell::next
 * pointer to the next cell
 * @var Cell::prev
 * pointer to the previous cell
 */
typedef struct Cell Cell;
/**
 * @struct Board
 * @brief this structure manages cells
 * @var Board::size
 * size of the double linked list
 * @var Board::first
 * pointer to the first cell
 * @var Board::last
 * pointer to the last cell
 */
typedef struct Board Board;

struct Cell {
    char value;
    Cell *prev;
    Cell *next;
};
struct Board {
    int size;
    Cell * first;
    Cell * last;
};

Board * initBoard();
void putChar(char);
void increment();
void decrement();
void nextCell();
void prevCell();
Cell getCell();
void show(FILE *);
void cleanBoard();

#endif //BRAINFUCK_BOARD_H
