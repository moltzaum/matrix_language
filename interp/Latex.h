#include <stdio.h>
#include "Matrix.h"
#include "types.h"

FILE *tex_file;
bool out_tex;

void dataTex (uint64_t data, uint32_t type);

void matrixTex (struct Matrix* m);