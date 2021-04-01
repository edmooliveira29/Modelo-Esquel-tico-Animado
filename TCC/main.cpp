#include <windows.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>

static int peEsquerdox = 10,
peDireitox = 10,
femurEsquerdox = -30,
femurEsquerdoy = 0,
femurEsquerdoz = 0,
joelhoEsquerdo = 50,
femurDireitox = -30,
femurDireitoy = 0,
femurDireitoz = 0,
joelhoDireito = 50;

GLfloat angle = 60, fAspect;

void Inicializa(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, 1, 0.5, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 13, 0, 0, 0, 0, 1, 0);
}

void Centro()
{
    glTranslatef(0.0, 2.0, 0.0);
    glutWireSphere(0.7, 10, 10);
    glRotatef(-90, 0.0, 0.0, 1.0);

    glPushMatrix();
    glTranslatef(-1.5, 0.0, 0.0);
    glScalef(3.0, 0.8, 0.8);
    glutWireCube(1.0);
    glPopMatrix();
}

void QuadrilEsquerdo()
{
    glutWireSphere(0.7, 10, 10);
    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(-90, 0.0, 0.0, 1.0);
    glTranslatef(-1.5, 0.0, 0.0);
    glScalef(3.0, 0.8, 0.8);
    glutWireCube(1.0);
    glPopMatrix();
}

void QuadrilDireito()
{
    glutWireSphere(0.7, 10, 10);
    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(90, 0.0, 0.0, 1.0);
    glTranslatef(-1.5, 0.0, 0.0);
    glScalef(3.0, 0.8, 0.8);
    glutWireCube(1.0);
    glPopMatrix();
}

void Coxa()
{
    glutWireSphere(0.7, 10, 10);
    glTranslatef(1.5, 0.0, 0.0);
    glPushMatrix();
    glScalef(3.0, 0.8, 0.8);
    glutWireCube(1.0);
    glPopMatrix();
}

void Tibia()
{
    glutWireSphere(0.5, 10, 10);
    glTranslatef(2.5, 0.0, 0.0);
    glPushMatrix();
    glScalef(5.0, 0.3, 0.3);
    glutWireCube(1.0);
    glPopMatrix();
}

void ExtensaoDoPe()
{
    glPushMatrix();
    glTranslatef(-0.3, -0.5, -0.5);
    glRotatef(-70, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(1.0, 0.1, 0.3);
    gluCylinder(gluNewQuadric(), 1.0, 1.0, 3.0, 10, 10);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}

void PeEsquerdo()
{
    glTranslatef(2.5, 0.0, 0.0);
    glRotatef((GLfloat)peEsquerdox, 0.0, 0.0, 1.0);
    glutWireSphere(0.4, 10, 10);
    glTranslatef(0.6, 0.0, 0.0);
    ExtensaoDoPe();
}


void peDireito()
{
    glTranslatef(2.5, 0.0, 0.0);
    glRotatef((GLfloat)peDireitox, 0.0, 0.0, 1.0);
    glutWireSphere(0.4, 10, 10);
    glTranslatef(0.6, 0.0, 0.0);
    ExtensaoDoPe();
}


void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    Centro();
    glPopMatrix();
    glPushMatrix();

    glTranslatef(-2, 2.0, 0.0);
    glRotatef(-90, 0.0, 0.0, 1.0);



    QuadrilEsquerdo();
    /*Rota??es da perna Esquerda em torno dos eixos x, y, z*/
    glRotatef((GLfloat)femurEsquerdox, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)femurEsquerdoy, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)femurEsquerdoz, 1.0, 0.0, 0.0);
    Coxa();
    /* origem posicionada no joelho */
    glTranslatef(1.5, 0.0, 0.0);
    glRotatef((GLfloat)joelhoEsquerdo, 0.0, 0.0, 1.0);
    Tibia();
    PeEsquerdo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 2.0, 0.0);
    glRotatef(-90, 0.0, 0.0, 1.0);



    QuadrilDireito();
    /*Rota??es da pernaDireita em torno dos eixos x, y, z*/
    glRotatef((GLfloat)femurDireitox, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)femurDireitoy, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)femurDireitoz, 1.0, 0.0, 0.0);
    Coxa();
    /* origem posicionada no joelho */
    glTranslatef(1.5, 0.0, 0.0);
    glRotatef((GLfloat)joelhoDireito, 0.0, 0.0, 1.0);
    Tibia();
    peDireito();
    glPopMatrix();
    glutSwapBuffers();
}

