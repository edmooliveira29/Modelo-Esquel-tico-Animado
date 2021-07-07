#pragma warning(disable : 4005)
#ifdef WIN32
#include <windows.h>
#endif
# define FNULL 0L
void (*display2) (void) = FNULL;
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
#include <sstream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <string>
#include "../headers/Display2.h"

using namespace std;

#if !defined(GLUT_WHEEL_UP)
#  define GLUT_WHEEL_UP    3
#  define GLUT_WHEEL_DOWN  4
#endif

static int allModel = 0,
hipLeft,
kneeLeft,
footLeft,
footRight,
kneeRight,
hipRight;
static int width;
static int height;

GLfloat angle, angleGraphic, xScaleGraphic, yScaleGraphic, xTranslateChart, yTranslateChart, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ, obsZChart;
GLfloat matrix[3518][6];

int i = 1, frameAux, lineDivX;
boolean play, reset, pause;
boolean flagHipLeft = false;
boolean flagKneeLeft = false;
boolean flagFootLeft = false;
boolean flagHipRight = false;
boolean flagKneeRight = false;
boolean flagFootRight = false;
int flag = false;

int axisYhipLeft[21540];
int axisYkneeLeft[21540];
int axisYfootLeft[21540];
int axisYhipRight[21540];
int axisYkneeRight[21540];
int axisYfootRight[21540];

void ParametrosIniciais(void) {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);

  //Habilita o uso de iluminação
  glEnable(GL_LIGHTING);

  // Habilita a luz de número 0
  glEnable(GL_LIGHT0);
  // Habilita o depth-buffering
  glEnable(GL_DEPTH_TEST);
  angle = 5;
  angleGraphic = 160;
  rotX = 30;
  rotY = 180;
  obsZ = 100;
  obsZChart = 260;
  xScaleGraphic = 1;
  yScaleGraphic = 2;
  xTranslateChart = 0;
  yTranslateChart = 0;
}

void readCsv() {
  ifstream myFile;
  myFile.open("G:\\Meu Drive\\UFOP\\TCC\\Parte 2\\Banco de Dados\\angle_1_person.csv");
  int i = 0, j = 0,h=0;

  while (myFile.good()) {
    string line, intermediate;
    GLfloat frame[6] = {};
    int temp = 1;
    getline(myFile, line, '\n');
    vector <string> tokens;
    stringstream check(line);

    if (j > 20 && j <3519) {
        while (getline(check, intermediate, ',')) {
            double numberIntermediate = stof(intermediate);
            frame[i] = (GLfloat)(numberIntermediate)-180;
            i++;
        }
        i = 0;
        h++;
        cout << "frame: " << h << endl;

        for (int i = 0; i < 6; i++) {
            matrix[h][i] = frame[i];
            //cout << matrix[h][i] << endl;
        }
        //Sleep(1000);
    }

    //Sleep(500);

    j++;
  }
  cout << "Arquivo carregado com sucesso!\n==============================\n\n" << endl;
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
  GLfloat luzAmbiente[4] = { (GLfloat)0.3,(GLfloat)0.3,(GLfloat)0.3,(GLfloat)1.0 };
  GLfloat luzDifusa[4] = { 1.0,1.0,1.0, 1.0 };
  GLfloat posicaoLuzDifusa[4] = { 300.0, 300.0, -120.0, 0.0 };
  GLint especMaterial = 20;

  // Define a concentração do brilho
  //glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

// Define os parâmetros da Luz número Zero
  glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
  glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuzDifusa);
  glEnable(GL_LIGHT0);

}

void ObservadorDoModelo(void) {
  gluPerspective(angle, fAspect, 10, 5000);
  glTranslatef(0, 0, (GLfloat)-obsZ);
  glRotatef(rotX, 1, 0, 0);
  glRotatef(rotY, 0, 1, 0);
  glutPostRedisplay();
}

void ObservadorDoGrafico(void) {
  gluPerspective(160, fAspect, 0.5, 5000);
  glTranslatef(-1700, -800, ((GLfloat)-obsZChart));
  glutPostRedisplay();
}

void EspecificaParametrosVisualizacao(void){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
  width = w;
  height = h;
  if (h == 0) 
     h = 1;

  glViewport(0, 0, w, h);

  fAspect = (GLfloat)w / (GLfloat)h;
}

