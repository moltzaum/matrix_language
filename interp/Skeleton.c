/*** BNFC-Generated Visitor Traversal Skeleton. ***/
/* This traverses the abstract syntax tree.
   To use, copy Skeleton.h and Skeleton.c to
   new files. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Skeleton.h"
#include "Enviroment.h"
#include "Matrix.h"
#include "Latex.h"
#include "stack.h"
#include "types.h"

#define UNUSED __attribute__ ((unused))

void visitProgram(Program _p_)
{
  switch(_p_->kind)
  {
  case is_Prog:
    printf ("Starting up program...\n");
    init_enviroment();
    visitListStm(_p_->u.prog_.liststm_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when interpreting Program!\n");
    exit(1);
  }
}

void visitListStm(ListStm liststm)
{
  while(liststm)
  {
    visitStm(liststm->stm_);
    liststm = liststm->liststm_;
  }
}

#define QUOTE(...) #__VA_ARGS__

void visitStm(Stm _p_)
{
  uint64_t data;
  uint32_t type;
  struct Variable *var;
  
  switch(_p_->kind) {
  
  case is_InitTex:
  {
    if (tex_file != NULL) {
        printf ("Did not create a new file. Close the previous file first.\n");
        return;
    }
    
    tex_file = fopen(_p_->u.inittex_.string_1, "w");
    
    if (tex_file == NULL) {
        printf ("There was an error opening the file.\n");
        return;
    }
    
    fprintf(tex_file, QUOTE(
        \\documentclass{article} \n
        \\usepackage{amsmath}    \n
        \\title{%s}              \n
        \\author{%s}             \n
        \\date{\\today}          \n
        \\begin{document}        \n
        \\maketitle              \n),
       _p_->u.inittex_.string_2,
       _p_->u.inittex_.string_3
    );
    break;
  }
  
  case is_OutTex:
    visitIdent(_p_->u.outtex_.ident_);
    POP(type);
    POP(data);
    dataTex (data, type);
    //if (type != MATR_T) printf("\n");
    break;
  
  case is_Redirect:
    out_tex = true;
    break;
  
  case is_SOutTex:
    //TODO find and replace `\' with `\\'?
    fprintf(tex_file, "%s\n\n", _p_->u.souttex_.string_);
    break;
  
  case is_CloseTex:
    if (tex_file != NULL) {
        fprintf(tex_file, "\\end{document}\n");
        fclose(tex_file);
    } else printf ("There is no file to close\n");
    
    break;
  
  case is_Print:
    visitIdent(_p_->u.print_.ident_);
    POP(type);
    POP(data);
    print_data(data, type);
    if (type != MATR_T) printf("\n");
    
    if (out_tex) {
        _p_->kind = is_OutTex;
        _p_->u.outtex_.ident_ = _p_->u.print_.ident_;
        visitStm(_p_);
    }
    break;
  
  case is_SPrint:
    printf("%s\n", _p_->u.sprint_.string_);
    
    if (out_tex) {
        _p_->kind = is_SOutTex;
        _p_->u.souttex_.string_ = _p_->u.sprint_.string_;
        visitStm(_p_);
    }
    break;
  
  case is_RPrint:
  {
    struct Row row;
    visitRow(_p_->u.rprint_.row_);
    POP (row);
    print_row (row.matrix, row.index);
    
    //TODO tex print
    break;
  }
  
  case is_AVar:
  {
    int iden = register_variable(_p_->u.avar_.ident_);
    visitExp(_p_->u.avar_.exp_);
    POP(type);
    POP(data);
    
    var = lookup_variable(iden);
    var->type = type;
    var->data = data;
    break;
  }
  
  case is_PMat:
  {
    int iden = register_variable(_p_->u.pmat_.ident_);
    visitListRow(_p_->u.pmat_.listrow_);
    struct Matrix *m;
    POP (m);
    
    var = lookup_variable(iden);
    var->type = MATR_T;
    var->data = (uint64_t) m;
    break;
  }
  
  {
  struct Row r1, r2;
  case is_RSwp: // Row1 <-> Row2
    visitRow(_p_->u.rswp_.row_1);
    visitRow(_p_->u.rswp_.row_2);
    POP (r2);
    POP (r1);
    swapRows(r1, r2);
    break;
  
  case is_RSet: // Row1 -> Row2
    visitRow(_p_->u.rset_.row_1);
    visitRow(_p_->u.rset_.row_2);
    POP (r2);
    POP (r1);
    if (r2.tmp) {
        printf ("Error: Cannot assign to a temporary matrix.\n");
        exit (-1);
    }
    row_copy(r2, r1);
    break;
  
  case is_RAss: // Row1 = Row2
    visitRow(_p_->u.rass_.row_1);
    visitRow(_p_->u.rass_.row_2);
    POP (r2);
    POP (r1);
    if (r1.tmp) {
        printf ("Error: Cannot assign to a temporary matrix.\n");
        exit (-1);
    }
    row_copy(r1, r2);
    break;
  }
  
  case is_Pause:
  {
    char line[256];
    printf ("Paused. Press enter to continue.\n");
    if (fgets(line, sizeof line, stdin) != NULL) {
        //continue
    } else {
        printf ("Error: input is too large.");
        exit(-1);
    }
  }
    break;
  
  case is_Ref:
    visitIdent(_p_->u.rref_.ident_);
    POP (type);
    POP (data);
    if (type != MATR_T)
        printf ("Error: Can only row reduce a matrix.\n");
    ref ((struct Matrix*) data);
    break;
  
  case is_Rref:
    visitIdent(_p_->u.rref_.ident_);
    POP (type);
    POP (data);
    if (type != MATR_T)
        printf ("Error: Can only row reduce a matrix.\n");
    rref ((struct Matrix*) data);
    break;
  
  case is_CDoub: //cast double
    visitIdent(_p_->u.cdoub_.ident_);
    POP (type);
    POP (data);
    if (type != MATR_T)
        printf ("Error: Can only cast a matrix. (for now)\n");
    cast_matrix ((struct Matrix*) data, DOUB_T);
    break;
    
  case is_CInt: //cast int
    visitIdent(_p_->u.cint_.ident_);
    POP (type);
    POP (data);
    if (type != MATR_T)
        printf ("Error: Can only cast a matrix. (for now)\n");
    cast_matrix ((struct Matrix*) data, INT_T);
    break;
  
  default:
    fprintf(stderr, "Error: bad kind field when interpreting Stm!\n");
    exit(1);
  }
}

/* Note: Be careful! At the moment there are two very different kinds of row formats that
 * I'm using. The PRow pushes all the row data onto the stack, while the other row labels
 * will push a "struct Row". I might end up choosing one row format over the other, but
 * in the meantime they will simply be incompatible (though the lexer doesn't recognize this)
 * A runtime error will probably occur if the two kinds of rows are mixed. */
