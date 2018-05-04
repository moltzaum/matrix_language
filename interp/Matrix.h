#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/* Perhaps my structure is a little odd, but this is how I'm going to organize it:
 * A Matrix is a 2D array of uint64_t (which can hold integers and doubles). Even
 * though this kind of "generic type" can also hold addresses, it was never designed
 * with that in mind. Perhaps I can make a much more flexible definition later once
 * I am more proficient with bnfc.
 * 
 * "Rows" hold an identifier that is a matrix, and an index. These rows are not the kind
 * of row that a matrix is created with, nor are they standalone, nor are they used
 * internally in the matrix struct. Any temporary row that I'm parsing will need to store
 * its matrix into a system variable called "__MATRIX_TEMP__", which should be sufficient
 * since I will only ever need one temporary variable at a time. */
struct Matrix {
    uint64_t **data;
    int rows, cols;
    int type;
};

struct Row {
    struct Matrix *matrix;
    int index;
    bool tmp;
};

//ref and rref is destructive
void ref (struct Matrix* m);
void rref (struct Matrix*);

void print_matrix (struct Matrix*);
void print_row (struct Matrix*, int);

/* In some cases these might come in handy. The main method for producing a matrix
 * however does not know the size of the matrix initially and must iterate. Perhaps
 * we can iterate it once, then use this matrix constructor to make the code simpler.
 * 
 * It seems the major thing I need this for though, is to allocate a temporary matrix.
 * Right now, I'm not all that concerned with the destructor.
 */
struct Matrix* matrix_constructor (int, int);
void matrix_destructor (struct Matrix*);

//Destructive methods: (make static?)

//Whole Matrix Operations
//matrix_copy (struct Matrix*, struct Matrix*)
//destructive_add (struct Matrix*, struct Matrix*)

//Individual Row Operations
void row_copy (struct Row, struct Row);
//static void dest_add (struct Row, struct Row);

void cast_matrix (struct Matrix*, uint32_t type);
struct Row mulRow(uint32_t type, uint64_t data, struct Row);
struct Row divRow(uint32_t type, uint64_t data, struct Row);
struct Row addRows(struct Row, struct Row);
struct Row subRows(struct Row, struct Row);
void swapRows(struct Row, struct Row);

#endif