void drawText(const char* text, float posX = 4, float posY = -4, int font = 12, const char* color = "black") {
  if (color == "black") {
    glColor3f(0.0f, 0.0f, 0.0f);
  }
  else if (color == "red") {
    glColor3f(1.0f, 0.0f, 0.0f);
  }
  else if (color == "green") {
    glColor3f(0.0f, 1.0f, 0.0f);
  }
  else if (color == "blue") {
    glColor3f(0.0f, 0.0f, 1.0f);
  }
  else if (color == "yellow") {
    glColor3f(1.0f, 1.0f, 0.0f);
  }
  else if (color == "pink") {
    glColor3f(1.0f, 0.0f, 1.0f);
  }
  else if (color == "ciano") {
    glColor3f(0.0f, 1.0f, 1.0f);
  }

  glRasterPos2f(posX, posY);
  for (int i = 0; text[i] != '\0'; i++) {
    if (font == 12) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
    else {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
  }
}

void drawViewPort1() {
  glPushMatrix();
  glViewport(0, height / 2, width, height / 2);
  if (width > 960) {
    obsZChart = 190;
  }
  else {
    obsZChart = 260;
  }
  glLineWidth(5);
  glBegin(GL_LINE_STRIP);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex2f(-1, -1);
  glVertex2f(1, -1);
  glEnd();
  glLineWidth(1);

  drawText("Visualizacao dos angulos", -0.15, 0.8, 18, "black");
  drawText("hipLeft: ", -0.80, -0.95, 12);
  drawText("---- ", -0.72, -0.95, 12, "red");

  drawText("kneeLeft: ", -0.62, -0.95, 12);
  drawText("---- ", -0.50, -0.95, 12, "green");

  drawText("footLeft: ", -0.40, -0.95, 12);
  drawText("---- ", -0.28, -0.95, 12, "blue");

  drawText("hipRight: ", -0.18, -0.95, 12);
  drawText("---- ", -0.1, -0.95, 12, "yellow");

  drawText("kneeRight: ", 0.1, -0.95, 12);
  drawText("---- ", 0.24, -0.95, 12, "pink");

  drawText("footRight: ", 0.34, -0.95, 12);
  drawText("---- ", 0.46, -0.95, 12, "ciano");
  glTranslatef(xTranslateChart, 0, 0);
  glTranslatef(0, yTranslateChart, 0);

  ObservadorDoGrafico();

  glBegin(GL_LINE_STRIP);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex2f(0, -400);
  glVertex2f(0, 2000);
  glVertex2f(-30, 2000);
  glVertex2f(0, 2050);
  glVertex2f(30, 2000);
  glVertex2f(0, 2000);
  glEnd();

  glBegin(GL_LINE_STRIP);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex2f(-100, 0);
  glVertex2f(3650, 0);
  glVertex2f(3650, 50);
  glVertex2f(3680, 0);
  glVertex2f(3650, -50);
  glVertex2f(3650, 0);
  glEnd();

  glScalef(xScaleGraphic, 1, 1);
  drawText("0", 0, -100, 12);
  drawText("449", 449, -100, 12);
  drawText("898", 898, -100, 12);
  drawText("1347", 1347, -100, 12);
  drawText("1796", 1796, -100, 12);
  drawText("2245", 2245, -100, 12);
  drawText("2694", 2694, -100, 12);
  drawText("3143 ", 3143, -100, 12);
  drawText("3590 ", 3590, -100, 12);

  glScalef(1, yScaleGraphic, 1);

  axisYhipLeft[i] = hipLeft;
  axisYkneeLeft[i] = kneeLeft;
  axisYfootLeft[i] = footLeft;
  axisYhipRight[i] = hipRight;
  axisYkneeRight[i] = kneeRight;
  axisYfootRight[i] = footRight;

  glLineWidth(1.5);

  if (flagHipLeft) {
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    for (int x = 0; x < 3590; x++) {
      glVertex2i(x, axisYhipLeft[x] );
    }
    glEnd();
  }
  if (flagKneeLeft) {
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    for (int x = 0; x < 3590; x++) {
      glVertex2i(x, axisYkneeLeft[x] );
    }
    glEnd();
  }

  if (flagFootLeft) {
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);
    for (int x = 0; x < 3590; x++) {
      glVertex2i(x, axisYfootLeft[x] );
    }
    glEnd();
  }

  if (flagHipRight) {
    glColor3f(1, 1, 0);
    glBegin(GL_LINE_STRIP);
    for (int x = 0; x < 3590; x++) {
      glVertex2i(x, axisYhipRight[x] );
    }
    glEnd();
  }

  if (flagKneeRight) {
    glColor3f(1, 0, 1);
    glBegin(GL_LINE_STRIP);
    for (int x = 0; x < 3590; x++) {
      glVertex2i(x, axisYkneeRight[x] );
    }
    glEnd();
  }

  if (flagFootRight) {
    glColor3f(0, 1, 1);
    glBegin(GL_LINE_STRIP);
    for (int x = 0; x < 3590; x++) {
      glVertex2i(x, axisYfootRight[x] );
    }
    glEnd();
  }
  glLineWidth(1);

  glPopMatrix();
}

