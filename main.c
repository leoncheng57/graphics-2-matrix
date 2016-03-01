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

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

  //testing
  ident(edges);
  scalar_mult(9, edges);
  print_matrix(edges);

  ident(transform);
  print_matrix(transform);

  matrix_mult(edges, transform);
  print_matrix(transform);



  free_matrix( transform );
  free_matrix( edges );
}
