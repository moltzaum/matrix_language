#ifndef TYPES_H
#define TYPES_H

#include "Enviroment.h"
#include "Matrix.h"
#include "stack.h"

enum {
    INT_T,
    DOUB_T,
    IDEN_T,
    MATR_T,
    ROW_T   //unused currently
} typedef TYPE;

static inline
double toDouble(uint64_t data) {
  double d;
  PUSH (data);
  POP (d);
  return d;
}

static inline
void print_data(uint64_t data, uint32_t type) {
  switch (type) {
  case INT_T:
    printf ("%d ", (int) data);
    break;
  case DOUB_T:
    printf ("%f ", toDouble(data));
    break;
  case MATR_T:
    print_matrix((struct Matrix*) data);
    break;
  case ROW_T:
    //I don't even know if this is accessible. print_data gets called on identifiers,
    //but I don't think identifiers are allowed to hold rows because of the compiler.
    printf ("row data is %p or %llu\n", (void*) data, data);
    //print_row((struct Row*));
  default:
    printf ("? ");
  }
}

#endif