void drawViewPort2() {

  glViewport(0, 0, width / 2, height / 2);
  glLineWidth(5);
  glBegin(GL_LINE_STRIP);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex2f(1, 1);
  glVertex2f(1, -1);
  glEnd();
  glLineWidth(1);

  if (play) {
    drawText("Simulacao em andamento");
  }
  if (pause) {
    drawText("Simulacao pausada");
  }
  if (reset) {
    drawText("Simulacao parada");
  }
  ObservadorDoModelo();
  /*Solo*/

  glColor3f(0.0f, 0.0f, 0.0f);
  glPushMatrix();
  glPushMatrix();
  glColor3f(0.5f, 0.5f, 0.5f);
  glRotatef(45, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, -2.5f, 0.0f);
  glScalef(5.0f, 0.01f, 5.0f);
  glutSolidCube(2.0f);
  glPopMatrix();
  glColor3f(0.85f, 0.63f, 0.50f);
  glRotatef(30, 0.0f, 1.0f, 0.0f);

  glRotatef((GLfloat)allModel, 0.0, 1.0, 0.0);

  /*Bone Central*/
  glPushMatrix();
  glTranslatef(0.0, 0.5, 0.0);
  glScalef(0.2f, 1.0f, 0.2f);
  glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-90, 0.0, 0.0, 1.0);
  glTranslatef(0.0f, 0.3f, 0.0f);
  glScalef(0.4f, 0.6f, 0.4f);
  glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-90, 0.0, 0.0, 1.0);
  glTranslatef(0.0f, -0.3f, 0.0f);
  glScalef(0.4f, 0.6f, 0.4f);
  glutSolidCube(1.0);
  glPopMatrix();
  glPushMatrix();
  glutWireSphere(0.10, 25, 25);
  glPopMatrix();

  /*PERNA ESQUERDA*/
  glPushMatrix();
  glTranslatef(0.6f, -0.5f, 0.0f);

  glRotatef(-90, 0.0, 0.0, 1.0);
  glTranslatef(-0.5f, 0.0f, 0.0f);

  glRotatef((GLfloat)hipLeft, 0.0, 1.0, 0.0);
  glPushMatrix();
  glutSolidSphere(0.22, 25, 25);
  glPopMatrix();
  glTranslatef(0.5f, 0.0f, 0.0f);
  glPushMatrix();
  glScalef(1.0f, 0.3f, 0.3f);
  glutSolidCube(1.0);
  glPopMatrix();

  glTranslatef(0.5f, 0.0f, 0.0f);
  glPushMatrix();
  glutSolidSphere(0.22, 25, 25);
  glPopMatrix();
  glTranslatef(-0.5f, 0.0f, 0.0f);

  glTranslatef(0.5f, 0.0f, 0.0f);
  glRotatef((GLfloat)kneeLeft, 0.0, 1.0, 0.0);
  glTranslatef(0.5f, 0.0f, 0.0f);

  glPushMatrix();
  glScalef(1.0f, 0.2f, 0.2f);
  glutSolidCube(1.0);
  glPopMatrix();

  glTranslatef(0.5, 0.0, 0.0);
  glPushMatrix();
  glutSolidSphere(0.13, 25, 25);
  glPopMatrix();
  glTranslatef(-0.5, 0.0, 0.0);

  glTranslatef(0.5, 0.0, 0.0);
  glRotatef((GLfloat)footLeft, 0.0, 1.0, 0.0);

  glTranslatef(0.25, 0.0, 0.0);

  glPushMatrix();
  glScalef((GLfloat)0.5, (GLfloat)0.2, (GLfloat)0.08);
  glutSolidCube(1.0);
  glPopMatrix();
  glPopMatrix();

  /*PERNA DIREITA*/
  glPushMatrix();
  glTranslatef(-0.6f, -0.5f, 0.0f);
  glRotatef(-90, 0.0, 0.0, 1.0);
  glTranslatef(-0.5, 0.0, 0.0);
  glRotatef((GLfloat)hipRight, 0.0, 1.0, 0.0);
  glPushMatrix();
  glutSolidSphere(0.23, 25, 25);
  glPopMatrix();

  glTranslatef(0.5, 0.0, 0.0);
  glPushMatrix();
  glScalef(1.0f, 0.3f, 0.3f);
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
  glScalef(1.0f, 0.2f, 0.2f);
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
  glScalef((GLfloat)0.5, (GLfloat)0.2, (GLfloat)0.08);
  glutSolidCube(1.0);
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
}

