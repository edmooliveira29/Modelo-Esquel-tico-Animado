#pragma warning(disable : 4005)
#ifdef WIN32
#include <windows.h>
#endif
# define FNULL 0L
void (*display2) (void) = FNULL;
#include <locale>
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

static int allModel,
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
int i = 30, frameAux, lineDivX, tamArquivo;
boolean play, reset, pause, openGraph = true, carregandoArquivo = false;
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
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  angle = 5;
  allModel = 195;
  angleGraphic = 160;
  rotX = 15;
  rotY = 0;
  obsZ = 100;
  obsZChart = 0;
  xScaleGraphic = 1;
  yScaleGraphic = 1;
  xTranslateChart = 0;
  yTranslateChart = 0;
}

string lerCaminho(string opcao) {
    string caminho;
    if (opcao == "1") {
        return "entrar";
    }else if (opcao == "2") {
        return "C:\\Program Files (x86)\\Modelo 3D\\arquivo_processamento_ideal.csv";
    }
    else if (opcao == "3") {
        return "C:\\Program Files (x86)\\Modelo 3D\\arquivo_sem_processamento.csv";
    }
    else if (opcao == "4") {
        cout << "Digite o caminho: ";
        getline(cin, caminho);
        return caminho;
    }
}

void readCsv(bool entrar,string opcao = "1") {
  ifstream myfile;
  int flag = 0;
  string opcaoInterna = opcao;
  
  setlocale(LC_ALL, "Portuguese");

  if (entrar) {
      cout << "***********************************************************" << endl;
      cout << "                 AVALIAÇÃO DA MARCHA HUMANA               " << endl;
      cout << "***********************************************************" << endl;
      cout << "Autor do código: Edmo de Oliveira Leite" << endl;
      cout << "Pesquisa realizada entre agosto de 2019 à agosto de 2021\n" << endl;
      cout << "MENU INICIAL" << endl;
      cout << "     1 - Entrar na animação sem carregar arquivos" << endl;
      cout << "     2 - Carregar arquivo com o processamento ideal" << endl;
      cout << "     3 - Carregar arquivo sem processamento" << endl;
      cout << "     4 - Digite o caminho do arquivo a ser lido" << endl;
      cout << "         Observações: O arquivo deve estar no formato .csv com o " << endl;
      cout << "                      conteúdo parecido com este modelo abaixo:" << endl;
      cout << "                      184,175,275,199,173,245" << endl;
      cout << "                      185,172,265,197,176,245\n" << endl;
      cout << "                      Cada linha do arquivo representa um frame" << endl;
      cout << "                      onde cada frame contém o valor de 6 ângulos" << endl;
      cout << "                      em graus, na seguinte sequência:" << endl;
      cout << "                        1 - Dorso Esquerdo" << endl;
      cout << "                        2 - Joelho Esquerdo" << endl;
      cout << "                        3 - Pé Esquerdo" << endl;
      cout << "                        4 - Dorso Direito" << endl;
      cout << "                        5 - Joelho Direito" << endl;
      cout << "                        4 - Pé Direito" << endl;
      cout << "                        Geralmente o caminho e definido da seguinte forma:" << endl;
      cout << "                        C:\\Users\\SeuNome\\Downloads\\nomedoarquivo.csv\n\n" << endl;
      cout << "Digite a opção desejada: "; getline(cin, opcaoInterna);
        while (opcaoInterna != "1" && opcaoInterna != "2" && opcaoInterna != "3" && opcaoInterna != "4") {
            cout << "Opção inválida! Digite uma nova opção: "; getline(cin, opcaoInterna);
        }
      
  }
  
  string caminho = lerCaminho(opcaoInterna);

  if (caminho != "entrar") {
      myfile.open(caminho);

      while (myfile.is_open() == 0) {
          cout << "O caminho digitado esta incorreto!" << endl;
          cout << "Digite uma nova opção: "; getline(cin, opcaoInterna);
          myfile.open(lerCaminho(opcaoInterna));

      }

      int i = 0, j = 0, h = 0;
      cout << "[";
      while (myfile.good()) {
          string line, intermediate;
          GLfloat frame[6] = {};
          int temp = 1;
          getline(myfile, line, '\n');
          vector <string> tokens;
          stringstream check(line);

          if (j > 20 && j < 3519) {
              while (getline(check, intermediate, ',')) {
                  double numberIntermediate = stof(intermediate);
                  frame[i] = (GLfloat)(numberIntermediate)-190;
                  i++;
              }
              i = 0;
              h++;
              if (h % 30 == 0)
                  cout << ".";

              for (int i = 0; i < 6; i++) {
                  matrix[h][i] = frame[i];
              }
              tamArquivo = h;
              
          }

          j++;
      }
      cout << "]\n";
      cout << "Arquivo carregado com sucesso!" << endl;
      cout << "Ao entrar, observe os comandos na legenda." << endl;

      cout << "Carregando animação...";
      if (carregandoArquivo == false) {
          Sleep(4000);
      }
  }
  else {
      cout << "Ao entrar, clique com o botão direito do mouse em algum lugar" << endl; 
      cout << "da tela e selecione carregar arquivos pré-definidos e aperte Espaço para dar um play." << endl;
      cout << "Carregando animação...";
      Sleep(8000);
  }
}

