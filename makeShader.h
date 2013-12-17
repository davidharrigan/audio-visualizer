#ifndef MAKE_SHADER_H_
#define MAKE_SHADER_H_
/**
 *
 *
 *
 *
 */
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/glext.h>

#include <cmath>
#include <iostream>
#include <stdio.h>

#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

GLuint makeShaderProgram(const char* vertexShaderFile, 
                         const char* fragmentShaderFile);
const GLfloat DivideByZeroTolerance = GLfloat(1.0e-07);
const GLfloat DegreesToRadians = M_PI / 180;

#endif