void visitRow(Row _p_)
{
  struct Row row1; //matrix, index
  struct Row row2; //matrix, index
  struct Row tmp;  //matrix, index
  
  switch(_p_->kind) {
  case is_PRow:
    visitListExp(_p_->u.prow_.listexp_);
    break;
    
  case is_RAdd:
    visitRow(_p_->u.radd_.row_1);
    visitRow(_p_->u.radd_.row_2);
    POP (row2);
    POP (row1);
    tmp = addRows (row1, row2);
    PUSH (tmp);
    break;
    
  case is_RSub:
    visitRow(_p_->u.rsub_.row_1);
    visitRow(_p_->u.rsub_.row_2);
    POP (row2);
    POP (row1);
    tmp = subRows (row1, row2);
    PUSH (tmp);
    break;
  
  {
    uint32_t type;
    uint64_t data;
    
  case is_RMul: // k * R
    visitExp(_p_->u.rmul_.exp_);
    visitRow(_p_->u.rmul_.row_);
    POP (row1);
    POP (type);
    POP (data);
    tmp = mulRow (type, data, row1);
    PUSH (tmp);
    break;
  
  case is_RDiv: // R / k
    visitRow(_p_->u.rdiv_.row_);
    visitExp(_p_->u.rdiv_.exp_);
    POP (type);
    POP (data);
    POP (row1);
    tmp = divRow (type, data, row1);
    PUSH (tmp);
    break;
    
  case is_RMul2: // R * k
    visitRow(_p_->u.rmul_.row_);
    visitExp(_p_->u.rmul_.exp_);
    POP (type);
    POP (data);
    POP (row1);
    tmp = mulRow (type, data, row1);
    PUSH (tmp);
    break;
  
  }
  
  //Subscript Matrix
  case is_SMat:
  {
    uint32_t type;
    uint64_t data;
    char* name = _p_->u.smat_.ident_;
    struct Variable *v = lookup_variable(hash_variable(name));
    
    if (v->type != MATR_T) {
      printf("Expected a 2D Matrix to subscript.\n");
      exit(-1);
    }
    
    visitExp(_p_->u.smat_.exp_);
    POP (type);
    POP (data);
    
    if (type != INT_T) {
      printf("Expected an integer to subscript the matrix.\n");
      exit(-1);
    }
    
    struct Row row;
    row.matrix = (void*) v->data;
    row.index = data;
    row.tmp = 0;
    
    PUSH (row);
    break;
  }
  
  default:
    fprintf(stderr, "Error: bad kind field when interpreting Row!\n");
    exit(1);
  }
}

