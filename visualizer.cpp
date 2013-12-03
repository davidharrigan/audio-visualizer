//
//
//
//

#include <GL/glut.h>
#include <portaudio.h>
#include <stdio.h>
#include "Audio.h"

#include "Point3.h"
#include "Scene.h"
#include "Box.h"

int windowWidth  = 640;
int windowHeight = 480;
//extern Packet *sharedBuffer;
//PaStream* stream;
Scene *scene;
Audio *audio;

//
// Create a scene
//
void createScene(void) {
    scene = new Scene();
    for (int i=0; i<20; i++) {
        Box *b = new Box();
        b->setSize(0.1,0.5,0.5);
        b->setColor( new Color(0,0,0+(float)i*0.1));
        b->setLocation(1-i*0.1, 0, 0);
        scene->addObject(b);
    }
}

//
// Window reshape function
//
void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(10, windowWidth/windowHeight, 0.1, 1000.0);
    glutPostRedisplay();
}

//
// Initialize OpenGL components
//
void appInit(void) {
    glClearColor(0.5,0.5,0.5,0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutReshapeFunc(reshape);
    createScene();
}

//
// OpenGL redraw function
//
void redraw(void) {
    glutPostRedisplay();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,3,10,
              0,0,0,
              0,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->redraw();
    glutSwapBuffers();
    glFlush();
}

int main(int argc, char *argv[]) {
    int window;
    //sharedBuffer = (Packet*)malloc(sizeof(Packet) * BUFFER_SIZE);

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

    //Initialize audio components 
    audio = new Audio();
    audio->initialize();
    if (!audio->loadFile(argv[1])) {
        return EXIT_FAILURE;
    }
    
    glutDisplayFunc(redraw);
    appInit();

    audio->play();
    glutMainLoop();
    return EXIT_SUCCESS;
}
