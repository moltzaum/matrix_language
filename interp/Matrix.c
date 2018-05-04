#include "Matrix.h"
#include "types.h"
#include <math.h>

static void dest_add (struct Row r1, struct Row r2);
static void dest_sub (struct Row r1, struct Row r2);
//static void dest_div(uint32_t type, struct Row row, int div);
static void dest_mul (struct Row row, uint32_t type, uint64_t data);
static void dest_div (struct Row row, uint32_t type, uint64_t data);

static bool is_ref (struct Matrix* m) {
    
    //don't think I need to worry about ints
    if (m->type == DOUB_T) {
        double d;
        for (int i = 0; i < m->rows; i++) {
            PUSH (m->data[i][i]);
            POP (d);
            if (d > 1.00000001 || d < 0.99999999) {
                return false;
            }
        }
        return true;
    }
}

void ref (struct Matrix* m) {
    
    if (is_ref (m))
        return;
    
    struct Row row, row2;
    for (int i = 0; i < m->rows; i++) {
        
        //divide row of leading term by leading term
        row = (struct Row) {m, i, 0};
        //divRow(m->type, m->data[i][0], row);
        //dest_div(m->type, row, m->data[i][i]);
        //printf ("div for %d with %f\n", i, toDouble(m->data[i][i]));
        dest_div (row, m->type, m->data[i][i]);
        
        /*
        printf ("matrix:\n");
        print_matrix (m);
        printf ("\n");
        //*/
        
        for (int j = i+1; j < m->rows; j++) {
            
            row2 = (struct Row) {m, j, 0};
            if (m->type == INT_T) {
                int data = (int) m->data[j][i];
                if (data > 1) {
                    while (m->data[j][i] != 0)
                        dest_sub (row2, row);
                } else if (data < 1) {
                    while (m->data[j][i] != 0)
                        dest_add (row2, row);
                }
            } else {
                double data;
                PUSH (m->data[j][i]);
                POP (data);
                
                PUSH (m->data[j][i]);
                POP (data);
                //printf ("[%d,%d] = %f\n", j, i, data);
                if (data > 0.000000001 || data < 0.000000001) {
                    dest_div (row2, m->type, m->data[j][i]);
                    dest_sub (row2, row);
                }
            }
        }
    }
}

//note: not safe for doubles and may not be safe for some integer matrices
void rref (struct Matrix* m) {
    
    ref (m);
    struct Row row, row2;
    for (int i = 0; i < m->rows; i++) {
        
        row = (struct Row) {m, i, 0};
        for (int j = i+1; j < m->rows; j++) {
              
            row2 = (struct Row) {m, j, 0};
            if (m->type == INT_T) {
                int data = (int) m->data[i][j];
                if (data > 1) {
                    while (m->data[i][j] != 0)
                        dest_sub (row, row2);
                } else if (data < 1) {
                    while (m->data[i][j] != 0)
                        dest_add (row, row2);
                }
            } else {
                double data;
                PUSH (m->data[i][j]);
                POP (data);
                
                //divide row by data, subtract lower row, then multiply by data
                dest_div (row, m->type, m->data[i][j]);
                
                dest_sub (row, row2);
                
                PUSH (data);
                uint64_t mul_data;
                POP (mul_data);
                dest_mul (row, m->type, mul_data);
            }
        }
    }
}

void print_matrix (struct Matrix *m) {
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++)
      print_data(m->data[i][j], m->type);
    printf ("\n");
  }
}

void print_row (struct Matrix *m, int i) {
  for (int j = 0; j < m->cols; j++)
    print_data(m->data[i][j], m->type);
  printf ("\n");
}

struct Matrix* matrix_constructor (int n, int m) {
    //Allocate on the heap so that data doesn't get deallocated. I want to make
    //sure this is correct, so test writing this a different way later. (Note
    //that this message is duplicate. I should resolve this later.)
    struct Matrix* mat = malloc(sizeof(struct Matrix));
    
