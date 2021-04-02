#pragma warning(disable : 4005)
#include <windows.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glaux.h>
using namespace std;

#if !defined(GLUT_WHEEL_UP)
#  define GLUT_WHEEL_UP    3
#  define GLUT_WHEEL_DOWN  4

#endif
static int allModel = 0,
hip = -30,
knee = 45,
foot = -65;

GLfloat angle, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ;


void init(void)
{
  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);
  //Habilita o uso de iluminação
  glEnable(GL_LIGHTING);
  // Habilita a luz de número 0
  glEnable(GL_LIGHT0);
  // Habilita o depth-buffering
  glEnable(GL_DEPTH_TEST);

  // Habilita o modelo de colorização de Gouraud
  glShadeModel(GL_SMOOTH);

  // Inicializa a variável que especifica o ângulo da projeção
  // perspectiva
  angle = 10;

  // Inicializa as variáveis usadas para alterar a posição do 
  // observador virtual
  rotX = 30;
  rotY = 0;
  obsZ = 180;
}

void drawCylinder(float base,float top,float altura) {

  GLUquadricObj* p = gluNewQuadric();
  gluQuadricDrawStyle(p, GLU_FILL);
  glColor3f(1.0, 1.0, 1.0);
  glRotatef(90, 1.0, 0.0, 0.0);
  gluCylinder(p, base, top, altura, 10, 10);
}

void DefineIluminacao(void)
{
  GLfloat luzAmbiente[4] = { 0.2,0.2,0.2,1.0 };
  GLfloat luzDifusa[4] = { 0.7,0.7,0.7,1.0 };          // "cor" 
  GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };// "brilho" 
  GLfloat posicaoLuz[4] = { 10.0, 0.0, 2.0, 2.0 };

  // Capacidade de brilho do material
  GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
  GLint especMaterial = 60;

  // Define a refletância do material 
  //glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
  // Define a concentração do brilho
  //glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

  // Ativa o uso da luz ambiente 
  //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

  // Define os parâmetros da luz de número 0
  //glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
  //glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
  glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

void PosicionaObservador(void)
{
  // Especifica sistema de coordenadas do modelo
  glMatrixMode(GL_MODELVIEW);
  // Inicializa sistema de coordenadas do modelo
  glLoadIdentity();
  DefineIluminacao();
  // Especifica posição do observador e do alvo
  glTranslatef(0, 0, -obsZ);
  glRotatef(rotX, 1, 0, 0);
  glRotatef(rotY, 0, 1, 0);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
  // Especifica sistema de coordenadas de projeção
  glMatrixMode(GL_PROJECTION);
  // Inicializa sistema de coordenadas de projeção
  glLoadIdentity();

  // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
  gluPerspective(angle, fAspect, 0.5, 500);

  PosicionaObservador();
}


// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
  // Para previnir uma divisão por zero
  if (h == 0) h = 1;

  // Especifica as dimensões da viewport
  glViewport(0, 0, w, h);

  // Calcula a correção de aspecto
  fAspect = (GLfloat)w / (GLfloat)h;

  EspecificaParametrosVisualizacao();
}


void GerenciaMouse(int button, int state, int x, int y){
  cout << "button: " << button << endl;
  cout << "state: " << state << endl;

  if (button == 3)
    if (state == GLUT_UP) {
      // Zoom-in

      if (angle > 1) {

        angle -= 1;
      }else {
        angle = 1;
      }
    }

  if (button == 4)
    if (state == GLUT_UP) {
      // Zoom-out
      if (angle <= 130)
        angle += 1;
    }
  EspecificaParametrosVisualizacao();
  glutPostRedisplay();
}

void display(void)
{
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  DefineIluminacao();
  //glBegin(GL_QUADS);
  //// Face frontal
  //glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
  //glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
  //glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
  //glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
  //// Face posterior
  //glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  //glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
  //glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
  //glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
  //// Face superior
  //glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
  //glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
  //glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
  //glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
  //// Face inferior
  //glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  //glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
  //glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
  //glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
  //// Face lateral direita
  //glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
  //glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
  //glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
  //glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
  //// Face lateral esquerda
  //glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  //glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
  //glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
  //glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
  //glEnd();


  glColor3f(0.85, 0.63, 0.50);
  glPushMatrix();  
  glPushMatrix();
  glColor3f(0.8,0.8,0.8);
    glRotatef(45, 0.0, 1.0, 0.0);
    glTranslatef(0.0, -2.1, 0.0);
    glScalef(5.0, 0.01, 5.0);
    glutSolidCube(2.0);
  glPopMatrix();
  glColor3f(0.85, 0.63, 0.50);
  glRotatef(30, 0.0, 1.0, 0.0);

    glRotatef((GLfloat)allModel, 0.0, 1.0, 0.0);

    /*Bone Central*/
    glPushMatrix();
      glTranslatef(0.0, 0.5, 0.0);
      glScalef(0.2, 1.0, 0.2);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glRotatef(-90, 0.0, 0.0, 1.0);
      glTranslatef(0.0, 0.3, 0.0);
      glScalef(0.4, 0.6, 0.4);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glRotatef(-90, 0.0, 0.0, 1.0);
      glTranslatef(0.0, -0.3, 0.0);
      glScalef(0.4, 0.6, 0.4);
      glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
      glutWireSphere(0.10, 25, 25);
    glPopMatrix();
    
    /*PERNA ESQUERDA*/
    glPushMatrix();
      glTranslatef(0.6, -0.5, 0.0);
      
      glRotatef(-90, 0.0, 0.0, 1.0);
      glTranslatef(-0.5, 0.0, 0.0);

      glRotatef((GLfloat)hip, 0.0, 1.0, 0.0);
      glPushMatrix();
        glutSolidSphere(0.22, 25, 25);
      glPopMatrix();
      glTranslatef(0.5, 0.0, 0.0);
      glPushMatrix();
        glScalef(1.0, 0.3, 0.3);
        glutSolidCube(1.0);
      glPopMatrix();
   
      glTranslatef(0.5, 0.0, 0.0);
      glPushMatrix();
        glutSolidSphere(0.22, 25, 25);
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
        glutSolidSphere(0.13, 25, 25);
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
      glutSolidSphere(0.23, 25, 25);
      glPopMatrix();

      glTranslatef(0.5, 0.0, 0.0);
      glPushMatrix();
        glScalef(1.0, 0.3, 0.3);
        glutSolidCube(1.0);
      glPopMatrix();

      glTranslatef(0.5, 0.0, 0.0);
        glPushMatrix();
        glutSolidSphere(0.22, 25, 25);
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
        glutSolidSphere(0.13, 25, 25);
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

void keyboard(unsigned char key, int x, int y){

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
void TeclasEspeciais(int tecla, int x, int y)
{
  switch (tecla)
  {
  case GLUT_KEY_LEFT:	rotY--;
    break;
  case GLUT_KEY_RIGHT:rotY++;
    break;
  case GLUT_KEY_UP:	rotX++;
    break;
  case GLUT_KEY_DOWN:	rotX--;
    break;
  case GLUT_KEY_HOME:	obsZ++;
    break;
  case GLUT_KEY_END:	obsZ--;
    break;
  }
  PosicionaObservador();
  glutPostRedisplay();
}


int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1024, 824);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(AlteraTamanhoJanela);
  glutSpecialFunc(TeclasEspeciais);

  glutKeyboardFunc(keyboard);
  
  glutMouseFunc(GerenciaMouse);

  init();
  glutMainLoop();
  return 0;
}