//Pushes the expressions in order, then the number of items pushed.
void visitListExp(ListExp listexp)
{
  uint32_t i;
  for (i = 0; listexp; i++) {
    visitExp(listexp->exp_);
    listexp = listexp->listexp_;
  }
  PUSH (i);
  if (i == 0) {
    printf ("Error: Cannot initialize a row of size 0.");
    exit (-1);
  }
}

void visitListRow(ListRow listrow)
{
  //Sentinel
  PUSH (int, 0xa110da7a);
  
  //64 bits is enough for a double or integer.
  uint64_t **matrix;
  int rows = 0;
  
  while(listrow) {
    // visit row is going to push information onto the stack
    //n          (row size)
    //64 bits    (row data)
    //...        (for n times)
    // Repeat row until sentinel,
    // where "a11 da7a" has been gotten.
    
    visitRow(listrow->row_);
    listrow = listrow->listrow_;
    rows++;
  }
  matrix = malloc(rows * sizeof(uint64_t*));
  
  // Row "length" is the number of matrix columns.
  uint32_t len;
  uint32_t len_;
  uint32_t type;
  uint32_t type_;
  uint64_t data;
  
  POP(len);
  PEEK(type);
  PUSH(len);
  
  for (int i = rows-1; i >= 0; i--) {
    POP (len_);
    if (len_ != len) {
      printf("Error: Inconsistent row length.\n");
      exit (-1);
    }
    matrix[i] = malloc(len * sizeof(uint64_t));
    
    for (int j = len-1; j >= 0; j--) {
      POP (type_);
      if (type_ != type) {
        printf("Error: Inconsistent type usage.\n");
        exit (-1);
      }
      POP (data);
      matrix[i][j] = data;
    }
  }
  
  /* I thought I would have actually needed this more. I decided 
   * to keep it because I thought the idea was cool. */
  POP(data);
  if (data != 0xa110da7a) {
    printf ("Warning: Stack might be corrupted.\n");
  }
  
  //Allocate on the heap so that data doesn't get deallocated. I want to make
  //sure this is correct, so test writing this a different way later.
  struct Matrix *mat = malloc(sizeof(struct Matrix));
  mat->data = matrix;
  mat->rows = rows;
  mat->cols = len;
  mat->type = type;
  PUSH(mat);
}

