#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols
Returns:

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)...
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m
Returns:

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols
Returns:

Reallocates the memory for m->m such that it now has
newcols number of columns
====================*/
void grow_matrix(struct matrix *m, int newcols) {

  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m
Returns:

print the matrix
*/
void print_matrix(struct matrix *m) {
  int r = m->rows;
  int c = m->cols;
  int i=0;
  int j=0;
  for(i=0; i<r; i++){
    for(j=0; j<c; j++){
      printf("%f ", m->m[i][j] );
    }
    printf("\n");
  }
  printf("\n");
  //extra space at the end to separate if two matrices
  //are printed back to back in the terminal
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns:

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int i, j;
  for (i=0;i<m->rows;i++){
    for (j=0; j<m->cols;j++){
      if (i==j)
        m->m[i][j] = 1;
    }
  }
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m
Returns:

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
  int i, j;
  for (i=0;i<m->rows;i++){
    for (j=0; j<m->cols;j++){
      m->m[i][j] = x * m->m[i][j];
    }
  }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b
Returns:

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  struct matrix * result;
  result = new_matrix(a->cols, b->rows);

  int h, i, j;
  for (h=0;h < a->rows;h++){
    double * row = a->m[h];

    for (i=0;i<b->rows;i++){
      double sum = 0; //sum of row*col
      for (j=0; j<b->cols;j++){
        // printf("row[%d]: %f \n", j, row[j]);
        // printf("b->m[%d][%d]: %f \n", i, j, b->m[i][j]);
        // printf("row[j] * b->m[i][j]: %f\n", row[j] * b->m[i][j]);
        sum += row[j] * b->m[i][j];
      }
      //one complete col
      result->m[h][i] = sum;
      // printf("sum=m[%d][%d]=%f\n", h, i, sum );
      // printf("\n");
    }
  }
  //Copy result matrix to b
  for(i=0; i<b->rows; i++){
    for(j=0; j<b->cols; j++){
      b->m[i][j] = result->m[i][j];
    }
  }
}



/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b
Returns:

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++)
    for (c=0; c < a->cols; c++)
      b->m[r][c] = a->m[r][c];
}

/*======== struct matrix * make_translate() ==========
Inputs:  int x
         int y
         int z
Returns: The translation matrix created using x, y and z
as the translation offsets.
====================*/
struct matrix * make_translate(double x, double y, double z) {
  struct matrix * result = new_matrix(4, 4);
  ident(result);
  result->m[0][3] = x;
  result->m[1][3] = y;
  result->m[2][3] = z;
  return result;
}

/*======== struct matrix * make_scale() ==========
Inputs:  int x
         int y
         int z
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix * make_scale(double x, double y, double z) {
  struct matrix * result = new_matrix(4, 4);
  result->m[0][0] = x;
  result->m[1][1] = y;
  result->m[2][2] = z;
  result->m[3][3] = 1;
  return result;
}

/*======== struct matrix * make_rotX() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the
angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
  struct matrix * result = new_matrix(4, 4);
  theta = theta * M_PI/180; //converting from deg to rad
  result->m[0][0] = 1;
  result->m[1][1] = cos(theta);
  result->m[2][1] = sin(theta);
  result->m[1][2] = -sin(theta);
  result->m[2][2] = cos(theta);
  result->m[3][3] = 1;
  return result;
}

/*======== struct matrix * make_rotY() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix * make_rotY(double theta) {
  struct matrix * result = new_matrix(4, 4);
  theta = theta * M_PI/180; //converting from deg to rad
  result->m[0][0] = cos(theta);
  result->m[0][2] = -sin(theta);
  result->m[1][1] = 1;
  result->m[2][0] = sin(theta);
  result->m[2][2] = cos(theta);
  result->m[3][3] = 1;
  return result;
}

/*======== struct matrix * make_rotZ() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix * make_rotZ(double theta) {
  struct matrix * result = new_matrix(4, 4);
  theta = theta * M_PI/180; //converting from deg to rad
  result->m[0][0] = cos(theta);
  result->m[0][1] = -sin(theta);
  result->m[1][0] = sin(theta);
  result->m[1][1] = cos(theta);
  result->m[2][2] = 1;
  result->m[3][3] = 1;
  return result;
}
