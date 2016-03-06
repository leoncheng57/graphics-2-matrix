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

  //begin testing  
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

  //display(s);
  save_extension(s, "lines.png");
  //end testing

  
  //now for the cool
  clear_screen(s);

  edges = new_matrix(4, 1);
  add_edge(edges, 0, 0, 0, 20, 20, 0);  
  //draw_lines(edges, s, c);


  
  double n;
  for (n = 20; n>0; n--){
    c.red = rand() % MAX_COLOR;
    c.blue = rand() % MAX_COLOR;
    c.green = rand() % MAX_COLOR;
    double angle,x, y;
    x = rand()%500;
    y = rand()%500;
    angle = 0;
    for (angle=0;angle<360;angle+=1){
      transform = make_rotZ(angle);
      matrix_mult(transform, edges);
      //draw_lines(edges, s, c);
      transform = make_translate(x, y, 0);
      matrix_mult(transform, edges);
      draw_lines(edges, s, c);
      transform = make_translate(-1*x, -1*y, 0);
      matrix_mult(transform, edges);
      //draw_lines(edges, s, c);
    }
  }
  
  display(s);
  save_extension(s, "cool.png");
  //end cool

  free_matrix( transform );
  free_matrix( edges );


}