void drawViewPort3() {

  glViewport(width / 2, 0, width / 2, height / 2);
  drawText("Skeleton Model - TCC",-0.3, 0.8, 18, "red");

   char text2[] = "Aluno: Edmo de Oliveira Leite";
   drawText("Aluno: Edmo de Oliveira Leite", -0.9, 0.6, 13);
   drawText("Matricula: 15.2.8045", -0.9, 0.4, 13);
   drawText("Trabalho de Conclusão de Curso II do curso de Bacharelado ", -0.9, 0.2, 12);
   drawText(" em Engenharia da Computação ", -0.9, 0.1, 12);

}

void Janelas(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  drawViewPort1();
  drawViewPort3();

  lighting();
  drawViewPort2();
  glutSwapBuffers();
}

void Teclas(unsigned char key, int x, int y) {
  cout << obsZChart << endl;

  switch (key) {
  case '1':
    allModel = (allModel + 1) % 360;
    glutPostRedisplay();
    break;
  case '2':
    allModel = (allModel - 1) % 360;
    glutPostRedisplay();
    break;
  case 'C':
    xTranslateChart += 0.005;
    break;
  case 'c':
    xTranslateChart -= 0.005;
    break;
  case 'Y':
      yTranslateChart += 0.005;
      break;
  case 'y':
      yTranslateChart -= 0.005;
      break;
  case 43:
    if (xScaleGraphic < 20) {
      xScaleGraphic += 0.1;
    }
    else {
      xScaleGraphic = 20;
    }
    break;
  case 45:
    if (xScaleGraphic > 1) {
      xScaleGraphic -= 0.1;
    }
    else {
      xScaleGraphic = 1;
    }
    break;
  case 57:
    if (yScaleGraphic < 20) {
      yScaleGraphic += 0.1;
    }
    else {
      yScaleGraphic = 20;
    }
    break;
  case 54:
    if (yScaleGraphic > 0.1) {
      yScaleGraphic -= 0.1;
    }
    else {
      yScaleGraphic = 0.1;
    }

    break;
  default:
    break;
  }

}

void TeclasEspeciais(int tecla, int x, int y) {
  switch (tecla)
  {
  case GLUT_KEY_RIGHT:	rotY--;
    break;
  case GLUT_KEY_LEFT:rotY++;
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
  //ObservadorDoModelo();
  glutPostRedisplay();
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
      if (angle <= 5)
        angle += 1;
    }
  glutPostRedisplay();
}

