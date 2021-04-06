#pragma warning(disable : 4005)
#include <windows.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glaux.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#if !defined(GLUT_WHEEL_UP)
#  define GLUT_WHEEL_UP    3
#  define GLUT_WHEEL_DOWN  4

#endif
static int allModel = 0,
hipLeft = -30,
kneeLeft = 45,
footLeft = -65,
footRight = -65,
kneeRight = 45,
hipRight = -30;

GLfloat angle, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ;
GLfloat matrix[3593][6];


void init(void)
{
  // Habilita a defini��o da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);

  //Habilita o uso de ilumina��o
  glEnable(GL_LIGHTING);

  // Habilita a luz de n�mero 0
  glEnable(GL_LIGHT0);
  // Habilita o depth-buffering
  glEnable(GL_DEPTH_TEST);

  // Habilita o modelo de coloriza��o de Gouraud
  glShadeModel(GL_SMOOTH);

  // Inicializa a vari�vel que especifica o �ngulo da proje��o
  // perspectiva
  angle = 10;

  // Inicializa as vari�veis usadas para alterar a posi��o do 
  // observador virtual
  rotX = 30;
  rotY = 0;
  obsZ = 180;
}


void readCsv() {
  ifstream myFile;
  myFile.open("G:\\Meu Drive\\UFOP\\TCC\\Parte 2\\Banco de Dados\\angle_1_person.csv");
  int i = 0, j =0;
  float line[6] = {};
  while (myFile.good()) {
    
    if (i < 6) {
      string value;
      getline(myFile, value, ',');
      float temp = stod(value);
      //cout << "temp: " << temp << endl;
      line[i] = (temp*180)/(3.14);

      //cout << "i: " << i << endl;
      i++;
    }else {
      for (int i = 0; i < 6; i++) {
        matrix[j][i] = line[i];
        //cout << "matrix[" << j << "][" << i << "]: " << matrix[j][i] << endl;
      }
      //cout << "matrix["<<j<<"]: " << *matrix[j] << endl;

      i = 0;
      j++;
    }
    cout << "." << endl;
  }
  cout << "Arquivo carregado com sucesso!" << endl;
  system("pause");
}




void drawCylinder(float base, float top, float altura) {

  GLUquadricObj* p = gluNewQuadric();
  gluQuadricDrawStyle(p, GLU_FILL);
  glColor3f(1.0, 1.0, 1.0);
  glRotatef(90, 1.0, 0.0, 0.0);
  gluCylinder(p, base, top, altura, 10, 10);
}

void lighting(void)
{
  GLfloat luzAmbiente[4] = { 0.3,0.3,0.3,1.0};
  GLfloat luzDifusa[4] = { 1.0,1.0,1.0, 1.0 };
  GLfloat posicaoLuzDifusa[4] = { 300.0, 300.0, -120.0, 0.0 };
  GLint especMaterial = 20;

  // Define a concentra��o do brilho
  //glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

// Define os par�metros da Luz n�mero Zero
  glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
  glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuzDifusa);
  glEnable(GL_LIGHT0);

}

void PosicionaObservador(void)
{
  // Especifica sistema de coordenadas do modelo
  glMatrixMode(GL_MODELVIEW);
  // Inicializa sistema de coordenadas do modelo
  glLoadIdentity();
  lighting();
  // Especifica posi��o do observador e do alvo
  glTranslatef(0, 0, -obsZ);
  glRotatef(rotX, 1, 0, 0);
  glRotatef(rotY, 0, 1, 0);

}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
  // Especifica sistema de coordenadas de proje��o
  glMatrixMode(GL_PROJECTION);
  // Inicializa sistema de coordenadas de proje��o
  glLoadIdentity();

  // Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
  gluPerspective(angle, fAspect, 0.5, 500);

  PosicionaObservador();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
  // Para previnir uma divis�o por zero
  if (h == 0) h = 1;

  // Especifica as dimens�es da viewport
  glViewport(0, 0, w, h);

  // Calcula a corre��o de aspecto
  fAspect = (GLfloat)w / (GLfloat)h;

  EspecificaParametrosVisualizacao();
}

void GerenciaMouse(int button, int state, int x, int y) {
  if (button == 3)
    if (state == GLUT_UP) {
      // Zoom-in
      if (angle > 1) {

        angle -= 1;
      }
      else {
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

  lighting();
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
  glColor3f(0.8, 0.8, 0.8);
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

  glRotatef((GLfloat)hipLeft, 0.0, 1.0, 0.0);
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
  glRotatef((GLfloat)kneeLeft, 0.0, 1.0, 0.0);
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
  glRotatef(matrix[1][3], 0.0, 1.0, 0.0);

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
  glRotatef((GLfloat)hipRight, 0.0, 1.0, 0.0);
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
  glRotatef((GLfloat)kneeRight, 0.0, 1.0, 0.0);
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
  glRotatef((GLfloat)footRight, 0.0, 1.0, 0.0);
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

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case '1':
      allModel = (allModel + 1) % 360;
      glutPostRedisplay();
      break;
    case '2':
      allModel = (allModel - 1) % 360;
      glutPostRedisplay();
      break;
    /*PERNA ESQUERDA*/
    case 'q': /* s key rotates at hipLeft */
      hipLeft = (hipLeft + 1) % 360;
      glutPostRedisplay();
      break;
    case 'Q':
      hipLeft = (hipLeft - 1) % 360;
      glutPostRedisplay();
      break;
    case 'a': /* e key rotates at kneeLeft */
      kneeLeft = (kneeLeft + 1) % 360;
      glutPostRedisplay();
      break;
    case 'A':
      kneeLeft = (kneeLeft - 1) % 360;
      glutPostRedisplay();
      break;
    case 'z':
      footLeft = (footLeft + 1) % 360;
      glutPostRedisplay();
      break;
    case 'Z':
      footLeft = (footLeft - 1) % 360;
      glutPostRedisplay();
      break;

     /*PERNA DIREITA*/
    case 'w': /* s key rotates at hipLeft */
      hipRight = (hipRight + 1) % 360;
      glutPostRedisplay();
      break;
    case 'W':
      hipRight = (hipRight - 1) % 360;
      glutPostRedisplay();
      break;
    case 's': /* e key rotates at kneeLeft */
      kneeRight = (kneeRight + 1) % 360;
      glutPostRedisplay();
      break;
    case 'S':
      kneeRight = (kneeRight - 1) % 360;
      glutPostRedisplay();
      break;
    case 'x':
      footRight = (footRight + 1) % 360;
      glutPostRedisplay();
      break;
    case 'X':
      footRight = (footRight - 1) % 360;
      glutPostRedisplay();
      break;
    default:
      break;
  }

}

void TeclasEspeciais(int tecla, int x, int y){
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
  readCsv();
  glutInit(&argc, argv);
  /*glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1024, 824);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);

  glutDisplayFunc(display);

  glutReshapeFunc(AlteraTamanhoJanela);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(TeclasEspeciais);

  glutMouseFunc(GerenciaMouse);

  init();
  glutMainLoop();*/
  return 0;
}