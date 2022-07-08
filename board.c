//
// Created by hashdg on 30/06/22.
//
#include <stdlib.h>
#include <stdio.h>
#include "board.h"

Cell * cellPtr;
Board * board;

/**
 * @brief initialize the main board
 * @return board
 */
Board * initBoard() {
    board = malloc(sizeof(*board));
    Cell * cell = malloc(sizeof(*cell));
    if (board == NULL || cell == NULL) {
        exit(EXIT_FAILURE);
    }

    cell->value = 0;
    cell->prev = NULL; // will stay null because first element
    cell->next = NULL;
    board->first = cell;
    board->last = cell;
    board->size = 1;

    cellPtr = cell;
    return board;
}

/**
 * @brief push a value in the current opened cell
 * @param value
 */
void putChar(char value) {
    cellPtr->value = value;
}

/**
 * @brief increments the current opened cell's value
 */
void increment() {
    cellPtr->value++;
}

/**
 * @brief decrements the current opened cell's value
 */
void decrement() {
    if (cellPtr->value == 0) {
        exit(EXIT_FAILURE);
    } else {
        cellPtr->value--;
    }
}

/**
 * @brief add one cell when the pointer is incremented at the last cell
 */
void addCell() {
    Cell * cell = malloc(sizeof(*cell));
    if (board == NULL || cell == NULL) {
        exit(EXIT_FAILURE);
    }

    cell->value = 0; // valeur = 0
    cell->prev = board->last; // avant = dernier de la liste
    cell->next = NULL; // après = null
    board->last->next = cell; // next du dernier = la nouvelle
    board->last = cell; // dernier du board = la nouvelle
    board->size++; // taille ++

    cellPtr = cell;
}

/**
 * @brief increments the pointer
 */
void nextCell() {
    if (cellPtr->next == NULL) {
        addCell();
    } else {
        cellPtr = cellPtr->next;
    }
}

/**
 * @brief decrements the pointer
 */
void prevCell() {
    if (cellPtr->prev == NULL) {
        exit(EXIT_FAILURE);
    } else {
        cellPtr = cellPtr->prev;
    }
}

/**
 * @brief cell getter only
 * @return cell structure with information
 */
Cell getCell() {
    return * cellPtr;
}

/**
 * @brief print the board content
 */
void show(FILE * output) {
    if (board == NULL) {
        exit(EXIT_FAILURE);
    }
    if (output == NULL) {
        exit(EXIT_FAILURE);
    }

    Cell *current = board->first;
    int i = 0;

    while (current != NULL) {
        fprintf(output, "%d", current->value);
        if (current->next != NULL) {
            fprintf(output, "|");
        }
        current = current->next;
        i++;
    }
    fprintf(output, "\n");
}

/**
 * @brief clean the cells and the board structures from memory
 */
void cleanBoard() {
    Cell * cell = board->first;
    while (cell->next != NULL) {
        cell = cell->next;
        free(cell);
    }
    free(board);
}