void Animacao() {
  if (play) {
    play = true;
    flag = false;
    if (i == 0) {
      cout << "Simulacao iniciada com sucesso. " << endl;
    }
    else if (i == 898) { cout << "25% da simulacao concluida: ||| " << endl; }
    else if (i == 1796) { cout << "50% da simulacao concluida: |||||| " << endl; }
    else if (i == 2694) { cout << "75% da simulacao concluida: ||||||||| " << endl; }
    else if (i == 3590) { cout << "100% - Simulacao concluida: |||||||||||| " << endl; }
    
    if (i<3518) {
      hipLeft = matrix[i][0];
      kneeLeft = matrix[i][1];
      footLeft = matrix[i][2];
      hipRight = matrix[i][3];
      kneeRight = matrix[i][4];
      footRight = matrix[i][5];
      i++;
      //cout << "FRAME: " <<i<<"\n" << endl;

      //cout << "hipLeft: " << matrix[i][0] << endl;
      //cout << "kneeLeft: " << matrix[i][1] << endl;
      //cout << "footLeft: " << matrix[i][2] << endl;
      //cout << "hipRight: " << matrix[i][3] << endl;
      //cout << "kneeRight: " << matrix[i][4] << endl;
      //cout << "footRight: " << matrix[i][5] << endl;
      //cout << "\n" << endl;

      //cout << "hipLeft: " << hipLeft << endl;
      //cout << "kneeLeft: " << kneeLeft << endl;
      //cout << "footLeft: " << footLeft << endl;
      //cout << "hipRight: " << hipRight << endl;
      //cout << "kneeRight: " << kneeRight << endl;
      //cout << "footRight: " << footRight << endl;
      //cout << "===============\n"<< endl;

    }
    else {
      cout << "A simulacao foi finalizada com sucesso. " << endl;
      hipLeft = matrix[1][0];
      kneeLeft = matrix[1][1];
      footLeft = matrix[1][2];
      hipRight = matrix[1][3];
      kneeRight = matrix[1][4];
      footRight = matrix[1][5];
    }
    Sleep(16);
    glutPostRedisplay();
  }

  if (pause && flag) {
    pause = true;
    flag = false;
    cout << "A simulacao foi pausada. " << endl;
    glutPostRedisplay();
  }


  if (reset && flag) {
    cout << "entrou aqui" << endl;
    flag = false;
    reset = true;
    i = 0;
    allModel = 0;
    hipLeft = matrix[1][0];
    kneeLeft = matrix[1][1];
    footLeft = matrix[1][2];
    hipRight = matrix[1][3];
    kneeRight = matrix[1][4];
    footRight = matrix[1][5];
    angle = 5;
    rotX = 30;
    rotY = 180;
    obsZ = 100;
    cout << "A simulacao foi resetada. " << endl;
    for (int i = 0; i < 10000; i++) {
        axisYhipLeft[i] = 0;
        axisYkneeLeft[i] = 0;
        axisYfootLeft[i] = 0;
        axisYhipRight[i] = 0;
        axisYkneeRight[i] = 0;
        axisYfootRight[i] = 0;
    }
    glutPostRedisplay();
  }

  EspecificaParametrosVisualizacao();
}

void menuPrincipal(int option) {
  switch (option) {
  case 0: /*Play/Continuar*/
    reset = false;
    pause = false;
    play = true;
    //flag = !flag;
    break;
  case 1: /*Pause*/
    reset = false;
    pause = true;
    play = false;
    flag = !flag;
    frameAux = i;

    break;
  case 2: /*Stop/Reset*/
    reset = true;
    pause = false;
    play = false;
    flag = !flag;
    break;
  case 3:
  case 4: /*Exit*/
    exit(0);
  }
}

void subMenu(int option)
{
  switch (option) {
  case 0:
    flagHipLeft = !flagHipLeft;
    break;
  case 1:
    flagKneeLeft = !flagKneeLeft;
    break;
  case 2:
    flagFootLeft = !flagFootLeft;
    break;
  case 3:
    flagHipRight = !flagHipRight;
    break;
  case 4:
    flagKneeRight = !flagKneeRight;
    break;
  case 5:
    flagFootRight = !flagFootRight;
    break;
  }
}

int main(int argc, char** argv) {
  readCsv();

  /*=================================
       POSIÇÃO INICIAL DO MODELO
  ===================================*/
  hipLeft = matrix[1][0];
  kneeLeft = matrix[1][1];
  footLeft = matrix[1][2];
  hipRight = matrix[1][3];
  kneeRight = matrix[1][4];
  footRight = matrix[1][5];
  /*=================================
     CONFIGURAÇÕES INICIAIS DO OPENGL
  ===================================*/
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(960, 700);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Skeleton Model");
  ParametrosIniciais();

  glutDisplayFunc(Janelas);
  glutReshapeFunc(AlteraTamanhoJanela);
  glutIdleFunc(Animacao);
  glutKeyboardFunc(Teclas);
  glutSpecialFunc(TeclasEspeciais);
  glutMouseFunc(GerenciaMouse);

  /*=================================
                  MENU
  ===================================*/

  int lineChartSubMenu = glutCreateMenu(subMenu);
  glutAddMenuEntry("HipLeft", 0);
  glutAddMenuEntry("KneeLeft", 1);
  glutAddMenuEntry("FootLeft", 2);
  glutAddMenuEntry("HipRight", 3);
  glutAddMenuEntry("KneeRight", 4);
  glutAddMenuEntry("FootRight", 5);


  glutCreateMenu(menuPrincipal);
  glutAddMenuEntry("Play/Continuar", 0);
  glutAddMenuEntry("Pause", 1);
  glutAddMenuEntry("Stop/Reset", 2);
  glutAddSubMenu("Lines os chart", lineChartSubMenu);
  glutAddMenuEntry("Open Graph", 3);
  glutAddMenuEntry("Exit", 4);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}

