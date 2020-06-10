/**
*   Programa para ilustrar os elementos mais basicos do OpenGL e Glut.
*   - Apresenta os principais recursos do sistema de Janelas GLUT
*
*   Autor: Cesar Tadeu Pozzer
*   UFSM - 2020
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
* Referencias GLUT: http://www.opengl.org/documentation/specs/glut/
*                   http://www.opengl.org/documentation/specs/glut/spec3/node1.html
**/

#include "gl_canvas2d.h"
#include "../Utilities.h"
#include <GL/glut.h>

int *scrWidth, *scrHeight; //guarda referencia para as variaveis de altura e largura da main()

void point(double x, double y) {
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
}

void line(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

void rect(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINE_LOOP);
    glVertex2d(x1, y1);
    glVertex2d(x1, y2);
    glVertex2d(x2, y2);
    glVertex2d(x2, y1);
    glEnd();
}

void rectFill(int x1, int y1, int x2, int y2) {
    glBegin(GL_QUADS);
    glVertex2d(x1, y1);
    glVertex2d(x1, y2);
    glVertex2d(x2, y2);
    glVertex2d(x2, y1);
    glEnd();
}

void polygon(Float3 vertices[], int elems) {
    int cont;
    glBegin(GL_LINE_LOOP);
    for (cont = 0; cont < elems; cont++) {
        glVertex2d(vertices[cont].x, vertices[cont].y);
    }
    glEnd();
}

void polygonFill(Float3 vertices[], int elems) {
    int cont;
    glBegin(GL_POLYGON);
    for (cont = 0; cont < elems; cont++) {
        glVertex2d(vertices[cont].x, vertices[cont].y);
    }
    glEnd();
}

void text(int x, int y, const char *t) {
    int tam = (int) strlen(t);
    for (int c = 0; c < tam; c++) {
        glRasterPos2i(x + c * 10, y);
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, t[c]);
    }
}

void clear(float r, float g, float b) {
    glClearColor(r, g, b, 1);
}

void circle(int x, int y, int raio, int div) {
    float ang, x1, y1;
    float inc = PI_2 / div;
    glBegin(GL_LINE_LOOP);
    //nao vai ateh PI_2 pois o ultimo ponto eh fechado automaticamente com o primeiro, pois tem o tipo LINE_LOOP
    for (ang = 0; ang < 6.27; ang += inc) {
        x1 = (cos(ang) * raio);
        y1 = (sin(ang) * raio);
        glVertex2d(x1 + x, y1 + y);
    }
    glEnd();
}

void circleFill(int x, int y, int raio, int div) {
    float ang, x1, y1;
    float inc = PI_2 / div;
    glBegin(GL_POLYGON);
    for (ang = 0; ang < 6.27; ang += inc) {
        x1 = (cos(ang) * raio);
        y1 = (sin(ang) * raio);
        glVertex2d(x1 + x, y1 + y);
    }
    glEnd();
}

void color(float r, float g, float b) {
    glColor3d(r, g, b);
}

void color(float r, float g, float b, float a) {
    glColor4d(r, g, b, a);
}

void special(int key, int, int) {
    keyboard(key + 100);
}

void specialUp(int key, int, int) {
    keyboardUp(key + 100);
}

void keyb(unsigned char key, int, int) {
    keyboard(key);
}

void keybUp(unsigned char key, int, int) {
    keyboardUp(key);
}

void mouseClick(int button, int state, int x, int y) {
    ConvertMouseCoord(button, state, -2, -2, x, y);
}

void mouseWheelCB(int wheel, int direction, int x, int y) {
    ConvertMouseCoord(-2, -2, wheel, direction, x, y);
}

void motion(int x, int y) {
    ConvertMouseCoord(-2, -2, -2, -2, x, y);
}

void ConvertMouseCoord(int button, int state, int wheel, int direction, int x, int y) {
#if Y_CANVAS_CRESCE_PARA_CIMA == 1
    y = *scrHeight -
        y; //deve-se inverter a coordenada y do mouse se o y da canvas crescer para cima. O y do mouse sempre cresce para baixo.
#else
    //nao faz nada.
#endif
    mouse(button, state, wheel, direction, x, y);
}

//funcao chamada sempre que a tela for redimensionada.
void reshape(int w, int h) {
    *scrHeight = h; //atualiza as variaveis da main() com a nova dimensao da tela.
    *scrWidth = w;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //cria uma projecao ortografica com z entre (-1, 1).
#if Y_CANVAS_CRESCE_PARA_CIMA == 1
    //parametros: left, right, bottom, top
    gluOrtho2D(0.0, w, 0.0, h); //o eixo y cresce para cima.
#else
    //parametros: left, right, bottom, top
    gluOrtho2D(0.0, w, h, 0.0); //o eixo y cresce para baixo
#endif

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//definicao de valores para limpar buffers
void inicializa() {
    glClearColor(255 / 255.0, 255 / 255.0, 255 / 255.0, 0);
    glPolygonMode(GL_FRONT, GL_FILL);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    render();

    glFlush();
    glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////////////
//  inicializa o OpenGL
////////////////////////////////////////////////////////////////////////////////////////
void initCanvas(int *w, int *h, const char *title) {
    int argc = 0;
    glutInit(&argc, NULL);

    scrHeight = h;
    scrWidth = w;

    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowSize(*w, *h);
    glutInitWindowPosition(200, 200);
    glutCreateWindow(title);

    inicializa();

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyb);
    glutKeyboardUpFunc(keybUp);
    glutSpecialUpFunc(specialUp);
    glutSpecialFunc(special);

    glutIdleFunc(display);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(motion);
    glutMotionFunc(motion);
    glutMouseWheelFunc(mouseWheelCB);
    glutIgnoreKeyRepeat(1);
    printf("GL Version: %s", glGetString(GL_VERSION));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void runCanvas() {
    glutMainLoop();
}