void AlteraTamanhoJanela(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    if (h == 0)
        h = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, (GLfloat)w / (GLfloat)h, 0.5, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 13, 0, 0, 0, 0, 1, 0); // Especifica posi??o do observador e do alvo
}

void Teclado(unsigned char key, int x, int y)
{
    switch (key)
    {

        /* Movimentacao Lado Direito*/

    case 'q':
        femurEsquerdox = (femurEsquerdox + 5) % 360;
        glutPostRedisplay();
        break;
    case 'Q':
        femurEsquerdox = (femurEsquerdox - 5) % 360;
        glutPostRedisplay();
        break;
    case 'a':
        femurEsquerdoy = (femurEsquerdoy + 5) % 360;
        glutPostRedisplay();
        break;
    case 'A':
        femurEsquerdoy = (femurEsquerdoy - 5) % 360;
        glutPostRedisplay();
        break;
    case 'z':
        femurEsquerdoz = (femurEsquerdoz + 5) % 360;
        glutPostRedisplay();
        break;
    case 'Z':
        femurEsquerdoz = (femurEsquerdoz - 5) % 360;
        glutPostRedisplay();
        break;
    case 'w':
        joelhoEsquerdo = (joelhoEsquerdo + 5) % 360;
        if (joelhoEsquerdo > 120 % 360)
            joelhoEsquerdo = 120;
        glutPostRedisplay();
        break;
    case 'W':
        joelhoEsquerdo = (joelhoEsquerdo - 5) % 360;
        if (joelhoEsquerdo < -120)
            joelhoEsquerdo = -120;
        glutPostRedisplay();
        break;
    case 's':
        peEsquerdox = (peEsquerdox + 5) % 360;
        glutPostRedisplay();
        break;
    case 'S':
        peEsquerdox = (peEsquerdox - 5) % 360;
        glutPostRedisplay();
        break;
        /* Movimentacao Lado Direito*/

    case 'e':
        femurDireitox = (femurDireitox + 5) % 360;
        glutPostRedisplay();
        break;
    case 'E':
        femurDireitox = (femurDireitox - 5) % 360;
        glutPostRedisplay();
        break;
    case 'd':
        femurDireitoy = (femurDireitoy + 5) % 360;
        glutPostRedisplay();
        break;
    case 'D':
        femurDireitoy = (femurDireitoy - 5) % 360;
        glutPostRedisplay();
        break;
    case 'c':
        femurDireitoz = (femurDireitoz + 5) % 360;
        glutPostRedisplay();
        break;
    case 'C':
        femurDireitoz = (femurDireitoz - 5) % 360;
        glutPostRedisplay();
        break;
    case 'r':
        joelhoDireito = (joelhoDireito + 5) % 360;
        if (joelhoDireito > 120 % 360)
            joelhoDireito = 120;
        glutPostRedisplay();
        break;
    case 'R':
        joelhoDireito = (joelhoDireito - 5) % 360;
        if (joelhoDireito < -120)
            joelhoDireito = -120;
        glutPostRedisplay();
        break;
    case 'f':
        peDireitox = (peDireitox + 5) % 360;
        glutPostRedisplay();
        break;
    case 'F':
        peDireitox = (peDireitox - 5) % 360;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutInitWindowSize(800, 800);

    glutInitWindowPosition(0, 0);

    glutCreateWindow("Movimento");

    Inicializa();

    glutDisplayFunc(Desenha);

    glutReshapeFunc(AlteraTamanhoJanela);

    glutKeyboardFunc(Teclado);

    glutMainLoop();
    return 0;
}

//
//#include <iostream>
//#include <memory>
//#include "Window.h"
//#include "MyScene.h"
//
//#define GLEW_STATIC
//
//
//int main(int argc, char** argv) {
//	Window w(800, 600, "TCC");
//	glEnable(GL_DEPTH_TEST);
//
//	w.setScene(std::unique_ptr<Scene>(new MyScene()));
//
//	while (!w.shouldClose())
//	{
//		w.update();
//	}
//
//	return 0;
//}
//
//
