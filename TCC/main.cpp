#include <windows.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

static int allModel = -320, hip = -30, knee = 45, foot = -65;
void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

void drawCylinder(float base,float top,float altura) {

  GLUquadricObj* p = gluNewQuadric();
  gluQuadricDrawStyle(p, GLU_FILL);
  glColor3f(1.0, 1.0, 1.0);
  glRotatef(90, 1.0, 0.0, 0.0);
  gluCylinder(p, base, top, altura, 10, 10);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();  
  glRotatef((GLfloat)allModel, 0.0, 1.0, 0.0);

    glPushMatrix();
      glRotatef(-90, 0.0, 0.0, 1.0);
      glTranslatef(0.0, 0.3, 0.0);
      glColor3f(0.0, 0.0, 1.0);
      glScalef(0.2, 0.6, 0.2);
      glutSolidCube(1.0);
      glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();

    /*Bone Central*/
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0);
      glScalef(0.2, 1.0, 0.2);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glRotatef(-90, 0.0, 0.0, 1.0);
      glTranslatef(0.0, -0.3, 0.0);
      glColor3f(0.0, 0.0, 1.0);
      glScalef(0.2, 0.6, 0.2);
      glutSolidCube(1.0);
      glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();
    glPushMatrix();
      glColor3f(1.0, 0.0, 0.0);
      glutWireSphere(0.10, 25, 25);
      glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();
    
    /*PERNA ESQUERDA*/
    glPushMatrix();
      glTranslatef(0.6, -0.5, 0.0);
      
      glRotatef(-90, 0.0, 0.0, 1.0);
      glTranslatef(-0.5, 0.0, 0.0);

      glRotatef((GLfloat)hip, 0.0, 1.0, 0.0);
      glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glutWireSphere(0.20, 25, 25);
        glColor3f(1.0, 1.0, 1.0);
      glPopMatrix();
      glTranslatef(0.5, 0.0, 0.0);
      glPushMatrix();
        glScalef(1.0, 0.2, 0.2);
        glutSolidCube(1.0);
      glPopMatrix();
   
      glTranslatef(0.5, 0.0, 0.0);
      glPushMatrix();
        glColor3f(1.0,0.0,0.0);
        glutWireSphere(0.20,25,25);
        glColor3f(1.0, 1.0, 1.0);
      glPopMatrix();
      glTranslatef(-0.5, 0.0, 0.0);
    
      glTranslatef(0.5, 0.0, 0.0);
      glRotatef((GLfloat)knee, 0.0, 1.0, 0.0);
      glTranslatef(0.5, 0.0, 0.0);
    
      glPushMatrix();
        glScalef(1.0, 0.2, 0.2);
        glutSolidCube(1.0);
      glPopMatrix();

      glTranslatef(0.5, 0.0, 0.0);
      glPushMatrix();
        glColor3f(0.5, 0.0, 0.0);
        glutWireSphere(0.15, 25, 25);
        glColor3f(1.0, 1.0, 1.0);
      glPopMatrix();
      glTranslatef(-0.5, 0.0, 0.0);

      glTranslatef(0.5, 0.0, 0.0);
      glRotatef((GLfloat)foot, 0.0, 1.0, 0.0);

      glTranslatef(0.25, 0.0, 0.0);

      glPushMatrix();
        glScalef(0.5, 0.2, 0.08);
        glutSolidCube(1.0);
      glPopMatrix();
    glPopMatrix();

    /*PERNA DIREITA*/
    glPushMatrix();
      glTranslatef(-0.6, -0.5, 0.0);
        glRotatef(-90, 0.0, 0.0, 1.0);
        glTranslatef(-0.5, 0.0, 0.0);
        glRotatef((GLfloat)hip, 0.0, 1.0, 0.0);
      glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glutWireSphere(0.20, 25, 25);
        glColor3f(1.0, 1.0, 1.0);
      glPopMatrix();

      glTranslatef(0.5, 0.0, 0.0);
      glPushMatrix();
        glScalef(1.0, 0.2, 0.2);
        glutSolidCube(1.0);
      glPopMatrix();

      glTranslatef(0.5, 0.0, 0.0);
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glutWireSphere(0.20, 25, 25);
        glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();
      glTranslatef(-0.5, 0.0, 0.0);

      glTranslatef(0.5, 0.0, 0.0);
      glRotatef((GLfloat)knee, 0.0, 1.0, 0.0);
      glTranslatef(0.5, 0.0, 0.0);

      glPushMatrix();
        glScalef(1.0, 0.2, 0.2);
        glutSolidCube(1.0);
      glPopMatrix();

      glTranslatef(0.5, 0.0, 0.0);
      glPushMatrix();
        glColor3f(0.5, 0.0, 0.0);
        glutWireSphere(0.15, 25, 25);
        glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();
      glTranslatef(-0.5, 0.0, 0.0);

      glTranslatef(0.5, 0.0, 0.0);
      glRotatef((GLfloat)foot, 0.0, 1.0, 0.0);
      glTranslatef(0.25, 0.0, 0.0);

      glPushMatrix();
        glScalef(0.5, 0.2, 0.08);
        glutSolidCube(1.0);
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

  glutSwapBuffers();
}
void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -5.0);
}
void keyboard(unsigned char key, int x, int y)
{

  cout << "allModel: " << allModel << endl;
  cout << "knee: " << knee << endl;
  cout << "hip: " << hip << endl;
  cout << "foot: " << foot << endl;
  cout << "============" << endl;


  switch (key) {
  case 's': /* s key rotates at hip */
    hip = (hip + 1) % 360;
    glutPostRedisplay();
    break;
  case 'S':
    hip = (hip - 1) % 360;
    glutPostRedisplay();
    break;
  case 'e': /* e key rotates at knee */
    knee = (knee + 1) % 360;
    glutPostRedisplay();
    break;
  case 'E':
    knee = (knee - 1) % 360;
    glutPostRedisplay();
    break;
  case 'f':
    foot = (foot + 1) % 360;
    glutPostRedisplay();
    break;
  case 'F':
    foot = (foot - 1) % 360;
    glutPostRedisplay();
    break;
  case 'z':
    allModel = (allModel + 1) % 360;
    glutPostRedisplay();
    break;
  case 'Z':
    allModel = (allModel - 1) % 360;
    glutPostRedisplay();
    break;
  default:
    break;
  }
}
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1024, 824);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
  return 0;
}