void lighting(void)
{
  GLfloat luzAmbiente[4] = { (GLfloat)0.3,(GLfloat)0.3,(GLfloat)0.3,(GLfloat)1.0 };
  GLfloat luzDifusa[4] = { 1.0,1.0,1.0, 1.0 };
  GLfloat posicaoLuzDifusa[4] = { 300.0, 300.0, -180.0, 0.0 };
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
  glTranslatef(-1780, -900, ((GLfloat)-obsZChart));
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

void drawText(const char* text, float posX = -0.9, float posY = -0.9, int font = 14, const char* color = "black") {
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
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
    else {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    }
  }
}

void drawViewPort1() {
  glPushMatrix();
  if (openGraph == true) {
      glViewport(0, height / 2, width, height / 2);
  }
  if (width > 960) {
    obsZChart = 190;
  }
  else {
    obsZChart = 260;
  }
  glLineWidth(5);
  glBegin(GL_LINE_STRIP);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex2i(-1, -1);
  glVertex2i(1, -1);
  glEnd();
  glLineWidth(1);
  drawText("Angulos x Frames", -0.15, 0.8, 18, "black");
  drawText("(Frames - fps)", 0.8, -0.95, 12, "ciano");
  drawText("(Angulo - graus)", -0.98, 0.9, 12, "ciano");


  glTranslatef(xTranslateChart, 0, 0);
  glTranslatef(0, yTranslateChart, 0);
  ObservadorDoGrafico();

  glBegin(GL_LINE_STRIP);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex2i(0, 0);
  glVertex2i(0, 1800);
  glEnd();

  glBegin(GL_LINE_STRIP);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex2i(0, 0);
  glVertex2i(3650, 0);
  glEnd();
  glScalef(xScaleGraphic, 1, 1);
  drawText("0", 0, -55, 12);
  drawText("449", 449, -55, 12);
  drawText("898", 898, -55, 12);
  drawText("1347", 1347, -55, 12);
  drawText("1796", 1796, -55, 12);
  drawText("2245", 2245, -55, 12);
  drawText("2694", 2694, -55, 12);
  drawText("3143 ", 3143, -55, 12);
  drawText("3590 ", 3570, -55, 12);


  glScalef(1, yScaleGraphic, 1);

  drawText("135", -55, 500, 12);
  drawText("158", -55, 657, 12);
  drawText("180", -55, 813, 12);
  drawText("203", -55, 970, 12);
  drawText("225 ", -55, 1126, 12);
  drawText("248 ", -55, 1282, 12);
      drawText("271", -55, 1438, 12);
  drawText("294", -55, 1594, 12);



  axisYhipLeft[i] = ((hipLeft) * 9) + 600;
  axisYkneeLeft[i] = (-kneeLeft * 7) + 800;
  axisYfootLeft[i] = (footLeft * 8) + 800;
  axisYhipRight[i] = (hipRight * 9) +600;
  axisYkneeRight[i] = (-kneeRight * 7) + 800;
  axisYfootRight[i] = (footRight * 8) + 800;

  glLineWidth(1.0);

  if (flagHipLeft) {
    drawText("HipLeft",3590, 650,12, "red");

    glColor3f(1, 0, 0);
   
    glBegin(GL_LINE_STRIP);
    for (int x = 0; x < 3590; x++) {
      glVertex2i(x, axisYhipLeft[x]);
    }

    glEnd();
  }
  if (flagKneeLeft) {
    glColor3f(0, 1, 0);
    drawText("KneeLeft", 3570, 850, 12, "green");

    glBegin(GL_LINE_STRIP);
    for (int x = 0; x < 3590; x++) {
      glVertex2i(x, axisYkneeLeft[x] );
    }
    glEnd();
  }

  if (flagFootLeft) {
    drawText("FootLeft", 3570, 1200, 12, "blue");

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);
    for (int x = 0; x < 3590; x++) {
      glVertex2i(x, axisYfootLeft[x] );
    }
    glEnd();
  }

  if (flagHipRight) {
    drawText("HipRight", 3570, 590, 12, "yellow");

    glColor3f(1, 1, 0);
    glBegin(GL_LINE_STRIP);
    for (int x = 0; x < 3590; x++) {
      glVertex2i(x, axisYhipRight[x] );
    }
    glEnd();
  }

  if (flagKneeRight) {
      drawText("KneeRight", 3570, 910, 12, "ciano");

    glColor3f(1, 0, 1);
    glBegin(GL_LINE_STRIP);
    for (int x = 0; x < 3590; x++) {
      glVertex2i(x, axisYkneeRight[x] );
    }
    glEnd();
  }

  if (flagFootRight) {
      drawText("FootRight", 3570, 1260, 12, "pink");

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
    if (openGraph == true) {
       glViewport(0, 0, width / 2, height / 2);
    }
    else {
        glViewport(0, 0, width, height);
    }

  glLineWidth(5);
  glBegin(GL_LINE_STRIP);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex2i(1, 1);
  glVertex2i(1, -1);
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
    if (openGraph == true) {

        glViewport(width / 2, 0, width / 2, height / 2);
    }
  drawText("Skeleton Model - TCC",-0.3, 0.8, 18, "red");

   drawText("Aluno: Edmo de Oliveira Leite", -0.4, 0.6, 13);
   drawText("Matricula: 15.2.8045", -0.3, 0.5, 13);

   drawText("COMANDOS GERAIS", -0.9, 0.35, 12);
   drawText("O: Tela Cheia/Graficos", -0.9, 0.25, 12);
   drawText("Espaco: Play", -0.9, 0.15, 12);
   drawText("P: Pause", -0.9, 0.05, 12);
   drawText("R: Reset", -0.9, -0.05, 12);
   drawText("Esc: Sair", -0.9, -0.15, 12);

   drawText("COMANDOS DOS GRAFICOS", -0.1, 0.35, 12);
   drawText("G ou T: Deslocar grafico para esquerda ou direita", -0.1, 0.25, 12);
   drawText("H ou Y: Deslocar grafico para cima ou para baixo", -0.1, 0.15, 12);
   drawText("J ou U: Zoom in/Zoom out no eixo x", -0.1, 0.05, 12);
   drawText("K ou I: Zoom in/Zoom out no eixo y", -0.1, -0.05, 12);
   drawText("Botao direito do mouse/Linhas do grafico: habilita o grafico ", -0.1, -0.15, 12);

   drawText("COMANDOS DO MODELO", -0.9, -0.35, 12);
   drawText("Setas do teclado movimenta o modelo", -0.9, -0.45, 12);
   drawText("Scrool do mouse: Zoom in/Zoom out", -0.9, -0.55, 12);

}

