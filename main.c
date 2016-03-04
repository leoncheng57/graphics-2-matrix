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
  color c;

  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;

  clear_screen(s);

  struct matrix *edges;
  struct matrix *transform;

  //testing

  edges = new_matrix(4, 4);
  add_edge(edges, 1, 1, 1, 200, 200, 200);
  add_edge(edges, 2, 2, 2, 300, 300, 300);
  add_edge(edges, 3, 3, 3, 400, 400, 400);
  // ident(edges);
  // scalar_mult(9, edges);
  print_matrix(edges);

  draw_lines(edges, s, c);

  transform = make_rotZ(30);
  // print_matrix(transform);


  // matrix_mult(transform, edges);
  // print_matrix(edges);
  //end testing

  free_matrix( transform );
  free_matrix( edges );

  display(s);
  save_extension(s, "lines.png");

}