    mat->data = malloc(n * sizeof(uint64_t*));
    for (int i = 0; i < n; i++)
        mat->data[i] = malloc(m * sizeof(uint64_t));
    
    mat->rows = n;
    mat->cols = m;
    //mat->type is left uninitialized
    return mat;
}

void matrix_destructor (struct Matrix* matrix) {
    //TODO
}

void row_copy (struct Row r1, struct Row r2) {
    int i1 = r1.index;
    int i2 = r2.index;
    for (int j = 0; j < r1.matrix->cols; j++)
        r1.matrix->data[i1][j] = r2.matrix->data[i2][j];
}

static void dest_add (struct Row r1, struct Row r2) {
    int i1 = r1.index;
    int i2 = r2.index;
    for (int j = 0; j < r1.matrix->cols; j++)
        r1.matrix->data[i1][j] += r2.matrix->data[i2][j];
}

//NOTE: I don't currently check to make sure both matrices have the same type
static void dest_sub (struct Row r1, struct Row r2) {
    int i1 = r1.index;
    int i2 = r2.index;
    if (r1.matrix->type == INT_T) {
        for (int j = 0; j < r1.matrix->cols; j++)
            r1.matrix->data[i1][j] -= r2.matrix->data[i2][j];
    } else {
        double d1, d2;
        for (int j = 0; j < r1.matrix->cols; j++) {
            PUSH (r2.matrix->data[i2][j]);
            POP (d1);
            PUSH (r1.matrix->data[i1][j]);
            POP (d2);
            d2 -= d1;
            PUSH (d2);
            POP (r1.matrix->data[i1][j]);
        }
    }
}

static void dest_mul (struct Row row, uint32_t type, uint64_t data) {
    
    if (row.matrix->type == INT_T) {
        for (int i = 0; i < row.matrix->cols; i++)
            row.matrix->data[row.index][i] = (int) row.matrix->data[row.index][i] * (int) data;
    } else {
        double d1, d2;
        for (int i = 0; i < row.matrix->cols; i++) {
            
            PUSH (row.matrix->data[row.index][i]);
            POP (d1);
            if (type == DOUB_T) {
                PUSH (data);
                POP (d2);
            } else d2 = data;
            
            d1 *= d2;
            PUSH (d1);
            POP (row.matrix->data[row.index][i]);
        }
    }
}

static void dest_div (struct Row row, uint32_t type, uint64_t data) {
    
    if (row.matrix->type == INT_T) {
        for (int i = 0; i < row.matrix->cols; i++)
            row.matrix->data[row.index][i] = (int) row.matrix->data[row.index][i] / (int) data;
    } else {
        double d1, d2;
        for (int i = 0; i < row.matrix->cols; i++) {
            
            PUSH (row.matrix->data[row.index][i]);
            POP (d1);
            if (type == DOUB_T) {
                PUSH (data);
                POP (d2);
            } else d2 = data;
            
            //printf ("%f / %f = %f\n", d1, d2, d1/d2);
            
            d1 /= d2;
            PUSH (d1);
            POP (row.matrix->data[row.index][i]);
        }
    }
}


//Consider making a macro for row access
struct Row mulRow(uint32_t type, uint64_t data, struct Row row) {
    
    int index = register_variable("__MATRIX_TEMP__");
    if (index == -1) {
        //free current tmp matrix before allocating new one
        index = hash_variable("__MATRIX_TEMP__");
    }
    struct Matrix* mat = matrix_constructor (1, row.matrix->cols);
    struct Variable* v = lookup_variable(index);
    v->data = (uint64_t) mat;
    mat->type = v->type; //v type vs type?
    
    struct Row tmp = {mat, 0, 1};
    row_copy (tmp, row);
    
    for (int j = 0; j < mat->cols; j++)
        mat->data[0][j] *= data;
    return tmp;
}

//the "type" is the type associated with the data
struct Row divRow(uint32_t type, uint64_t data, struct Row row) {
    