void Janelas(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  if (openGraph == true) {
      drawViewPort1();
      drawViewPort3();
      lighting();
      drawViewPort2();
      glutSwapBuffers();
  }
  else {
      lighting();
      drawViewPort2();
      glutSwapBuffers();
  }
}
 
void Teclas(unsigned char key, int x, int y) {

  switch (key) {
  case '1':
    allModel = (allModel + 1) % 360;
    glutPostRedisplay();
    break;
  case '2':
    allModel = (allModel - 1) % 360;
    glutPostRedisplay();
    break;
  case 't':
  case 'T':
    xTranslateChart += 0.05;
    break;
  case 'g':
  case 'G':
    xTranslateChart -= 0.05;
    break;
  case 'Y':
  case 'y':
      yTranslateChart += 0.05;
      break;
  case 'h':
  case 'H':
      yTranslateChart -= 0.05;
      break;
  case 'U':
  case 'u':
    if (xScaleGraphic < 20) {
      xScaleGraphic += 0.1;
    }
    else {
      xScaleGraphic = 20;
    }
    break;
  case 'J':
  case 'j':
    if (xScaleGraphic > 1) {
      xScaleGraphic -= 0.1;
    }
    else {
      xScaleGraphic = 1;
    }
    break;
  case 'i':
  case 'I':
    if (yScaleGraphic < 20) {
      yScaleGraphic += 0.1;
    }
    else {
      yScaleGraphic = 20;
    }
    break;
  case 'K':
  case 'k':
    if (yScaleGraphic > 0.1) {
      yScaleGraphic -= 0.1;
    }
    else {
      yScaleGraphic = 0.1;
    }
    break;
  case 32:
      reset = false;
      pause = false;
      play = true;
      //flag = !flag;
      break;

  case 112:
  case 80:
      reset = false;
      pause = true;
      play = false;
      flag = !flag;
      frameAux = i;

  case 114:
  case 82:
      reset = true;
      pause = false;
      play = false;
      flag = !flag;
      break;
  case 'o':
  case 'O':
      openGraph = !openGraph;
      break;
  case 27: /*Exit*/
      exit(0);
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
    if (i<tamArquivo) {
      hipLeft = matrix[i][0];
      kneeLeft = matrix[i][1];
      footLeft = matrix[i][2];
      hipRight = matrix[i][3];
      kneeRight = matrix[i][4];
      footRight = matrix[i][5];
      i++;
    }
    else {
      hipLeft = matrix[30][0];
      kneeLeft = matrix[30][1];
      footLeft = matrix[30][2];
      hipRight = matrix[30][3];
      kneeRight = matrix[30][4];
      footRight = matrix[30][5];
      reset = true;
      play = false;
    }
    Sleep(16);
    glutPostRedisplay();
  }

  if (pause && flag) {
    pause = true;
    flag = false;
    glutPostRedisplay();
  }

  if (reset && flag) {
    flag = false;
    reset = true;
    i = 0;
    allModel = 195;
    hipLeft = matrix[30][0];
    kneeLeft = matrix[30][1];
    footLeft = matrix[30][2];
    hipRight = matrix[30][3];
    kneeRight = matrix[30][4];
    footRight = matrix[30][5];
    angle = 5;
    rotX = 15;
    rotY = 0;
    obsZ = 100;
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
  case 112:
  case 80:
    reset = false;
    pause = true;
    play = false;
    flag = !flag;
    frameAux = i;

    break;
  case 2:
  case 114:
  case 82:
    reset = true;
    pause = false;
    play = false;
    flag = !flag;
    break;
  case 3:
    openGraph = !openGraph;
    break;
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


void subMenuArquivos(int option)
{
    switch (option) {
    case 0:
        carregandoArquivo = !carregandoArquivo;
        readCsv(false,"2");
        carregandoArquivo = !carregandoArquivo;

        break;
    case 1:
        carregandoArquivo = !carregandoArquivo;
        readCsv(false, "3");
        carregandoArquivo = !carregandoArquivo;

        break;
    }
}



int main(int argc, char** argv) {
 readCsv(true);

  /*=================================
       POSIÇÃO INICIAL DO MODELO
  ===================================*/
  hipLeft = matrix[30][0];
  kneeLeft = matrix[30][1];
  footLeft = matrix[30][2];
  hipRight = matrix[30][3];
  kneeRight = matrix[30][4];
  footRight = matrix[30][5];
  /*=================================
     CONFIGURAÇÕES INICIAIS DO OPENGL
  ===================================*/
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  
  glutInitWindowSize(1920, 1080);
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

  int arquivosParaProcessamento = glutCreateMenu(subMenuArquivos);
  glutAddMenuEntry("Arquivo com processamento", 0);
  glutAddMenuEntry("Arquivo sem processamento", 1);

  glutCreateMenu(menuPrincipal);
  glutAddSubMenu("Carregar arquivos pré-definidos", arquivosParaProcessamento);

  glutAddMenuEntry("Play/Continuar (Espaço)", 0);
  glutAddMenuEntry("Pause (P)", 1);
  glutAddMenuEntry("Reset (R)", 2);
  glutAddSubMenu("Linhas do gráfico", lineChartSubMenu);
  glutAddMenuEntry("Mudar Visualização (0)", 3);
  glutAddMenuEntry("Exit (Esc)", 4);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}