void visitExp(Exp _p_)
{
  double d;
  
  //Deal with atomic elements first
  switch(_p_->kind) {
  
  /*
  case is_EInt:
    visitInteger(_p_->u.eint_.integer_);
    return;
  //*/
  case is_ESInt:
    visitSInteger(_p_->u.esint_.sinteger_);
    return;
  case is_EDob:
    visitDouble(_p_->u.edob_.double_);
    return;
  case is_EIden:
    visitIdent(_p_->u.eiden_.ident_);
    return;
  case is_ConstE:
    d = 2.718281828459045235360287471352662497757247093699959574966;
    PUSH (double, d);
    PUSH (uint32_t, DOUB_T);
    return;
  case is_ConstPI:
    d = 3.141592653589793238462643383279502884197169399375105820974;
    PUSH (double, d);
    PUSH (uint32_t, DOUB_T);
    return;
  default:;
  }
  
  //uint64_t works to store doubles, but not to add them
  //(at least against ints)
  double d1, d2;
  uint32_t type1;
  uint64_t data1;
  uint32_t type2;
  uint64_t data2;
  
  #define POP_FOR(op)                  \
    visitExp(_p_->u.e##op##_.exp_1);   \
    visitExp(_p_->u.e##op##_.exp_2);   \
    POP(type2); POP(data2);            \
    POP(type1); POP(data1);
  
  #define DO_OP(op)                             \
    if (type1 == DOUB_T || type2 == DOUB_T) {   \
                                                \
      if (type1 == DOUB_T)                      \
        d1 = toDouble(data1);                   \
      else d1 = data1;                          \
                                                \
      if (type2 == DOUB_T)                      \
        d2 = toDouble(data2);                   \
      else d2 = data2;                          \
                                                \
      double result = d1 op d2;                 \
      PUSH (double, result);                    \
      PUSH (uint32_t, DOUB_T);                  \
    } else {                                    \
      PUSH (uint64_t, data1 op data2);          \
      PUSH (uint32_t, INT_T);                   \
    }
    
  switch(_p_->kind) {
  case is_EAdd:
    POP_FOR(add);
    DO_OP(+);
    break;
  case is_ESub:
    POP_FOR(sub);
    DO_OP(-);
    break;
  case is_EMul:
    POP_FOR(mul);
    DO_OP(*);
    break;
  case is_EDiv:
    POP_FOR(div);
    DO_OP(/);
    break;
    
  default:
    fprintf(stderr, "Error: bad kind field when interpreting Exp!\n");
    exit(1);
  }
  #undef POP_FOR
  #undef DO_OP
}

/* Here are some of the base expressions. They push type information so that
 * the caller knows how to handle the data. */

//Visiting an identifier returns the data stored and the associated type,
//NOT anything to do with the variable itself.
void visitIdent(Ident i)
{
  //if unknown identifier, will likely push type as IDEN_T
  //PUSH (uint64_t, hash_variable(i));
  //PUSH (uint32_t, IDEN_T);
  int hash = hash_variable(i);
  if (hash == -1) {
    printf ("Error: Variable \"%s\" is not defined.\n", i);
    exit (-1);
  }
  struct Variable *v = lookup_variable(hash);
  PUSH (uint64_t, v->data);
  PUSH (uint32_t, v->type);
}

//Note: strtol might be better to use than atoi
void visitSInteger(SInteger p)
{
  int i = atoi(p);
  visitInteger(i);
}

void visitInteger(Integer i)
{
  PUSH (uint64_t, i);
  PUSH (uint32_t, INT_T);
}

void visitDouble(Double d)
{
  PUSH (double, d);
  PUSH (uint32_t, DOUB_T);
}

//Unused in expressions
void visitChar(UNUSED Char c) {}
void visitString(UNUSED String s) {}

