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

  clear_screen(s);

  //testing  
  struct matrix *edges;
  struct matrix *transform;

  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;

  edges = new_matrix(4, 4);
  add_edge(edges, 100, 100, 100, 200, 200, 200);
  print_matrix(edges);
  draw_lines(edges, s, c);

  c.blue = MAX_COLOR;
  transform = make_translate(200, 200, 0);
  print_matrix(transform);
  matrix_mult(transform, edges);
  print_matrix(edges);

  draw_lines(edges, s, c);


  //end testing

  free_matrix( transform );
  free_matrix( edges );

  display(s);
  save_extension(s, "lines.png");

}
