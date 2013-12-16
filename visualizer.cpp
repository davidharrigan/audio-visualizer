//
//
//
//

#include <GL/glut.h>
#include <stdio.h>
#include "Audio.h"

#include "Point3.h"
#include "Scene.h"
#include "ScrollScene.h"
#include "Box.h"

#include <math.h>
#include <unistd.h>

bool scroll;
int windowWidth  = 1920;
int windowHeight = 1080;
float lightX, lightY = 0.0;
float sceneX = 3.4;
float sceneY = 5.4;

Scene *scene;
ScrollScene *scrollScene;
Audio *audio;

//
// Create a scene
//
void createScene(void) {
    scrollScene = new ScrollScene();
    scene = new Scene(); 
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
    glClearColor(0,0,0,0.0);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat ambient[4]  = {0.2, 0.2, 0.2, 1};
    GLfloat diffuse[4]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat location[4] = {0.2, 1.4, -1, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, location);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glEnable(GL_LIGHT1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(sceneX,sceneY,16,
              0.5,0,0,
              0,1,0);
    if (!scroll)
        scrollScene->redraw();
    else
        scene->redraw();
    glFlush();
    glutSwapBuffers();
}

//
// OpenGL keyboard function
//
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            scroll ^= 1;
            break;
        case 'h':
            sceneX -= 0.2;
            break;
        case 'l':
            sceneX += 0.2;
            break;
        case 'j':
            sceneY += 0.2;
            break;
        case 'k':
            sceneY -= 0.2;
            break;
        case 'H':
            lightX -= 0.2;
            break;
        case 'L':
            lightX += 0.2;
            break;
        case 'J':
            lightY += 0.2;
            break;
        case 'K':
            lightY -= 0.2;
            break;
        case 'n':
            audio->next();
            break;
        case 27:
            exit(0);

    }
    printf("Camera: %.2f, %.2f\n", sceneX, sceneY);
    printf("Light: %.2f, %.2f\n\n", lightX, lightY);
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    scroll = false;

    if (argc < 2) {
        printf("No sound file\n");
        return EXIT_FAILURE;
    }

    // Initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Visualizer");

    //Initialize audio components 
    audio = new Audio();
    audio->initialize();
    for (int i=1; i<argc; i++) {
        audio->saveFile(argv[i]);
    }
    audio->loadFile();
    
    glutDisplayFunc(redraw);
    glutKeyboardFunc(keyboard);
    appInit();

    audio->play();
    glutMainLoop();
    return EXIT_SUCCESS;
}
