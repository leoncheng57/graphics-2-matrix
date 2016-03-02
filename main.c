#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
// #include "parser.h"

int main() {

  screen s;
  struct matrix *edges;
  struct matrix *transform;

  //testing
  edges = new_matrix(4, 4);
  // ident(edges);
  // scalar_mult(9, edges);
  print_matrix(edges);

  transform = make_rotZ(30);
  // print_matrix(transform);


  // matrix_mult(transform, edges);
  // print_matrix(edges);
  //end testing

  free_matrix( transform );
  free_matrix( edges );
}
