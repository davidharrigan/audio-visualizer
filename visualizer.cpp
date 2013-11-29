//
//
//
//

#include <GL/glut.h>
#include <portaudio.h>
#include "Audio.h"

int windowWidth  = 640;
int windowHeight = 480;
PaStream *stream;

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20, w/(GLdouble)h, 1.0, 1000.0);
}

void appInit(void) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutReshapeFunc(reshape);
    glClearColor(0.5,0.5,0.5,0.0);
}

void redraw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    int window;

    if (argc != 2) {
        printf("No sound file\n");
        return EXIT_FAILURE;
    }

    // Initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 150);
    window = glutCreateWindow("Visualizer");
    
    glutDisplayFunc(redraw);
    appInit();

    // start audio stream
    startAudio(&stream, argv[1]);

    glutMainLoop();

    endAudio(&stream);
    return EXIT_SUCCESS;
}
