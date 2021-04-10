#pragma warning(disable : 4005)
#ifdef WIN32
#include <windows.h>
#endif
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
  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);

  //Habilita o uso de iluminação
  //glEnable(GL_LIGHTING);

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
  obsZ = 100;
}

void readCsv() {
  ifstream myFile;
  myFile.open("G:\\Meu Drive\\UFOP\\TCC\\Parte 2\\Banco de Dados\\angle_1_person.csv");
  int i = 0, j = 0;

  while (myFile.good()) {
    string line, intermediate;
    GLfloat frame[6] = {};
    int temp = 1;
    getline(myFile, line, '\n');
    vector <string> tokens;
    stringstream check(line);

    while (getline(check, intermediate, ',')) {
      double numberIntermediate = stof(intermediate);
      frame[i] = (GLfloat)(((numberIntermediate * 180) / (3.14)) * 3);
      i++;
    }
    i = 0;
    for (int i = 0; i < 6; i++) {
      matrix[j][i] = frame[i];
    }
    cout << "frame: " << j << endl;
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

void PosicionaObservador(void)
{
  // Especifica sistema de coordenadas do modelo
  glMatrixMode(GL_MODELVIEW);
  // Inicializa sistema de coordenadas do modelo
  glLoadIdentity();
  lighting();
  // Especifica posição do observador e do alvo
  glTranslatef(0, 0, (GLfloat)-obsZ);
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
int i, frameAux;
boolean play, reset, pause;
int flag = false;

void drawText(char text[], int posX = 5.0, int posY = -10, int font = 12) {
  glColor3f(1.0f, 1.0f, 1.0f);
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

void display1(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  char text[] = "Skeleton Model ";
  drawText(text, -2, 10, 18);
  if (play) {
    char text[] = "Simulacao em andamento ";
    drawText(text);
  }
  if (pause) {
    char text[] = "Simulacao pausada. ";
    drawText(text);
  }
  if (reset) {
    char text[] = "Simulacao parada. ";
    drawText(text);
  }

  lighting();
  glColor3f(0.85f, 0.63f, 0.50f);
  glPushMatrix();
  glPushMatrix();
  glColor3f(0.8f, 0.8f, 0.8f);
  glRotatef(45, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, -2.1f, 0.0f);
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
  case 'U':
  case 'u':
    hipLeft = matrix[i][0] - 45 % 360;
    kneeLeft = matrix[i][1] - 45 % 360;
    footLeft = matrix[i][2] - 45 % 360;
    hipRight = matrix[i][3] - 45 % 360;
    kneeRight = matrix[i][4] - 45 % 360;
    footRight = matrix[i][5] - 45 % 360;
    i++;
    cout << "tempo: " << i << endl;
    cout << "hipLeft: " << matrix[i][0] << endl;
    cout << "kneeLeft: " << matrix[i][1] << endl;
    cout << "footLeft: " << matrix[i][2] << endl;
    cout << "hipRight: " << matrix[i][3] << endl;
    cout << "kneeRight: " << matrix[i][4] << endl;
    cout << "footRight: " << matrix[i][5] << endl;
    glutPostRedisplay();
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
  PosicionaObservador();
  glutPostRedisplay();
}

int windowPlot() {
  glutCreateWindow("Plot dos grficos");   // Create a window 2
  glutDisplayFunc(display);   // Register display callback
  glutMainLoop();             // Enter main event loop
  return 0;
}

void idle() {

  if (play) {
    play = true;
    flag = false;
    if (i == 0) {
      cout << "Simulacao iniciada com sucesso. " << endl;
    }
    else if (i == 898) { cout << "25% da simulacao concluida: ||| " << endl; }
    else if (i == 1796) { cout << "50% da simulacao concluida: |||||| " << endl; }
    else if (i == 2694) { cout << "75% da simulacao concluida: ||||||||| " << endl; }
    else if (i == 3593) { cout << "       Simulacao concluida: |||||||||||| " << endl; }

    if (i < 3590) {
      hipLeft = matrix[i][0] - 45;
      kneeLeft = matrix[i][1] - 45;
      footLeft = matrix[i][2] - 45;
      hipRight = matrix[i][3] - 45;
      kneeRight = matrix[i][4] - 45;
      footRight = matrix[i][5] - 45;
      i++;
    }
    else {
      cout << "A simulacao foi finalizada com sucesso. " << endl;
      glutIdleFunc(NULL);
    }
    Sleep(60);
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
    hipLeft = -30;
    kneeLeft = 45;
    footLeft = -65;
    footRight = -65;
    kneeRight = 45;
    hipRight = -30;
    angle = 10;
    rotX = 30;
    rotY = 0;
    obsZ = 100;
    cout << "A simulacao foi resetada. " << endl;
    glutPostRedisplay();
  }
}

void menu(int option) {
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
    windowPlot();
  case 4: /*Exit*/
    exit(0);
  }
}

int main(int argc, char** argv)
{
  readCsv();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1024, 824);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Skeleton Model");
  init();

  glutDisplayFunc(display1);
  glutReshapeFunc(AlteraTamanhoJanela);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(TeclasEspeciais);
  glutMouseFunc(GerenciaMouse);

  /*=================================
                  MENU
  ===================================*/
  glutCreateMenu(menu);
  glutAddMenuEntry("Play/Continuar", 0);
  glutAddMenuEntry("Pause", 1);
  glutAddMenuEntry("Stop/Reset", 2);
  glutAddMenuEntry("Open Graph", 3);
  glutAddMenuEntry("Exit", 4);
  glutAttachMenu(GLUT_RIGHT_BUTTON);






  glutMainLoop();
  return 0;
}