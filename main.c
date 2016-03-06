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
  add_edge(edges, 100, 100, 100, 200, 200, 200); //first line
  draw_lines(edges, s, c);

  c.blue = MAX_COLOR;
  transform = make_translate(200, 200, 0); //transform
  matrix_mult(transform, edges);
  draw_lines(edges, s, c);

  c.red = MAX_COLOR;
  c.blue = 0;
  scalar_mult(0.5, edges); //scaling
  draw_lines(edges, s, c);

  c.green = 0;
  c.blue = 0;
  transform = make_scale(0.25, 1, 1);
  matrix_mult(transform, edges);
  draw_lines(edges, s, c);
  
  c.green = MAX_COLOR;
  c.blue = MAX_COLOR;
  transform = make_rotZ(-20);
  matrix_mult(transform, edges);
  draw_lines(edges, s, c);

  //end testing

  free_matrix( transform );
  free_matrix( edges );

  display(s);
  save_extension(s, "lines.png");

}