    int index = register_variable("__MATRIX_TEMP__");
    if (index == -1) {
        //free current tmp matrix before allocating new one
        index = hash_variable("__MATRIX_TEMP__");
    }
    struct Matrix* mat = matrix_constructor (1, row.matrix->cols);
    struct Variable* v = lookup_variable(index);
    v->data = (uint64_t) mat;
    mat->type = v->type; //v type vs type?
    
    struct Row tmp = {mat, 0, 1};
    row_copy (tmp, row);
    
    if (row.matrix->type == INT_T) {
        for (int j = 0; j < mat->cols; j++)
            mat->data[0][j] /= data;
    } else {
        
        double d1, d2;
        for (int j = 0; j < mat->cols; j++) {
            
            PUSH (mat->data[0][j]);
            POP (d1);
            if (type == DOUB_T) {
                PUSH (data);
                POP (d2);
            } else d2 = data;
            
            d1 /= d2;
            PUSH (d1);
            POP (mat->data[0][j]);
        }
    }
    return tmp;
}

//The resultant row refers to the external variable __MATRIX_TMP__
struct Row addRows(struct Row r1, struct Row r2) {
  
  int index = register_variable("__MATRIX_TEMP__");
  if (index == -1) {
    //free current tmp matrix before allocating new one
    index = hash_variable("__MATRIX_TEMP__");
  }
  
  //TODO: Do better error handling and cleanup
  if (r1.matrix->cols != r2.matrix->cols) {
    printf ("Error: Rows need to be the same size.\n");
    exit (-1);
  }
  
  struct Matrix* mat = matrix_constructor (1, r1.matrix->cols);
  struct Variable* v = lookup_variable(index);
  v->data = (uint64_t) mat;
  mat->type = v->type;
  
  struct Row tmp = {mat, 0, 1};
  row_copy (tmp, r1);
  dest_add (tmp, r2);
  return tmp;
}

struct Row subRows(struct Row r1, struct Row r2) {
  
  int index = register_variable("__MATRIX_TEMP__");
  if (index == -1) {
    //free current tmp matrix before allocating new one
    index = hash_variable("__MATRIX_TEMP__");
  }
  
  if (r1.matrix->cols != r2.matrix->cols) {
    printf ("Error: Rows need to be the same size.\n");
    exit (-1);
  }
  
  struct Matrix* mat = matrix_constructor (1, r1.matrix->cols);
  struct Variable* v = lookup_variable(index);
  v->data = (uint64_t) mat;
  mat->type = v->type;
  
  struct Row tmp = {mat, 0, 1};
  row_copy (tmp, r1);
  dest_sub (tmp, r2);
  return tmp;
}

void cast_matrix (struct Matrix *m, uint32_t type) {
    
    if (m->type == (int) type) return;
    
    double d;
    if (type == INT_T) {
        m->type = INT_T;
        for (int i = 0; i < m->rows; i++) {
            for (int j = 0; j < m->cols; j++) {
                PUSH (m->data[i][j]);
                POP (d);
                m->data[i][j] = (uint64_t) round(d);
            }
        }
    } else {
        m->type = DOUB_T;
        for (int i = 0; i < m->rows; i++) {
            for (int j = 0; j < m->cols; j++) {
                d = (int) m->data[i][j];
                PUSH (d);
                POP (m->data[i][j]);
            }
        }
    }
}

void swapRows(struct Row r1, struct Row r2) {
    
    if (r1.tmp || r2.tmp) {
        printf ("Error: Cannot swap temporary matrix.\n");
        exit (-1);
    }
    
    uint64_t tmp;
    int i1 = r1.index;
    int i2 = r2.index;
    for (int j = 0; j < r1.matrix->cols; j++) {
        tmp = r1.matrix->data[i1][j];
        r1.matrix->data[i1][j] = r2.matrix->data[i2][j];
        r2.matrix->data[i2][j] = tmp;
    }
}


