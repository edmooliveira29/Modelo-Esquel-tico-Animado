#include "../headers/Display2.h"
#include <GL/glut.h>

void Display2::display2()
{
  Display2::getParams();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_LINE_STRIP);
  glVertex2f(0.0f, 0.0f);
  for (float x = 1.0f; x < 100.0f; x += 1.0f)
    glVertex2f(x, x);
  glVertex2f(100.0f, 0.0f);
  glEnd();  glutSwapBuffers();
}
