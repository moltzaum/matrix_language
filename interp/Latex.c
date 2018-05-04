#include "Latex.h"

void dataTex (uint64_t data, uint32_t type) {
  switch (type) {
  case INT_T:
    fprintf (tex_file, "%d ", (int) data);
    break;
  case DOUB_T:
    fprintf (tex_file, "%f ", toDouble(data));
    break;
  case MATR_T:
    matrixTex ((struct Matrix*) data);
    break;
  case ROW_T:
    //Not accessible
  default:
    printf ("? ");
  }
}

void matrixTex (struct Matrix* m) {
    
    if (tex_file == NULL) {
        printf ("Cannot write to tex file. It hasn't been opened yet.\n");
        return;
    }
    
    fprintf (tex_file, "\\[ \n\\begin{bmatrix} \n");
    
    int cols = m->cols - 1;
    
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < cols; j++) {
            dataTex(m->data[i][j], m->type);
            fprintf (tex_file, " & ");
        }
        dataTex(m->data[i][cols], m->type);
        fprintf (tex_file, "\\\\\n");
    }
    
    fprintf (tex_file, "\\end{bmatrix} \n \\]\n");
}